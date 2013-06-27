#include "HTTPHandler.h"

void httpHandler(HTTPClient cliInfo)
{
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

			if (isPython(docRequest))
			{
				//Python module requested, execute python file
				PythonModule pm;
			}

			std::cout << docRequest << " from " << cliInfo.ip() << std::endl;

			std::string resp = "HTTP/1.1 200 OK\r\n"
				"Server: nginx/1.24\r\n"
				"Content-Length: 5\r\n"
				"Content-Type: text/html\r\n\r\n"
				"hello";
			send(cliInfo.clientSock, resp.c_str(), strlen(resp.c_str()) + 1, 0);
		}
	}
	while (readBytes > 0);
	
}

bool isPython(std::string docRequest)
{
	size_t loc = docRequest.find(".py");
	if (loc != std::string::npos)
	{
		if (loc == (docRequest.length() - 3))
			return true;
		else
			return false;
	}
	else
		return false;
}