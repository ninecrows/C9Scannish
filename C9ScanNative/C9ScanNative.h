#pragma once

#include <list>
#include <string>
#include <windows.h>
#include "MonitorList.h"
#include <msclr/marshal_cppstd.h>

using namespace System;

namespace C9ScanNative {
	public ref class NativeVolumeInformation
	{
	public:
		String ^ pathName;
		String ^ volumeName;
		String ^ volumeSerial;
		Int32 maximumComponentLength;
		Int32 flags;
		String ^ fileSystemName;
		String ^ volumeType;
	};

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
		static array<String ^>^ VolumeNames();

		static array<String ^>^ MountNames(String ^mountName);

		static array<String ^>^ DriveNames();

	public:
		// Get volume information using native API calls that allow us to dig deeper than C# calls do.
		static NativeVolumeInformation ^ VolumeInformation(String ^volumePath);
#if false
		{
			NativeVolumeInformation ^information = gcnew NativeVolumeInformation();

			// Save the volume path that was passed in so the caller gets if back in this data block.
			information->pathName = volumePath;

			std::wstring nativeVolumePath = msclr::interop::marshal_as<std::wstring>(volumePath);

			wchar_t buffer[MAX_PATH];
			DWORD vsn = 0;
			DWORD maximumComponentLength = 0;
			DWORD fileSystemFlags = 0;
			wchar_t nameBuffer[MAX_PATH];
			BOOL ok(::GetVolumeInformationW(nativeVolumePath.c_str(),
				buffer, MAX_PATH,
				&vsn,
				&maximumComponentLength,
				&fileSystemFlags,
				nameBuffer, MAX_PATH));

			wchar_t driveTypeString[64];
			{
				UINT driveType(::GetDriveTypeW(nativeVolumePath.c_str()));
				switch (driveType)
				{
				case DRIVE_UNKNOWN:
					wcscpy(driveTypeString, L"unknonwn");
					break;
				case DRIVE_NO_ROOT_DIR:
					wcscpy(driveTypeString, L"no root dir");
					break;
				case DRIVE_REMOVABLE:
					wcscpy(driveTypeString, L"removable");
					break;
				case DRIVE_FIXED:
					wcscpy(driveTypeString, L"fixed");
					break;
				case DRIVE_REMOTE:
					wcscpy(driveTypeString, L"remote");
					break;
				case DRIVE_CDROM:
					wcscpy(driveTypeString, L"cdrom");
					break;
				case DRIVE_RAMDISK:
					wcscpy(driveTypeString, L"ramdisk");
					break;
				default:
					_snwprintf(driveTypeString, 64, L"%lu", driveType);
					break;

				}
			}

			if (ok)
			{
				// Store physical volume type information.
				information->volumeType = Marshal::PtrToStringUni((IntPtr)driveTypeString);
				information->volumeName = Marshal::PtrToStringUni((IntPtr)buffer);
				information->fileSystemName = Marshal::PtrToStringUni((IntPtr)nameBuffer);
				{
					wchar_t vsnString[64];
					_snwprintf(vsnString, 64, L"%08lx", vsn);
					information->volumeSerial = Marshal::PtrToStringUni((IntPtr)vsnString);
				}
				information->flags = fileSystemFlags;
				information->maximumComponentLength = maximumComponentLength;
			}

			return (information);
		}
#endif
	};
}
