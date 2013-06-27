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
public:
	void httpHandler(HTTPClient cliInfo, std::string docRootParam);
	bool isPython(std::string docRequest);
	std::string readFile(std::string filePath);

};