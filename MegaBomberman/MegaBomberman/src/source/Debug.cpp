#include "..\headers\Debug.h"

#include <iostream>
#include <cstdarg>

Debug::Debug() {

}

Debug::~Debug()
{
}

void Debug::Log(const char * title, const char * message)
{
	std::cout << "\033[32m" << "[Info] " << title << ": " << message << "\033[0m" << std::endl;
}

void Debug::LogWarning(const char * title, const char * message)
{
	std::cout << "\033[33m" << "[Warning] " << title << ": " << message << "\033[0m" << std::endl;
}

void Debug::LogError(const char * title, const char * message)
{
	std::cout << "\033[31m" << "[Error] " << title << ": " << message << "\033[0m" << std::endl;
}