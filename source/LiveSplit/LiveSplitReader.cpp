#include "LiveSplitReader.h"

bool LiveSplitReader::Open(const wchar_t* path)
{
	Close();

	pugi::xml_parse_result result = m_Doc.load_file(path);
	m_FileStatus = FileStatus::WRONG_FILE;

	if (result.status == pugi::xml_parse_status::status_ok)
	{
		m_RootNode = m_Doc.child(L"Run");

		if (m_RootNode)
		{
			m_FileStatus = FileStatus::OK;
			m_Splits.GameName = m_RootNode.child_value(L"GameName");
			m_Splits.AttemptCount = m_RootNode.child(L"AttemptCount").text().as_int();
			m_Splits.CategoryName = m_RootNode.child_value(L"CategoryName");

			pugi::xml_node segmentsRoot = m_RootNode.child(L"Segments");

			if (segmentsRoot)
			{
				pugi::xpath_node_set segments = segmentsRoot.select_nodes(L"Segment");

				for (int i = 0; i < segments.size(); i++)
				{
					pugi::xml_node segmentNode = segments[i].node();
					pugi::xml_node splitTimeNode = segmentNode.select_node(L"SplitTimes").node().select_node(L"SplitTime[@name='Personal Best']").node();
					pugi::xml_node bestSegmentTimeNode = segmentNode.select_node(L"BestSegmentTime").node();

					SegmentInfo* pSegment = new SegmentInfo;

					if (pSegment)
					{
						pSegment->Name = segmentNode.child_value(L"Name");
						pSegment->RealTime = splitTimeNode.child_value(L"RealTime");
						pSegment->GameTime = splitTimeNode.child_value(L"GameTime");
						pSegment->BestRealTime = bestSegmentTimeNode.child_value(L"RealTime");
						pSegment->BestGameTime = bestSegmentTimeNode.child_value(L"GameTime");

						m_Splits.Segments.push_back(pSegment);
					}
				}
			}
			else
			{
				m_FileStatus = FileStatus::NO_SEGMENTS;
			}
		}
	}
}

void LiveSplitReader::Close()
{
	for (int i = 0; i < m_Splits.segments.size(); i++)
	{
		delete m_Splits.Segments[i];
	}

	m_Doc.reset();
}
