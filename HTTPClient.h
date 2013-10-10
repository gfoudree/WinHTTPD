#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>

class HTTPClient
{
public:
	SOCKET clientSock;
	struct sockaddr_in cliInfo;

	std::string ip();
	HTTPClient(void);
	~HTTPClient(void);
};

#endif
