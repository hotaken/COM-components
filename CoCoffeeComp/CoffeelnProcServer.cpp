#include <initguid.h>
#include <Windows.h>
#include "iid.h"
#include "CoCoffeeClassFactory.h"

ULONG g_lockCount = 0; // Количество блокировок сервера
ULONG g_objCount = 0; // Количество "живых" объектов в сервере

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	HRESULT hr;
	CoCoffeeClassFactory* pCFact = NULL;

	if (rclsid != CLSID_CoCoffee)
		return CLASS_E_CLASSNOTAVAILABLE;

	pCFact = new CoCoffeeClassFactory;

	hr = pCFact->QueryInterface(riid, ppv);

	if (FAILED(hr))
		delete pCFact;

	return hr;
}
STDAPI DllCanUnloadNow()
{
	if (g_lockCount == 0 && g_objCount == 0)
	{
		return S_OK;
	}
	else
		return S_FALSE;
}

