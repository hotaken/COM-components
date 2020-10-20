#include "CoCoffeeClassFactory.h"
#include "CoCoffee.h"

extern DWORD g_lockCount;
extern DWORD g_objCount;

STDMETHODIMP_(ULONG) CoCoffeeClassFactory::AddRef()
{
    return ++m_refCount;

}

STDMETHODIMP_(ULONG) CoCoffeeClassFactory::Release()
{
    if (--m_refCount == 0)
    {
        delete this;
        return 0;
    }
    return m_refCount;
}

STDMETHODIMP CoCoffeeClassFactory::QueryInterface(REFIID riid, void** ppv)
{
    // Which aspect of me do they want?
    if (riid == IID_IUnknown)
    {
        *ppv = (IUnknown*)this;
    }
    else if (riid == IID_IClassFactory)
    {
        *ppv = (IClassFactory*)this;
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    ((IUnknown*)(*ppv))->AddRef();
    return S_OK;
}

STDMETHODIMP CoCoffeeClassFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, void** ppv)
{
    if (pUnkOuter != NULL)
        return CLASS_E_NOAGGREGATION;

    CoCoffee* pCoffeeObj = NULL;
    HRESULT hr;

    pCoffeeObj = new CoCoffee;

    if (pCoffeeObj == nullptr)
    {
        return E_OUTOFMEMORY;
    }

    pCoffeeObj->Init();
    hr = pCoffeeObj->QueryInterface(riid, ppv);

    if (FAILED(hr))
        delete pCoffeeObj;

    return hr;    // S_OK or E_NOINTERFACE.

}



CoCoffeeClassFactory::CoCoffeeClassFactory()
{
    m_refCount = 0;
    g_objCount++;
}

CoCoffeeClassFactory::~CoCoffeeClassFactory()
{
    g_objCount--;
}

STDMETHODIMP CoCoffeeClassFactory::LockServer(BOOL fLock)
{
    if (fLock)
        ++g_lockCount;
    else
        --g_lockCount;

    return S_OK;
}