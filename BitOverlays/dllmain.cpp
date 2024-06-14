// dllmain.cpp: DllMain 的实现。

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "BitOverlays_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CBitOverlaysModule _AtlModule;
TCHAR g_ModulePath[MAX_PATH];
// DLL 入口点
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(hInstance, dwReason, lpReserved))
		return FALSE;
#endif
	GetModuleFileName(hInstance, g_ModulePath, ARRAYSIZE(g_ModulePath));
	return _AtlModule.DllMain(dwReason, lpReserved);
}
