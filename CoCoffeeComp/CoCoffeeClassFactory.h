#pragma once
#include <windows.h>
class CoCoffeeClassFactory : public IClassFactory
{
public:
    CoCoffeeClassFactory();
    virtual ~CoCoffeeClassFactory();

    // IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, void** pIFace);
    STDMETHODIMP_(DWORD)AddRef();
    STDMETHODIMP_(DWORD)Release();

    // ICF
    STDMETHODIMP LockServer(BOOL fLock);
    STDMETHODIMP CreateInstance(LPUNKNOWN pUnkOuter,
        REFIID riid, void** ppv);

private:
    DWORD    m_refCount;
};