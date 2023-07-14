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

	array<char>^ ManagedForge::ReadEntry(ubiU64 Uid) {
		for (int i = 0; i < entries->Length; i++) {
			if (entries[i]->Uid == Uid) {
				char* buffer;
				auto bufferSize = m_Instance->Read(*m_StreamWrapper->GetStream(), Uid, buffer);

				auto data = gcnew array<char>(bufferSize);

				for (int j = 0; j < bufferSize; j++) {
					data[j] = buffer[j];
				}

				delete[] buffer; // should fix memory leaks ?!

				return data;
			}
		}
		return nullptr;
	}

}