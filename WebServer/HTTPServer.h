#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <boost\thread\thread.hpp>
#include <boost\bind\bind.hpp>

#include "HTTPClient.h"
#include "HTTPHandler.h"


class HTTPServer
{
protected:
	WSADATA wsadata;
	struct addrinfo srv, *result;

	std::vector<HTTPClient> httpClients;

	boost::thread_group threadGroup;

public:
	SOCKET serverSock;

	void startListen(const char *port);

	HTTPServer(void);
	~HTTPServer(void);
};
