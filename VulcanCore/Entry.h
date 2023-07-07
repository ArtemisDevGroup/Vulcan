#pragma once

#include <fstream>
#include "types.h"

namespace VulcanCore {
	class Entry {
	public:
		ubiU64 Offset;
		ubiU64 Uid;

		ubiU64 SizeOffset;
		ubiU32 Size;

		Entry(std::fstream& File);
	};
}