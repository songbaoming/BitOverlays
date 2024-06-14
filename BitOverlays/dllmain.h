// dllmain.h: 模块类的声明。

class CBitOverlaysModule : public ATL::CAtlDllModuleT<CBitOverlaysModule> {
public:
	DECLARE_LIBID(LIBID_BitOverlaysLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_BITOVERLAYS, "{59858dfb-6a7a-422b-af21-adbb360aa5c5}")
};

extern class CBitOverlaysModule _AtlModule;
