#pragma once
#ifndef _INTERFACES
#define _INTERFACES
#include <windows.h>
//IStats ������������ ��� ��������� ����� ����������, � ����� 
//��� ����������� ���������� ��������� ������������ �������
DECLARE_INTERFACE_(IStats, IUnknown)
{
	STDMETHOD(DisplayStats)() PURE;
	STDMETHOD(GetName)(BSTR * Name) PURE;
};
//IEngine ���������� ��������� ���������. ����� �������� ���, 
//�������� �������� ������������ � ������� ��������
DECLARE_INTERFACE_(IFilling, IUnknown)
{
	STDMETHOD(Use)() PURE;
	STDMETHOD(GetMaxVolume)(int* maxVolume) PURE;
	STDMETHOD(GetCurVolume)(int* curVolume) PURE;
};
//ICreateCar ������������ ��� ���������� ����� ������������  
//������� � ������� ������������ ��������
DECLARE_INTERFACE_(ICreate, IUnknown)
{
	STDMETHOD(SetName)(BSTR Name) PURE;
	STDMETHOD(SetMaxVolume)(int maxVl) PURE;
};

#endif // _INTERFACES
