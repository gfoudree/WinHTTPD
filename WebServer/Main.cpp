#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>

#include "HTTPServer.h"

#pragma comment(lib, "Ws2_32.lib")

int main()
{
	HTTPServer httpd;
	try {
	httpd.startListen("9990");
	}
	catch (char *error)
	{
		MessageBoxA(0, error, 0, MB_OK);
	}
}