#include "Error.h"
#include <windows.h>
#include <iostream>

int Error(std::string message)
{
	int code = GetLastError();

	std::cerr
		<< std::endl << "---------------------------------------" << std::endl
		<< "Error: " << message << " with code: " << code
		<< std::endl << "---------------------------------------" << std::endl;

	return code;
}