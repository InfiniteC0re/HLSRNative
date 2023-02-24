#pragma once
#include <Windows.h>

#undef CopyFile

class FileSystem
{
public:
	struct DiskSpaceInfo
	{
		ULARGE_INTEGER FreeBytesAvailable;
		ULARGE_INTEGER TotalNumberOfBytes;
		ULARGE_INTEGER TotalNumberOfFreeBytes;
	};

public:
	static bool GetFreeDiskSpace(wchar_t* path, DiskSpaceInfo& info)
	{
		ULARGE_INTEGER freeBytesAvailable;
		ULARGE_INTEGER totalNumberOfBytes;
		ULARGE_INTEGER totalNumberOfFreeBytes;

		BOOL bRes = GetDiskFreeSpaceExW(path, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes);
		
		if (bRes == TRUE)
		{
			info.FreeBytesAvailable = freeBytesAvailable;
			info.TotalNumberOfBytes = totalNumberOfBytes;
			info.TotalNumberOfFreeBytes = totalNumberOfFreeBytes;

			return true;
		}

		return false;
	}

	static bool CopyFile(wchar_t* src, wchar_t* dst, bool overwrite = true)
	{
		BOOL bRes = CopyFileW(src, dst, !overwrite);
		return bRes == TRUE;
	}
};