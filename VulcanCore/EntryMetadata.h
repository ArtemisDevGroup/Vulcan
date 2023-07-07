#pragma once

#include <fstream>
#include <format>
#include "types.h"

#define FILENAME_ENCODING_BASE_KEY 0xA860F0ECDE3339FB
#define FILENAME_ENCODING_ENTRY_KEY_STEP 0x357267C76FFB9EB2
#define FILENAME_ENCODING_FILE_KEY_STEP 0xE684BFF857699452

namespace VulcanCore {
	auto DecodeName(std::string name, ubiU32 fileType, ubiU64 uid, ubiU64 dataOffset, ubiU64 keyStep) -> std::string;

	class EntryMetaData {
		char NameBytes[0xFF];
		ubiChar NameLength;
	public:
		std::string Name;
		ubiU32 TimeStamp;
		ubiS32 PrevEntryIndex;
		ubiS32 NextEntryIndex;
		ubiU32 Type;
		ubiU64 SizeOffset;
		ubiU32 Size;

		EntryMetaData(std::fstream& File, ubiChar Version, ubiU64 Offset, ubiU64 Uid);
	};
}