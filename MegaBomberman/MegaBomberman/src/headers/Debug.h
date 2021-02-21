#pragma once

#include "Singleton.h"

#include "../simple_types.h"

class Debug : public Singleton<Debug>
{
	friend class Singleton<Debug>;

private:
	Debug();
public:
	~Debug();

	// Console logs
	void Log(const char* title, const char* message);
	void LogWarning(const char* title, const char* message);
	void LogError(const char* title, const char* message);

	// Message box logs
	// TODO: Implement
};