#include "Forge.h"

namespace VulcanCore {

	Forge::Forge(std::fstream& File) {
		File.read(scimitar, 9); //0x0
		File.read((char*)&_version, 1); //0x9

		File.seekg(0x14, std::ios::cur); //+0x14

		File.read((char*)&MaxFile, 4); //0x1E
		File.read((char*)&MaxDir, 4); //0x22

		File.seekg(0x4 * 0x6, std::ios::cur); //+0x18

		File.read((char*)&MaxTable, 4); //0x30
		File.read((char*)&fatLocation, 8); //0x38
		
		for (auto i = 0; i < (int)MaxTable; i++)
		{
			ubiU32 m_MaxFile;
			ubiU32 m_MaxDir; //unused
			ubiU64 m_PosFat;
			ubiU64 m_NextPosFat; //unused
			ubiU32 m_FirstIndex; //unused
			ubiU32 m_LastIndex; //unused
			ubiU64 _metaTableOffset;
			ubiU64 _directoryOffset; //unused

			File.read((char*)&m_MaxFile, 4);
			File.read((char*)&m_MaxDir, 4);
			File.read((char*)&m_PosFat, 8);
			File.read((char*)&m_NextPosFat, 8);
			File.read((char*)&m_FirstIndex, 4);
			File.read((char*)&m_LastIndex, 4);
			File.read((char*)&_metaTableOffset, 8);
			File.read((char*)&_directoryOffset, 8);

			File.seekg(m_PosFat);
			for (auto j = 0; j < (int)m_MaxFile; j++)
			{
				Entries.push_back(Entry(File));
			}

			File.seekg(_metaTableOffset);
			for (auto j = 0; j < (int)m_MaxFile; j++)
			{
				EntryMetaDatas.push_back(EntryMetaData(File, _version, Entries[j].Offset, Entries[j].Uid));
			}
		}
	}

	Forge::~Forge() {
		
	}

	void Forge::Read(std::fstream& File, ubiU64 Uid, char* &output) {
		for (const auto &k : Entries) {
			if (k.Uid == Uid) {
				output = new char[k.Size];

				char* assetContainer = new char[k.Size];
				File.seekg(k.Offset);
				File.read(assetContainer, k.Size);

				ForgeAsset asset(assetContainer);


				//size_t const dSize = ZSTD_decompress(void* dst, size_t dstCapacity, const void* src, size_t compressedSize);

				break;
			}
		}
	}
}