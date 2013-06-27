#include "HTTPServer.h"


HTTPServer::HTTPServer(std::string docRootParam)
{
	WSAStartup(MAKEWORD(2,2), &this->wsadata);
	memset(&this->srv, 0, sizeof(srv));

	srv.ai_family = AF_INET;
	srv.ai_socktype = SOCK_STREAM;
	srv.ai_protocol = IPPROTO_TCP;
	srv.ai_flags = AI_PASSIVE;

	docRoot = docRootParam;
}


HTTPServer::~HTTPServer(void)
{
	WSACleanup();
	closesocket(serverSock);
	threadGroup.join_all();
}

void HTTPServer::startListen(const char *port)
{
	if (getaddrinfo(NULL, port, &srv, &result) != 0)
		throw "Error in getaddrinfo()";
	serverSock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (serverSock == INVALID_SOCKET)
		throw "Error creating socket";
	if (bind(serverSock, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR)
		throw "Error binding";
	freeaddrinfo(result);
	if (listen(serverSock, SOMAXCONN) == SOCKET_ERROR)
		throw "Error listening";

	while (1)
	{
		int addrlen = sizeof(sockaddr_in);
		HTTPClient httpCli;
		httpCli.clientSock = accept(serverSock, (sockaddr*)&httpCli.cliInfo, &addrlen);
		httpClients.push_back(httpCli);

		HTTPHandler hp;
		boost::thread hThread(boost::bind(&HTTPHandler::httpHandler, &hp, httpCli, docRoot)); 
		threadGroup.add_thread(&hThread);
	}
}