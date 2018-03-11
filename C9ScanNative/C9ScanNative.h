#pragma once

#include <list>
#include <string>
#include <windows.h>

using namespace System;

namespace C9ScanNative {

	inline void GetVolumeNames(std::list< std::wstring > &results)
	{
		wchar_t name[MAX_PATH + 1];
		HANDLE findHandle = ::FindFirstVolumeW(name, sizeof(name) / sizeof(*name));
		if (findHandle != INVALID_HANDLE_VALUE)
		{
			results.push_back(std::wstring(name));

			BOOL moreComing = TRUE;
			while (moreComing)
			{
				moreComing = ::FindNextVolumeW(findHandle, name, sizeof(name) / sizeof(*name));
				if (moreComing)
				{
					results.push_back(std::wstring(name));
				}
			}
		}

	}

	public ref class NativeAccessHelpers
	{
	public:
		NativeAccessHelpers();

	public:
		 void DoSomething();

	public:
		static String ^GetSomething()
		{
			return ("Foo");
		}

		static array<String ^>^ VolumeNames();

	private:
		static BOOL CALLBACK MonitorEnumProc(
			_In_ HMONITOR hMonitor,
			_In_ HDC      hdcMonitor,
			_In_ LPRECT   lprcMonitor,
			_In_ LPARAM   dwData
		);
	};
}
