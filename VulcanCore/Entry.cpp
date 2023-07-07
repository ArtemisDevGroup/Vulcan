#include "Entry.h"

namespace VulcanCore {
	Entry::Entry(std::fstream& File) {
		File.read((char*)&Offset, 8);
		File.read((char*)&Uid, 8);

		SizeOffset = File.tellg();
		File.read((char*)&Size, 4);
	}
}