#pragma once

#include <msclr\marshal_cppstd.h>
#include "../VulcanCore/EntryMetadata.h"
#include "ManagedFStream.h"

namespace ManagedVulcanCore {
	public ref class ManagedEntryMetadata {
		VulcanCore::EntryMetaData* m_Instance;
	public:

		System::String^ Name;
		ubiU32 TimeStamp;
		ubiS32 PrevEntryIndex;
		ubiS32 NextEntryIndex;
		ubiU32 Type;
		ubiU64 SizeOffset;
		ubiU32 Size;

		ManagedEntryMetadata(VulcanCore::EntryMetaData metadata);
		~ManagedEntryMetadata();
		!ManagedEntryMetadata();
	};
}