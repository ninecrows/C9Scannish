#include "stdafx.h"
#include "MonitorList.h"


MonitorList::MonitorList()
{
	BOOL ok = EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc, 0);
}


MonitorList::~MonitorList()
{
}

BOOL CALLBACK MonitorList::MonitorEnumProc(
	_In_ HMONITOR hMonitor,
	_In_ HDC      hdcMonitor,
	_In_ LPRECT   lprcMonitor,
	_In_ LPARAM   dwData
)
{
	BOOL ok = TRUE;

	return(ok);
}