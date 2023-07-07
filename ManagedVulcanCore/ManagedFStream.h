#pragma once

#include <fstream>

namespace ManagedVulcanCore {
	public ref class ManagedFStream {
		std::fstream* m_Stream;
	public:
		ManagedFStream(System::String^ path);
		~ManagedFStream();
		!ManagedFStream();

		std::fstream* GetStream();
	};
}