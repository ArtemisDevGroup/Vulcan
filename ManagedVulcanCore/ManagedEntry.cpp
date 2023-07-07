#include "ManagedEntry.h"

namespace ManagedVulcanCore {
	ManagedEntry::ManagedEntry(VulcanCore::Entry entry) {
		m_Instance = &entry;
		Offset = m_Instance->Offset;
		Uid = m_Instance->Uid;
		SizeOffset = m_Instance->SizeOffset;
		Size = m_Instance->Size;
	}
	ManagedEntry::~ManagedEntry() { this->!ManagedEntry(); }
	ManagedEntry::!ManagedEntry() {
		delete m_Instance;
	};
}