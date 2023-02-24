#pragma once
#include <chrono>

class DateTime
{
public:
	static long long Now()
	{
		auto now = std::chrono::system_clock::now().time_since_epoch();
		return std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
	}
};