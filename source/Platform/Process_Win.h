#pragma once
#include "System_Win.h"

#include <Windows.h>
#include <cstdint>

class Process
{
public:
	typedef uint32_t Priority;
	enum Priority_ : Priority
	{
		Priority_Idle,
		Priority_BelowNormal,
		Priority_Normal,
		Priority_AboveNormal,
		Priority_High,
		Priority_RealTime,
	};

	using ProcessInfo = PROCESS_INFORMATION;

public:
	static bool Create(wchar_t* process, wchar_t* commandLine = NULL, wchar_t* currentDirectory = NULL, Priority priority = Priority_Normal, int numCores = 1, ProcessInfo* pProcessInfo = NULL)
	{
		DWORD creationFlags = 0;

		switch (priority)
		{
		case Priority_Idle:
			creationFlags |= IDLE_PRIORITY_CLASS;
			break;
		case Priority_BelowNormal:
			creationFlags |= BELOW_NORMAL_PRIORITY_CLASS;
			break;
		case Priority_Normal:
			creationFlags |= NORMAL_PRIORITY_CLASS;
			break;
		case Priority_AboveNormal:
			creationFlags |= ABOVE_NORMAL_PRIORITY_CLASS;
			break;
		case Priority_High:
			creationFlags |= HIGH_PRIORITY_CLASS;
			break;
		case Priority_RealTime:
			creationFlags |= REALTIME_PRIORITY_CLASS;
			break;
		}

		STARTUPINFOW startupInfo;
		memset(&startupInfo, '\0', sizeof(startupInfo));

		PROCESS_INFORMATION processInfo;
		BOOL bRes = CreateProcessW(process, commandLine, NULL, NULL, FALSE, creationFlags, NULL, currentDirectory, &startupInfo, &processInfo);
		
		if (bRes)
		{
			if (pProcessInfo != NULL)
			{
				*pProcessInfo = processInfo;
			}

			if (numCores == -1)
			{
				numCores = System::GetNumberOfProcessors();
			}

			DWORD_PTR processAffinityMask = (1 << numCores) - 1;
			SetProcessAffinityMask(processInfo.hProcess, processAffinityMask);

			return true;
		}

		return false;
	}
};