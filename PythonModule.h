#ifndef PYTHONMODULE_H
#define PYTHONMODULE_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <stdio.h>

class PythonModule
{
public:
	std::string runPythonScript(std::string path);

	PythonModule(void);
	~PythonModule(void);
};

#endif
