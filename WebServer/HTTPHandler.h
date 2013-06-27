#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winsock2.h>
#include <boost\thread\thread.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "HTTPClient.h"
#include "HTTPCodes.h"
#include "PythonModule.h"

void httpHandler(HTTPClient cliInfo);

bool isPython(std::string docRequest);