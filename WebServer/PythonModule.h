#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>

class PythonModule
{
public:
	std::string runPythonScript(std::string path);

	PythonModule(void);
	~PythonModule(void);
};

