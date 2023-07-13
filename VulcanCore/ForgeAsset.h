#pragma once

#include <string.h>
#include <stdio.h>

#include "types.h"

namespace VulcanCore {
	class CArrayReader {
		char* m_ptr;
		unsigned long long m_pos;
	public:
		CArrayReader(char*& source);
		template <typename T> void Read(T& out);
		template <typename T> T Read();
		template <typename T> void Read(T*& out); // changes referencei instead of copying
	};

	class ForgeAsset {
		
	public:
		ForgeAsset(char*& ptr);
	};
}
