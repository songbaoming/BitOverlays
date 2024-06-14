#include "pch.h"
#include "BitShellExt.h"

extern TCHAR g_ModulePath[MAX_PATH];

CBitShellExt::CBitShellExt(WORD machine)
	: m_machine(machine)
{
}

HRESULT STDMETHODCALLTYPE CBitShellExt::IsMemberOf(
	/* [string][in] */ __RPC__in_string LPCWSTR pwszPath,
	/* [in] */ DWORD dwAttrib)
{
	HRESULT hRef = S_FALSE;
	auto pExt = PathFindExtension(pwszPath);
	if (_tcsicmp(pExt, TEXT(".exe")) && _tcsicmp(pExt, TEXT(".dll")) && _tcsicmp(pExt, TEXT(".sys")))
		return hRef;
	HANDLE hFile = CreateFile(pwszPath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL, OPEN_EXISTING, 0, NULL);
	do {
		if (hFile == INVALID_HANDLE_VALUE)
			break;
		DWORD bytes;
		byte buff[512];
		auto bRes = ReadFile(hFile, buff, sizeof(buff), &bytes, NULL);
		if (!bRes || bytes < sizeof(buff) || buff[0] != 'M' || buff[1] != 'Z')
			break;
		auto dos = (_IMAGE_DOS_HEADER *)buff;
		_IMAGE_NT_HEADERS *nthdr = nullptr;
		if (dos->e_lfanew > sizeof(buff) - 8) {
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dos->e_lfanew, nullptr, FILE_BEGIN))
				break;
			bRes = ReadFile(hFile, buff, sizeof(buff), &bytes, NULL);
			if (!bRes || bytes < sizeof(buff))
				break;
			nthdr = (_IMAGE_NT_HEADERS *)buff;
		} else
			nthdr = (_IMAGE_NT_HEADERS *)(buff + dos->e_lfanew);
		if (nthdr && nthdr->Signature == 0x4550 && m_machine == nthdr->FileHeader.Machine) {
			hRef = S_OK;
		}
	} while (false);
	if (hFile != INVALID_HANDLE_VALUE)
		CloseHandle(hFile);
	return hRef;
}

HRESULT STDMETHODCALLTYPE CBitShellExt::GetOverlayInfo(
	/* [size_is][string][out] */ __RPC__out_ecount_full_string(cchMax) LPWSTR pwszIconFile,
	/* [in] */ int cchMax,
	/* [out] */ __RPC__out int *pIndex,
	/* [out] */ __RPC__out DWORD *pdwFlags)
{
	switch (m_machine) {
	case IMAGE_FILE_MACHINE_I386:
		*pIndex = 1;
		_tcscpy_s(pwszIconFile, cchMax, g_ModulePath);
		break;
	case IMAGE_FILE_MACHINE_AMD64:
		*pIndex = 0;
		_tcscpy_s(pwszIconFile, cchMax, g_ModulePath);
		break;
	default:
		return S_FALSE;
	}

	*pdwFlags = ISIOI_ICONFILE | ISIOI_ICONINDEX;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CBitShellExt::GetPriority(
	/* [out] */ __RPC__out int *pPriority)
{
	*pPriority = 0;
	return S_OK;
}