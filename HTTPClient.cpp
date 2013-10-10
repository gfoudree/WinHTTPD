#include "HTTPClient.h"


HTTPClient::HTTPClient(void)
{
}


HTTPClient::~HTTPClient(void)
{
}

std::string HTTPClient::ip()
{
	std::string ipaddr = inet_ntoa(cliInfo.sin_addr);
	return ipaddr;
}