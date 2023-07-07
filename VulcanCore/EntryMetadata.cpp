#include "EntryMetadata.h"

namespace VulcanCore {
	auto DecodeName(std::string name, ubiU32 fileType, ubiU64 uid, ubiU64 dataOffset, ubiU64 keyStep) -> std::string {
		ubiU64 key = FILENAME_ENCODING_BASE_KEY + uid + dataOffset + fileType + ((ubiU64)fileType << 32);

		int blocks = (name.length() + 8) / 8;

		auto* output = new ubiU64[blocks];
		memcpy(output, name.c_str(), name.length());

		for (auto i = 0; i < blocks; i++)
		{
			output[i] ^= key;
			key += keyStep;
		}

		auto bytes = std::string((char*)output, name.length());
		return bytes;
	}

	EntryMetaData::EntryMetaData(std::fstream& File, ubiChar Version, ubiU64 Offset, ubiU64 Uid) {
		if (Version == 30)
		{
			File.seekg(0x14, std::ios::cur);

			File.read(NameBytes, 0xFF);
			File.read((char*)&NameLength, 1);
			File.read((char*)&TimeStamp, 4);

			File.seekg(0x4, std::ios::cur);

			File.read((char*)&PrevEntryIndex, 4);
			File.read((char*)&NextEntryIndex, 4);

			File.seekg(0x8, std::ios::cur);

			File.read((char*)&Type, 4);

			File.seekg(0x4 * 0x3, std::ios::cur);

			SizeOffset = File.tellg();
			File.read((char*)&Size, 4);

			Name = DecodeName(std::string(NameBytes, NameLength), Type, Uid, Offset, FILENAME_ENCODING_ENTRY_KEY_STEP);
		}
		else
		{
			throw std::exception(std::format("Unsupported Forge version: {}", Version).c_str());
		}
	}
}