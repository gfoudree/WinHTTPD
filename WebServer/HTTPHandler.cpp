#include "HTTPHandler.h"

void HTTPHandler::httpHandler(HTTPClient cliInfo, std::string docRootParam)
{
	docRoot = docRootParam;
	char buf[1024];
	const int recvbufLen = sizeof(buf);
	int readBytes;
	do
	{
		readBytes = recv(cliInfo.clientSock, buf, recvbufLen, 0);
		if (readBytes > 0)
		{
			char *docRequestStr = strtok(buf, "\n");
			char *docRequest = strtok(docRequestStr, " ");
			docRequest = strtok(NULL, " ");

			if (docRequest == NULL)
				break;

			if (isPython(docRequest))
			{
				//Python module requested, execute python file
				PythonModule pm;
			}

			std::cout << docRequest << " from " << cliInfo.ip() << std::endl;

			std::string file = docRequest;
			file.erase(0, 1);
			std::string html = readFile(file);

			std::stringstream resp;
			resp << "HTTP/1.1 200 OK\r\n"
				"Server: nginx/1.24\r\n"
				"Content-Length: " << html.length() << "\r\nContent-Type: text/html\r\n\r\n" << html;

			send(cliInfo.clientSock, resp.str().c_str(), strlen(resp.str().c_str()) + 1, 0);
		}
	}
	while (readBytes > 0);
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
	filePath.insert(0, this->docRoot);
	std::string fileBuf;
	std::ifstream hFile (filePath, std::ios::binary);
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
	return fileBuf;
}