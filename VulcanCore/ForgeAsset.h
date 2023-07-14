#pragma once

#include <string.h>
#include <stdio.h>

#include "zstd.h"
#include "types.h"

namespace VulcanCore {
	class CArrayReader {
		char* m_ptr;
		unsigned long long m_pos;
	public:
		CArrayReader(char*& source);
		unsigned long long Tell();
		void Seek(unsigned long long newPos);
		void Skip(unsigned long long offset);
		template <typename T> void Read(T& out);
		template <typename T> T Read();
		template <typename T> void Read(T*& out); // changes referencei instead of copying
		void Read(char*& out, unsigned long long size);
	};

	struct ForgeAssetChunk {
		unsigned int DataLength;
		unsigned int SerializedLength;
		unsigned int Offset;
	};

	class ForgeAsset {
		ForgeAssetChunk* ChunksSideA;
		ForgeAssetChunk* ChunksSideB;

		// how many chunks
		short ChunksNumA;
		short ChunksNumB;
	public:
		unsigned long long TotalUnpackedSide;
		char* DecompressedContent;

		void ReadChunks(CArrayReader& r, ForgeAssetChunk*& outChunks, short& ChunkNum);

		ForgeAsset(char*& ptr);
		~ForgeAsset();
	};
}
