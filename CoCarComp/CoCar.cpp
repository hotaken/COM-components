#include "CoCar.h"
#include <cstdio>
#include "iid.h"

extern DWORD g_objCount;
// Конструктор и деструктор СоСаr
CoCar::CoCar() : m_refCount(0), m_currSpeed(0), m_maxSpeed(0)
{
	m_petName = SysAllocString(L"Default Pet Name");
	++g_objCount;
}

CoCar::~CoCar()
{
	--g_objCount;
	if (m_petName)
		SysFreeString(m_petName);
	MessageBoxA(NULL, "CoCar is dead", "Destructor", MB_OK |
		MB_SETFOREGROUND);
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

	MessageBoxA(NULL,  buff, "Pet Name", MB_OK | MB_SETFOREGROUND);
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
		MessageBoxA(NULL, "Handed out ICreateCar", "QI", MB_OK |
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

