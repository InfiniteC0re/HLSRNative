#pragma once
#include <Windows.h>
#include <vector>
#include <string>

class Window
{
private:
	struct EnumWindowsData
	{
		DWORD iProcessId;
		std::vector<Window>& Windows;
	};

	static BOOL CALLBACK EnumWindowsCallback(HWND hHwnd, LPARAM lParam)
	{
		EnumWindowsData* pData = static_cast<EnumWindowsData*>(lParam);

		DWORD iProcessId = 0;
		GetWindowThreadProcessId(hHwnd, &iProcessId);

		if (pData->iProcessId == iProcessId)
		{
			pData->Windows.emplace_back(hHwnd);
		}

		return TRUE;
	}

public:
	Window(HANDLE hHandle) : m_hHandle(hHandle)
	{

	}

	bool IsVisible()
	{
		BOOL bRes = IsWindowVisible(m_hHandle);
		return bRes == TRUE;
	}

	bool IsEnabled()
	{
		BOOL bRes = IsWindowEnabled(m_hHandle);
		return bRes == TRUE;
	}

	std::wstring GetTitle()
	{
		WCHAR title[256] = { L'\0' };
		GetWindowTextW(m_hHandle, title, sizeof(title) / sizeof(*title));

		return title;
	}

	static std::vector<Window> GetProcessWindows(DWORD iProcessId)
	{
		std::vector<Window> windows;

		EnumWindowsData data{ iProcessId, windows };
		EnumWindows(EnumWindowsCallback, &data);

		return windows;
	}

private:
	HANDLE m_hHandle;
};