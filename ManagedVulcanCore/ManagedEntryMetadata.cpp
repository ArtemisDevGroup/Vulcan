#include "ManagedEntryMetadata.h"

namespace ManagedVulcanCore {
	ManagedEntryMetadata::ManagedEntryMetadata(VulcanCore::EntryMetaData metadata) {
		m_Instance = &metadata;
		Name = msclr::interop::marshal_as<System::String^>(m_Instance->Name);
		TimeStamp = m_Instance->TimeStamp;
		PrevEntryIndex = m_Instance->PrevEntryIndex;
		NextEntryIndex = m_Instance->NextEntryIndex;
		Type = m_Instance->Type;
		SizeOffset = m_Instance->SizeOffset;
		Size = m_Instance->Size;
	}
	ManagedEntryMetadata::~ManagedEntryMetadata() { this->!ManagedEntryMetadata(); }
	ManagedEntryMetadata::!ManagedEntryMetadata() {
		delete m_Instance;
	};
}