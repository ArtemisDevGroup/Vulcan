#pragma once

#include "../VulcanCore/Forge.h"
#include "ManagedFStream.h"
#include "ManagedEntry.h"
#include "ManagedEntryMetadata.h"

namespace ManagedVulcanCore {
	public ref class ManagedForge {
		VulcanCore::Forge* m_Instance;
		
	public:
		ManagedFStream^ m_StreamWrapper;

		ubiChar Version;
		ubiU32 MaxFile;
		ubiU32 MaxDir;
		ubiU32 MaxTable;
		ubiU64 FatLocation;

		array<ManagedEntry^>^ entries;
		array<ManagedEntryMetadata^>^ entryMetadatas;

		ManagedForge(ManagedFStream^ File);
		~ManagedForge();
		!ManagedForge();
	};
}