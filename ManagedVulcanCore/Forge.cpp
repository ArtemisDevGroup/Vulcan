#include "Forge.h"

namespace ManagedVulcanCore {
	ManagedForge::ManagedForge(ManagedFStream^ File) {
		m_StreamWrapper = File;
		m_Instance = new VulcanCore::Forge(*m_StreamWrapper->GetStream());

		const auto ENTRIES_SIZE = m_Instance->Entries.size();
		const auto ENTRY_METADATAS_SIZE = m_Instance->EntryMetaDatas.size();

		entries = gcnew array<ManagedEntry^>(ENTRIES_SIZE);
		for (auto i = 0; i < ENTRIES_SIZE; i++) {
			entries[i] = gcnew ManagedEntry(m_Instance->Entries[i]);
		}

		entryMetadatas = gcnew array<ManagedEntryMetadata^>(ENTRY_METADATAS_SIZE);
		for (auto i = 0; i < ENTRY_METADATAS_SIZE; i++) {
			entryMetadatas[i] = gcnew ManagedEntryMetadata(m_Instance->EntryMetaDatas[i]);
		}
	}
	ManagedForge::~ManagedForge() { this->!ManagedForge(); }
	ManagedForge::!ManagedForge() {
		delete m_StreamWrapper;
		delete m_Instance;
		delete entries;
		delete entryMetadatas;
	};

	bool ManagedForge::ReadEntry(ubiU64 Uid) {
		for (int i = 0; i < entries->Length; i++) {
			if (entries[i]->Uid == Uid) {
				m_Instance->Read(*m_StreamWrapper->GetStream(), Uid);

				entryData = gcnew array<char>(entries[i]->Size);

				for (int j = 0; j < entries[i]->Size; j++) {
					entryData[j] = m_Instance->entryData[j];
				}

				return true;
			}
		}
		return false;

		
	}

}