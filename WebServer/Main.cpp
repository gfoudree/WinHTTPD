#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>

#include "HTTPServer.h"

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "Please specify a root directory. (WebServer.exe -d C:\\www)";
		return 1;
	}

	if (strcmp(argv[1], "-d") == 0)
	{
		HTTPServer httpd(argv[2]);
		try {
		httpd.startListen("9990");
		}
		catch (char *error)
		{
			MessageBoxA(0, error, 0, MB_OK);
		}
	}
}
