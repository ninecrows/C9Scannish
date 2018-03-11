// This is the main DLL file.

#include "stdafx.h"

#include "C9ScanNative.h"
#include <windows.h>

using namespace System::Runtime::InteropServices;

namespace C9ScanNative
{
	
	array<String ^>^ NativeAccessHelpers::VolumeNames()
	{
		std::list<std::wstring> nativeList;
		GetVolumeNames(nativeList);

		array<String ^>^ items = gcnew array<String ^>(nativeList.size());

		/*std::list<std::wstring>::iterator*/ auto it = nativeList.begin();
		for (int ct = 0; ct < items->Length; ct++)
		{
			wchar_t *temp(const_cast<wchar_t *>((*it).c_str()));
			int howMany((*it).length());
			String^ foo = Marshal::PtrToStringUni((IntPtr)temp, howMany);

			items[ct] = foo; //gcnew String((*it).c_str());			
			
			it++;
		}

		return (items);
	}


	NativeAccessHelpers::NativeAccessHelpers()
	{

	}

	void NativeAccessHelpers::DoSomething()
	{
		auto lll = new MonitorList();

		delete lll;
	}

	
}
