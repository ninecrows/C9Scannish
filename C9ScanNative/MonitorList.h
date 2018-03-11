#pragma once

#include <windows.h>
#include <vector>

struct MonitorInformation
{
	HMONITOR monitor;
	RECT area;
};

class MonitorList
{
public:
	MonitorList();
	~MonitorList();

	// Information on each monitor in the system.
	std::vector<MonitorInformation> information;

private:
	static BOOL CALLBACK MonitorList::MonitorEnumProc(
		_In_ HMONITOR hMonitor,
		_In_ HDC      hdcMonitor,
		_In_ LPRECT   lprcMonitor,
		_In_ LPARAM   dwData);
};

