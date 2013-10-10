#include "PythonModule.h"


PythonModule::PythonModule(void)
{
}


PythonModule::~PythonModule(void)
{
}

std::string PythonModule::runPythonScript(std::string path)
{
	std::string output;
	char buf[128];
	FILE *hProc;
	hProc = _popen(path.c_str(), "rt");

	if (hProc == NULL)
	{
		std::cout << "Unable to execute python file at " << path.c_str();
		return "";
	}

	while (fgets(buf, 127, hProc))
	{
		output.append(buf);
	}

	if (feof(hProc))
		_pclose(hProc);

	return output;
}