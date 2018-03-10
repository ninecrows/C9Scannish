// This is the main DLL file.

#include "stdafx.h"

#include "C9ScanNative.h"
namespace C9ScanNative
{
#if false
	array<String ^>^ NativeAccessHelpers::VolumeNames()
	{
		std::list<std::wstring> nativeList;
		GetVolumeNames(nativeList);

		return (nullptr);
	}
#endif

	NativeAccessHelpers::NativeAccessHelpers()
	{

	}

	void NativeAccessHelpers::DoSomething()
	{

	}
}
