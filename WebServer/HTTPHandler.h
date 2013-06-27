#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winsock2.h>
#include <boost\thread\thread.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>

#include "HTTPClient.h"
#include "HTTPCodes.h"
#include "PythonModule.h"

class HTTPHandler
{
protected:
	std::string docRoot;
	HTTPClient cliInfo;

	std::string HTTPHandler::trimRequestSlash(char *strPtr);
	char *parseDocRequest(char *httpBuf);

public:
	void httpHandler(HTTPClient cliInfoParam, std::string docRootParam);
	bool isPython(std::string docRequest);
	std::string readFile(std::string filePath);

	~HTTPHandler();
};