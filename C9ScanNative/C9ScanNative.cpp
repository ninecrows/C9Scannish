// This is the main DLL file.

#include "stdafx.h"

#include "C9ScanNative.h"
namespace C9ScanNative
{

	/*array<String ^>^*/ void NativeAccessHelpers::VolumeNames()
	{
		std::list<std::wstring> nativeList;
		GetVolumeNames(nativeList);

		//return (nullptr);
	}


	NativeAccessHelpers::NativeAccessHelpers()
	{

	}

	void NativeAccessHelpers::DoSomething()
	{

	}
}
