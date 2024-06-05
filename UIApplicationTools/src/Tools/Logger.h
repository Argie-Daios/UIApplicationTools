#pragma once

#include <string>
using UIString = std::string;

class Logger
{
public:
	static void Message(const UIString& message, char end = '\n');
	static void DebugMessage(const UIString& message, char end = '\n');
};