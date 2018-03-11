#include "stdafx.h"
#include "MonitorList.h"


MonitorList::MonitorList()
{
	BOOL ok = EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc, (LPARAM)this);
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
	MonitorList *This = (MonitorList *)dwData;

	BOOL ok = TRUE;

	MonitorInformation i;
	if (lprcMonitor != nullptr)
	    i.area = *lprcMonitor;
	i.monitor = hMonitor;
	
	This->information.push_back(i);
	
	return(ok);
}