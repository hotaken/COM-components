#pragma once
#include "interfaces.h"

const int MAX_VOLUME = 1000;
const int MAX_NAME_LENGTH = 256;

class CoCoffee : public IFilling, public ICreate, public IStats, public IDispatch
{
public:
	CoCoffee();
	virtual ~CoCoffee();

	HRESULT Init();

	// IDispatch
	STDMETHODIMP GetTypeInfoCount(UINT* pctinfo);
	STDMETHODIMP GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo);
	STDMETHODIMP GetIDsOfNames(const IID& riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId);
	STDMETHODIMP Invoke(DISPID dispIdMember, const IID& riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams,
		VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr);

	// IUnknown
	STDMETHODIMP QueryInterface(REFIID riid, void** pIFace);
	STDMETHODIMP_(DWORD)AddRef();
	STDMETHODIMP_(DWORD)Release();

	// IFilling
	STDMETHODIMP Use();
	STDMETHODIMP GetMaxVolume(int* maxSpeed);
	STDMETHODIMP GetCurVolume(int* curSpeed);

	// IStats
	STDMETHODIMP DisplayStats();
	STDMETHODIMP GetName(BSTR* petName);

	// ICreate
	STDMETHODIMP SetName(BSTR petName);
	STDMETHODIMP SetMaxVolume(int maxSp);
private:
	ITypeInfo* _typeInfo{};
	DWORD m_refCount = 0;
	BSTR	m_Name; // Инициализация через SysAllocString(), 
	// удаление — через вызов SysFreeString()
	int		m_maxVolume = 0; // Максимальная скорость
	int		m_currVolume = 0; // Текущая скорость СоСаr
};

