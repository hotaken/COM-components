#include "CoCar.h"
#include <cstdio>
#include "iid.h"

extern DWORD g_objCount;
// Конструктор и деструктор СоСаr
CoCar::CoCar()
{
	m_petName = SysAllocString(L"Default Name");
	++g_objCount;
}

CoCar::~CoCar()
{
	--g_objCount;
	if (m_petName)
		SysFreeString(m_petName);
	MessageBoxA(NULL, "It is dead", "Destructor", MB_OK |
		MB_SETFOREGROUND);
}
HRESULT CoCar::Init()
{
	ITypeLib* pTypeLib;
	if (FAILED(LoadRegTypeLib(CLSID_CoCar, 1, 0, LANG_NEUTRAL, &pTypeLib)))
	{
		return E_FAIL;
	}

	const auto hr = pTypeLib->GetTypeInfoOfGuid(CLSID_CoCar, &_typeInfo);

	pTypeLib->Release();
	return hr;
}

// Реализация IEngine
STDMETHODIMP CoCar::SpeedUp()
{
	m_currSpeed += 10;
	return S_OK;
}

STDMETHODIMP CoCar::GetMaxSpeed(int* maxSpeed)
{
	*maxSpeed = m_maxSpeed;
	return S_OK;
}

STDMETHODIMP CoCar::GetCurSpeed(int* curSpeed)
{
	*curSpeed = m_currSpeed;
	return S_OK;
}

// Реализация ICreateCar
STDMETHODIMP CoCar::SetPetName(BSTR petName)
{
	SysReAllocString(&m_petName, petName);
	return S_OK;
}

STDMETHODIMP CoCar::SetMaxSpeed(int maxSp)
{
	if (maxSp < MAX_SPEED)
		m_maxSpeed = maxSp;
	return S_OK;
}

// Возвращает клиенту копию внутреннего буфера BSTR 
STDMETHODIMP CoCar::GetPetName(BSTR* petName)
{
	*petName = SysAllocString(m_petName);
	return S_OK;
}
// Информация о СоСаr помещается в блоки сообщений
STDMETHODIMP CoCar::DisplayStats()
{
	// Need to transfer a BSTR to a char array.
	char buff[MAX_NAME_LENGTH];
	WideCharToMultiByte(CP_ACP, NULL, m_petName, -1, buff,
		MAX_NAME_LENGTH, NULL, NULL);

	MessageBoxA(NULL,  buff, "Name", MB_OK | MB_SETFOREGROUND);
	memset(buff, 0, sizeof(buff));
	sprintf_s(buff, "%d", m_maxSpeed);
	MessageBoxA(NULL,  buff, "Max Speed", MB_OK |
		MB_SETFOREGROUND);
	return S_OK;
}



STDMETHODIMP_(DWORD) CoCar::AddRef()
{
	++m_refCount;
	return m_refCount;
}

STDMETHODIMP_(DWORD) CoCar::Release()
{
	if (--m_refCount == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_refCount;
}
STDMETHODIMP CoCar::QueryInterface(REFIID riid, void** pIFace)
{
	// Which aspect of me do they want?
	if (riid == IID_IUnknown)
	{
		*pIFace = (IUnknown*)(IEngine*)this;
		MessageBoxA(NULL, "Handed out IUnknown", "QI", MB_OK |
			MB_SETFOREGROUND);
	}
	else if (riid == IID_IDispatch)
	{
		*pIFace = (IDispatch*)this;
	}
	else if (riid == IID_IEngine)
	{
		*pIFace = (IEngine*)this;
		MessageBoxA(NULL, "Handed out IEngine", "QI", MB_OK |
			MB_SETFOREGROUND);
	}

	else if (riid == IID_IStats)
	{
		*pIFace = (IStats*)this;
		MessageBoxA(NULL, "Handed out IStats", "QI", MB_OK |
			MB_SETFOREGROUND);
	}

	else if (riid == IID_ICreateCar)
	{
		*pIFace = (ICreateCar*)this;
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
STDMETHODIMP CoCar::GetTypeInfoCount(UINT* pctinfo)
{
	*pctinfo = 1;
	return S_OK;
}
STDMETHODIMP CoCar::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo)
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

HRESULT CoCar::GetIDsOfNames(const IID& riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId)
{
	if (riid != IID_NULL)
	{
		return DISP_E_UNKNOWNINTERFACE;
	}

	return DispGetIDsOfNames(_typeInfo, rgszNames, cNames, rgDispId);
}

HRESULT CoCar::Invoke(DISPID dispIdMember, const IID& riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams,
	VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
	if (riid != IID_NULL)
	{
		return DISP_E_UNKNOWNINTERFACE;
	}

	return DispInvoke(this, _typeInfo, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
}

