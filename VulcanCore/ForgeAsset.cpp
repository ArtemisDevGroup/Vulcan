#include "ForgeAsset.h"

namespace VulcanCore {
	CArrayReader::CArrayReader(char*& source) {
		m_ptr = source;
		m_pos = 0;
	}

	template <typename T>
	void CArrayReader::Read(T& output) {
		auto _size = sizeof(T);

		// copy memory
		memcpy(&output, m_ptr + m_pos, _size);

		// increase position pointer
		m_pos += _size;
	}

	template <typename T>
	T CArrayReader::Read() {
		T ret;
		auto _size = sizeof(T);

		// copy memory
		memcpy(&ret, m_ptr + m_pos, _size);

		// increase position pointer
		m_pos += _size;

		return ret;
	}

	template <typename T> void CArrayReader::Read(T*& out) {
		out = (T*)(m_ptr + m_pos);

		m_pos += sizeof(T);
	}

	ForgeAsset::ForgeAsset(char*& ptr) {
		CArrayReader r(ptr);

		ubiU32 containerMagic = r.Read<ubiU32>();
		printf("Container Magic: 0x%llx\n", containerMagic);

		ubiU32 ForgeAssetMagic = r.Read<ubiU32>();
		printf("ForgeAssetMagic: 0x%llx\n", ForgeAssetMagic);

		ubiU16 ContainerDeserializationType = r.Read<ubiU16>();
		printf("ContainerDeserializationType: 0x%llx\n", ContainerDeserializationType);


	}
}