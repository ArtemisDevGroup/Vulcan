#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "types.h"
#include "Entry.h"
#include "EntryMetadata.h"
#include "ForgeAsset.h"

namespace VulcanCore {

	class Forge {
		char scimitar[0x9]; //0x0		should be scimitar� (73 63 69 6D 69 74 61 72 00)
	public:
		ubiChar _version; //0x9

		ubiU32 MaxFile; //0x1E
		ubiU32 MaxDir; //0x22
		ubiU32 MaxTable; //0x30

		ubiU64 fatLocation; //0x38

		std::vector<Entry> Entries;
		std::vector<EntryMetaData> EntryMetaDatas;

		Forge(std::fstream& File);
		~Forge();
		unsigned long long Read(std::fstream& File, ubiU64 Uid, char* &output);
	};
}