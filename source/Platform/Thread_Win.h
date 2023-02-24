#pragma once
#include <Windows.h>

class Thread
{
public:
	static void Sleep(unsigned long ms)
	{
		::Sleep(ms);
	}
};