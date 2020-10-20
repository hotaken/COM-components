#include "CoCoffee.h"
#include <cstdio>
#include "iid.h"

extern DWORD g_objCount;
// Конструктор и деструктор 
CoCoffee::CoCoffee()
{
	m_Name = SysAllocString(L"Default Name");
	++g_objCount;
}

CoCoffee::~CoCoffee()
{
	--g_objCount;
	if (m_Name)
		SysFreeString(m_Name);
	MessageBoxA(NULL, "It is dead", "Destructor", MB_OK |
		MB_SETFOREGROUND);
}
HRESULT CoCoffee::Init()
{
	ITypeLib* pTypeLib;
	if (FAILED(LoadRegTypeLib(CLSID_CoCoffee, 1, 0, LANG_NEUTRAL, &pTypeLib)))
	{
		return E_FAIL;
	}

	const auto hr = pTypeLib->GetTypeInfoOfGuid(CLSID_CoCoffee, &_typeInfo);

	pTypeLib->Release();
	return hr;
}

// Реализация IFilling
STDMETHODIMP CoCoffee::Use()
{
	if (m_currVolume < 10) 
		return S_OK;
	m_currVolume -= 10;
	return S_OK;
}

STDMETHODIMP CoCoffee::GetMaxVolume(int* maxVolume)
{
	*maxVolume = m_maxVolume;
	return S_OK;
}

STDMETHODIMP CoCoffee::GetCurVolume(int* curVol)
{
	*curVol = m_currVolume;
	return S_OK;
}

// Реализация ICreate
STDMETHODIMP CoCoffee::SetName(BSTR Name)
{
	SysReAllocString(&m_Name, Name);
	return S_OK;
}

STDMETHODIMP CoCoffee::SetMaxVolume(int maxVol)
{
	if (maxVol < MAX_VOLUME)
	{
		m_maxVolume = maxVol;
		m_currVolume = maxVol;
	}
		
	return S_OK;
}

// Возвращает клиенту копию внутреннего буфера BSTR 
STDMETHODIMP CoCoffee::GetName(BSTR* Name)
{
	*Name = SysAllocString(m_Name);
	return S_OK;
}
// Информация о СоСаr помещается в блоки сообщений
STDMETHODIMP CoCoffee::DisplayStats()
{
	// Need to transfer a BSTR to a char array.
	char buff[MAX_NAME_LENGTH];
	WideCharToMultiByte(CP_ACP, NULL, m_Name, -1, buff,
		MAX_NAME_LENGTH, NULL, NULL);

	MessageBoxA(NULL,  buff, "Name", MB_OK | MB_SETFOREGROUND);
	memset(buff, 0, sizeof(buff));
	sprintf_s(buff, "%d", m_maxVolume);
	MessageBoxA(NULL,  buff, "Max Volume", MB_OK |
		MB_SETFOREGROUND);
	return S_OK;
}



STDMETHODIMP_(DWORD) CoCoffee::AddRef()
{
	++m_refCount;
	return m_refCount;
}

STDMETHODIMP_(DWORD) CoCoffee::Release()
{
	if (--m_refCount == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_refCount;
}
STDMETHODIMP CoCoffee::QueryInterface(REFIID riid, void** pIFace)
{
	// Which aspect of me do they want?
	if (riid == IID_IUnknown)
	{
		*pIFace = (IUnknown*)(IFilling*)this;
		MessageBoxA(NULL, "Handed out IUnknown", "QI", MB_OK |
			MB_SETFOREGROUND);
	}
	else if (riid == IID_IDispatch)
	{
		*pIFace = (IDispatch*)this;
	}
	else if (riid == IID_IFilling)
	{
		*pIFace = (IFilling*)this;
		MessageBoxA(NULL, "Handed out IFilling", "QI", MB_OK |
			MB_SETFOREGROUND);
	}

	else if (riid == IID_IStats)
	{
		*pIFace = (IStats*)this;
		MessageBoxA(NULL, "Handed out IStats", "QI", MB_OK |
			MB_SETFOREGROUND);
	}

	else if (riid == IID_ICreate)
	{
		*pIFace = (ICreate*)this;
		MessageBoxA(NULL, "Handed out ICreate", "QI", MB_OK |
			MB_SETFOREGROUND);
	}
	else
	{
		*pIFace = NULL;
		return E_NOINTERFACE;
	}

	((IUnknown*)(*pIFace))->AddRef();
	return S_OK;
}
STDMETHODIMP CoCoffee::GetTypeInfoCount(UINT* pctinfo)
{
	*pctinfo = 1;
	return S_OK;
}
STDMETHODIMP CoCoffee::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo)
{
	*ppTInfo = nullptr;
	if (iTInfo)
	{
		return DISP_E_BADINDEX;
	}

	_typeInfo->AddRef();
	*ppTInfo = _typeInfo;
	return S_OK;
}

HRESULT CoCoffee::GetIDsOfNames(const IID& riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId)
{
	if (riid != IID_NULL)
	{
		return DISP_E_UNKNOWNINTERFACE;
	}

	return DispGetIDsOfNames(_typeInfo, rgszNames, cNames, rgDispId);
}

HRESULT CoCoffee::Invoke(DISPID dispIdMember, const IID& riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams,
	VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
	if (riid != IID_NULL)
	{
		return DISP_E_UNKNOWNINTERFACE;
	}

	return DispInvoke(this, _typeInfo, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
}

