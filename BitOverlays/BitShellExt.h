#pragma once
#include "resource.h" // 主符号

#include "BitOverlays_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;

class CBitShellExt : public IShellIconOverlayIdentifier {
public:
	CBitShellExt(WORD machine);

	virtual HRESULT STDMETHODCALLTYPE IsMemberOf(
		/* [string][in] */ __RPC__in_string LPCWSTR pwszPath,
		/* [in] */ DWORD dwAttrib);

	virtual HRESULT STDMETHODCALLTYPE GetOverlayInfo(
		/* [size_is][string][out] */ __RPC__out_ecount_full_string(cchMax) LPWSTR pwszIconFile,
		/* [in] */ int cchMax,
		/* [out] */ __RPC__out int *pIndex,
		/* [out] */ __RPC__out DWORD *pdwFlags);

	virtual HRESULT STDMETHODCALLTYPE GetPriority(
		/* [out] */ __RPC__out int *pPriority);

private:
	WORD m_machine;
};

// CBitShellExt32

class ATL_NO_VTABLE CBitShellExt32 : public CComObjectRootEx<CComSingleThreadModel>,
									 public CComCoClass<CBitShellExt32, &CLSID_BitShellExt32>,
									 public IDispatchImpl<IBitShellExt32, &IID_IBitShellExt32, &LIBID_BitOverlaysLib, /*wMajor =*/1, /*wMinor =*/0>,
									 public CBitShellExt {
public:
	CBitShellExt32()
		: CBitShellExt(IMAGE_FILE_MACHINE_I386)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(106)

	BEGIN_COM_MAP(CBitShellExt32)
	COM_INTERFACE_ENTRY(IBitShellExt32)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellIconOverlayIdentifier)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
};

OBJECT_ENTRY_AUTO(__uuidof(BitShellExt32), CBitShellExt32)

// CBitShellExt64

class ATL_NO_VTABLE CBitShellExt64 : public CComObjectRootEx<CComSingleThreadModel>,
									 public CComCoClass<CBitShellExt64, &CLSID_BitShellExt64>,
									 public IDispatchImpl<IBitShellExt64, &IID_IBitShellExt64, &LIBID_BitOverlaysLib, /*wMajor =*/1, /*wMinor =*/0>,
									 public CBitShellExt {
public:
	CBitShellExt64()
		: CBitShellExt(IMAGE_FILE_MACHINE_AMD64)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(107)

	BEGIN_COM_MAP(CBitShellExt64)
	COM_INTERFACE_ENTRY(IBitShellExt64)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellIconOverlayIdentifier)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
};

OBJECT_ENTRY_AUTO(__uuidof(BitShellExt64), CBitShellExt64)
