#include "ManagedFStream.h"

using namespace System::Runtime::InteropServices;

namespace ManagedVulcanCore {
	static auto UnmanageString(System::String^ string) -> std::string
	{
		const char* str = (const char*)(Marshal::StringToHGlobalAnsi(string)).ToPointer();
		return std::string(str);
	}

	ManagedFStream::ManagedFStream(System::String^ path) {
		auto path_string = UnmanageString(path);
		m_Stream = new std::fstream(path_string);
	}

	ManagedFStream::~ManagedFStream() {
		this->!ManagedFStream();
		}
	ManagedFStream::!ManagedFStream() {
		//delete m_Stream; // may leak memory but i dont care
	}

	std::fstream* ManagedFStream::GetStream() {
		return m_Stream;
	}
}