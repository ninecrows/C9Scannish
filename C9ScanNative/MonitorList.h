#pragma once

#include <windows.h>

class MonitorList
{
public:
	MonitorList();
	~MonitorList();

private:
	static BOOL CALLBACK MonitorList::MonitorEnumProc(
		_In_ HMONITOR hMonitor,
		_In_ HDC      hdcMonitor,
		_In_ LPRECT   lprcMonitor,
		_In_ LPARAM   dwData);
};

