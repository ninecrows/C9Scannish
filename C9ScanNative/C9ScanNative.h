#pragma once

#include <list>
#include <string>
#include <windows.h>
#include "MonitorList.h"

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

	inline DWORD GetMountNames(const std::wstring &volumeName, std::list<std::wstring> &result)
	{
		DWORD status = ERROR_SUCCESS;

		wchar_t name[MAX_PATH + 1];
		HANDLE h = FindFirstVolumeMountPointW(volumeName.c_str(), name, sizeof(name) / sizeof(*name));
		if (h != INVALID_HANDLE_VALUE)
		{
			result.push_back(std::wstring(name));

			BOOL moreComing = TRUE;
			while (moreComing)
			{
				moreComing = ::FindNextVolumeMountPointW(h, name, sizeof(name) / sizeof(*name));
				if (moreComing)
				{
					result.push_back(std::wstring(name));
				}
			}
		}
		else
		{
			status = ::GetLastError();
		}

		return (status);
	}

	inline void RawLogicalDriveNames(std::wstring &result, size_t bufferLength)
	{
		wchar_t *buffer = new wchar_t[bufferLength];

		DWORD actualLength = GetLogicalDriveStringsW(bufferLength, buffer);
		if (actualLength < bufferLength)
		{
			result = std::wstring(buffer, actualLength);
		}
		else
		{
			delete[] buffer;
			buffer = nullptr;

			RawLogicalDriveNames(result, actualLength + 1);
		}

		delete[] buffer;
	}

	inline void LogicalDriveNames(std::list<std::wstring> &drives)
	{
		// Get the results string from windows.
		std::wstring rawResult;
		RawLogicalDriveNames(rawResult, 256);

		size_t thisLength(0);
		size_t workingOffset(0);
		do
		{
			// Grab the next null terminated string at our working offset.
			std::wstring item(&rawResult[workingOffset]);
			if (item.length() > 0)
				drives.push_back(item);

			// Length of this item so we can decide whether to keep looping.
			thisLength = item.length();

			workingOffset += thisLength + 1;
		} while (thisLength > 0);
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

		static array<String ^>^ MountNames(String ^mountName);

		static array<String ^>^ DriveNames();
	};
}
