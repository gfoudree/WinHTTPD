#include "HTTPHandler.h"

HTTPHandler::~HTTPHandler()
{
	closesocket(cliInfo.clientSock);
}

void HTTPHandler::httpHandler(HTTPClient cliInfoParam, std::string docRootParam)
{
	docRoot = docRootParam;
	cliInfo = cliInfoParam;

	char buf[1024];
	const int recvbufLen = sizeof(buf);
	int readBytes;
	do
	{
		readBytes = recv(cliInfo.clientSock, buf, recvbufLen, 0);
		if (readBytes > 0)
		{
            int httpStatus = 200;
			char *docRequest = parseDocRequest(buf);
			if (docRequest == NULL) //Is the request malformed? protect from null pointer
				break;

            std::string docFile = requestToRoot((char*)trimRequestSlash(docRequest).c_str());
            std::string data;

            std::cout << docRequest << " from " << cliInfo.ip() << std::endl;

			if (isPython(docRequest))
			{
				//Python module requested, execute python file
				PythonModule pm;
                try
                {
                    data = pm.runPythonScript(docFile);
                }
                catch (int error)
                {
                    httpStatus = error;
                }
			}
            else
            {
                try
                {
                    data = readFile(docFile);
                }
                catch (int error)
                {
                    httpStatus = error;
                }
            }

			std::stringstream resp;
            resp << "HTTP/1.1 ";

            switch(httpStatus)
            {
                case 200:
                {
                    resp << "200 OK\r\n";
                }
                break;

                case 500:
                {
                    resp << "500 Internal Server Error\r\n";
                    data = "<h1>500 Internal Server Error<h1>";
                }
                break;

                case 404:
                {
                    resp << "404 Not Found\r\n";
                    data = "<h1>404 Not Found<h1>";
                }
                break;
            }

            resp << "Server: WinHTTPD/1.00\r\nContent-Length: " << data.length() << "\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n" << data;

			send(cliInfo.clientSock, resp.str().c_str(), strlen(resp.str().c_str()) + 1, 0);
		}
	}
	while (readBytes > 0);
	closesocket(cliInfo.clientSock);
}

bool HTTPHandler::isPython(std::string docRequest)
{
	size_t loc = docRequest.find(".py");
	if (loc != std::string::npos)
	{
		if (loc == (docRequest.length() - 3)) //Check if .py is at the end of the string (no /.py/hello.html)
			return true;
		else
			return false;
	}
	else
		return false;
}

std::string HTTPHandler::readFile(std::string filePath)
{
	std::string fileBuf;
    std::ifstream hFile(filePath.c_str(), std::ios::binary);
	if (hFile.is_open())
	{
		while (hFile.good())
		{
			std::string tmpStr;
            getline(hFile, tmpStr);
			fileBuf.append(tmpStr);
		}
		hFile.close();
	}
    else
    {
        throw 404;
    }

	return fileBuf;
}

std::string HTTPHandler::trimRequestSlash(char *strPtr)
{
	std::string req = strPtr;
	req.erase(0, 1);
	return req;
}

char *HTTPHandler::parseDocRequest(char *httpBuf)
{
	char *docRequestStr = strtok(httpBuf, "\n");
	char *docRequest = strtok(docRequestStr, " ");
	docRequest = strtok(NULL, " ");
	return docRequest;
}

std::string HTTPHandler::requestToRoot(char *request)
{
    std::string retStr = docRoot;
    retStr.append("\\");
    retStr.append(request);
    return retStr;
}
