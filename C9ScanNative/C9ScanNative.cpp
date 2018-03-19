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

	array<String^>^ NativeAccessHelpers::MountNames(String^ mountName)
	{
		std::wstring nativeString
			= msclr::interop::marshal_as<std::wstring>(mountName);

		std::list<std::wstring> nativeList;
		int result = GetMountNames(nativeString, nativeList);

		array<String ^>^ items = gcnew array<String ^>(nativeList.size());
		auto it = nativeList.begin();
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

	array<String ^>^ NativeAccessHelpers::DriveNames()
	{
		std::list<std::wstring> names;
		LogicalDriveNames(names);

		array<String ^>^ items = gcnew array<String ^>(names.size());

		return (items);
	}

	NativeVolumeInformation ^ NativeAccessHelpers::VolumeInformation(String ^volumePath)
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
				wcscpy_s(driveTypeString, L"unknonwn");
				break;
			case DRIVE_NO_ROOT_DIR:
				wcscpy_s(driveTypeString, L"no root dir");
				break;
			case DRIVE_REMOVABLE:
				wcscpy_s(driveTypeString, L"removable");
				break;
			case DRIVE_FIXED:
				wcscpy_s(driveTypeString, L"fixed");
				break;
			case DRIVE_REMOTE:
				wcscpy_s(driveTypeString, L"remote");
				break;
			case DRIVE_CDROM:
				wcscpy_s(driveTypeString, L"cdrom");
				break;
			case DRIVE_RAMDISK:
				wcscpy_s(driveTypeString, L"ramdisk");
				break;
			default:
				_snwprintf_s(driveTypeString, 64, L"%lu", driveType);
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
				_snwprintf_s(vsnString, 64, L"%08lx", vsn);
				information->volumeSerial = Marshal::PtrToStringUni((IntPtr)vsnString);
			}
			information->flags = fileSystemFlags;
			information->maximumComponentLength = maximumComponentLength;
		}

		return (information);
	}
	
	NativeAccessHelpers::NativeAccessHelpers()
	{

	}

	
	
}
