#include "ForgeAsset.h"

namespace VulcanCore {
	CArrayReader::CArrayReader(char*& source) {
		m_ptr = source;
		m_pos = 0;
	}

	unsigned long long CArrayReader::Tell() {
		return m_pos;
	}
	void CArrayReader::Seek(unsigned long long newPos) {
		m_pos = newPos;
	}
	void CArrayReader::Skip(unsigned long long offset) {
		m_pos += offset;
	}

	template <typename T>
	void CArrayReader::Read(T& output) {
		auto _size = sizeof(T);

		// copy memory
		memcpy(&output, m_ptr + m_pos, _size);

		// increase position pointer
		m_pos += _size;
	}

	template <typename T>
	T CArrayReader::Read() {
		T ret;
		auto _size = sizeof(T);

		// copy memory
		memcpy(&ret, m_ptr + m_pos, _size);

		// increase position pointer
		m_pos += _size;

		return ret;
	}

	template <typename T>
	void CArrayReader::Read(T*& out) {
		out = (T*)(m_ptr + m_pos);

		m_pos += sizeof(T);
	}

	void CArrayReader::Read(char*& out, unsigned long long size) {
		out = new char[size];
		memcpy(out, m_ptr + m_pos, size);

		m_pos += size;
	}

	void ForgeAsset::ReadChunks(CArrayReader& r, ForgeAssetChunk*& outChunks, short& ChunkNum) {
		ubiU16 ContainerDeserializationType = r.Read<ubiU16>();
		printf("ContainerDeserializationType: 0x%llx\n", ContainerDeserializationType);

		ubiU16 ContainerDeserializationType2 = r.Read<ubiU16>();
		printf("ContainerDeserializationType2: 0x%llx\n", ContainerDeserializationType2);

		ubiU8 unk1 = r.Read<ubiU8>();
		ubiU16 unk2 = r.Read<ubiU16>();

		ChunkNum = r.Read<ubiU16>();
		printf("ChunkNum: 0x%llx\n", ChunkNum);

		ubiU16 u2 = r.Read<ubiU16>();
		printf("u2: 0x%llx\n\n", u2);

		unsigned long long TotalSerializedSize = 0;
		outChunks = new ForgeAssetChunk[ChunkNum];
		for (int i = 0; i < ChunkNum; i++) {
			outChunks[i].DataLength = r.Read<ubiU32>();
			outChunks[i].SerializedLength = r.Read<ubiU32>();

			printf("Chunk %d\n", i);
			printf("Data Length: 0x%llx\n", outChunks[i].DataLength);
			printf("Serialized Length: 0x%llx\n\n", outChunks[i].SerializedLength);

			TotalSerializedSize += outChunks[i].SerializedLength;
		}
		for (int i = 0; i < ChunkNum; i++) {
			ubiU32 hash = r.Read<ubiU32>();

			outChunks[i].Offset = r.Tell();
			r.Skip(outChunks[i].SerializedLength);
		}

		printf("TotalSerializedSize: 0x%llx\n", TotalSerializedSize);

	}

	ForgeAsset::ForgeAsset(char*& ptr) {
		CArrayReader r(ptr);

		ubiU32 containerMagic = r.Read<ubiU32>();
		printf("Container Magic: 0x%llx\n", containerMagic);

		ubiU32 ForgeAssetMagic = r.Read<ubiU32>();
		printf("ForgeAssetMagic: 0x%llx\n", ForgeAssetMagic);

		ReadChunks(r, ChunksSideA, ChunksNumA);
		ubiU64 AssetBlockMagic = r.Read<ubiU64>();
		ReadChunks(r, ChunksSideB, ChunksNumB);

		TotalUnpackedSide = 0;
		for (int i = 0; i < ChunksNumB; i++) {
			TotalUnpackedSide += ChunksSideB[i].DataLength;
		}

		printf("Total unpacked size: 0x%x", TotalUnpackedSide);

		// size_t const dSize = ZSTD_decompress(void* dst, size_t dstCapacity, const void* src, size_t compressedSize);
		DecompressedContent = new char[TotalUnpackedSide];
		unsigned long long currentOffset = 0;
		for (int i = 0; i < ChunksNumB; i++) {
			r.Seek(ChunksSideB[i].Offset);
			auto packedSize = ChunksSideB->SerializedLength;
			char* packedContent;
			r.Read(packedContent, packedSize);
			
			ZSTD_decompress(DecompressedContent+currentOffset, TotalUnpackedSide, packedContent, packedSize); // expand on this to be compatible with other seasons

			currentOffset += packedSize;
			delete[] packedContent;
		}
	}

	ForgeAsset::~ForgeAsset() {
		delete[] ChunksSideA;
		delete[] ChunksSideB;
		delete[] DecompressedContent;
	}
}