#pragma once

#include "../VulcanCore/Entry.h"
#include "ManagedFStream.h"

namespace ManagedVulcanCore {
	public ref class ManagedEntry {
		VulcanCore::Entry* m_Instance;
	public:

		ubiU64 Offset;
		ubiU64 Uid;
		ubiU64 SizeOffset;
		ubiU64 Size;

		ManagedEntry(VulcanCore::Entry entry);
		~ManagedEntry();
		!ManagedEntry();
	};
}