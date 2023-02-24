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

	static bool CopyDirectory(wchar_t* src, wchar_t* dst)
	{
		size_t srcLen = wcslen(src);
		size_t dstLen = wcslen(dst);

		WCHAR* from = new WCHAR[srcLen + 2];
		wcscpy(from, src);
		from[srcLen] = L'\0';
		from[srcLen + 1] = L'\0';

		WCHAR* to = new WCHAR[dstLen + 2];
		wcscpy(to, src);
		to[dstLen] = L'\0';
		to[dstLen + 1] = L'\0';

		SHFILEOPSTRUCTW fileOp = { 0 };
		fileOp.wFunc = FO_COPY;
		fileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMMKDIR | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NO_UI;
		fileOp.pFrom = from;
		fileOp.pTo = to;

		int iRes = SHFileOperationW(&fileOp);

		delete[] from;
		delete[] to;

		return iRes == 0;
	}
};