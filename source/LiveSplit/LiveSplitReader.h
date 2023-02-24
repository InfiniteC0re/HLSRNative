#pragma once
#include "pugi/pugixml.hpp"
#include <vector>

class LiveSplitReader
{
public:
	enum class FileStatus
	{
		OK,
		NO_SEGMENTS,
		WRONG_FILE,
	};

	struct SegmentInfo
	{
		const pugi::char_t* Name;
		const pugi::char_t* RealTime;
		const pugi::char_t* GameTime;
		const pugi::char_t* BestRealTime;
		const pugi::char_t* BestGameTime;
	};

	struct SplitsInfo
	{
		const pugi::char_t* GameName = nullptr;
		const pugi::char_t* CategoryName = nullptr;
		int AttemptCount = 0;

		std::vector<SegmentInfo*> Segments;
	};

public:
	LiveSplitReader()
	{
		m_FileStatus = FileStatus::WRONG_FILE;
	}

	~LiveSplitReader()
	{
		Reset();
	}

	bool Open(const wchar_t* path);
	void Close();

private:
	pugi::xml_document m_Doc;
	pugi::xml_node m_RootNode;
	FileStatus m_FileStatus;
	SplitsInfo m_Splits;
};
