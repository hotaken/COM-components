#pragma once
#include "interfaces.h"

const int MAX_SPEED = 1000;
const int MAX_NAME_LENGTH = 256;

class CoCar : public IEngine, public ICreateCar, public IStats, public IDispatch
{
public:
	CoCar();
	virtual ~CoCar();

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

	// IEngine
	STDMETHODIMP SpeedUp();
	STDMETHODIMP GetMaxSpeed(int* maxSpeed);
	STDMETHODIMP GetCurSpeed(int* curSpeed);

	// IStats
	STDMETHODIMP DisplayStats();
	STDMETHODIMP GetPetName(BSTR* petName);

	// ICreateCar
	STDMETHODIMP SetPetName(BSTR petName);
	STDMETHODIMP SetMaxSpeed(int maxSp);
private:
	ITypeInfo* _typeInfo{};
	DWORD m_refCount = 0;
	BSTR	m_petName; // Инициализация через SysAllocString(), 
	// удаление — через вызов SysFreeString()
	int		m_maxSpeed = 0; // Максимальная скорость
	int		m_currSpeed = 0; // Текущая скорость СоСаr
};

