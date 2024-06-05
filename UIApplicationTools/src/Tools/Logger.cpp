#include "Logger.h"

#include <iostream>

void Logger::Message(const UIString& message, char end)
{
	std::cout << message << end;
}

#ifdef UIDEBUG
	void Logger::DebugMessage(const UIString& message, char end)
	{
		Message(message, end);
	}
#else
	void Logger::DebugMessage(const UIString& message, char end)
	{

	}
#endif