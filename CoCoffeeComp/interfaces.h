#pragma once
#ifndef _INTERFACES
#define _INTERFACES
#include <windows.h>
//IStats используетс€ дл€ получени€ имени автомобил€, а также 
//дл€ отображени€ параметров состо€ни€ реализуемого объекта
DECLARE_INTERFACE_(IStats, IUnknown)
{
	STDMETHOD(DisplayStats)() PURE;
	STDMETHOD(GetName)(BSTR * Name) PURE;
};
//IEngine моделирует поведение двигател€. ћожем ускор€ть его, 
//получать значени€ максимальной и текущей скорости
DECLARE_INTERFACE_(IFilling, IUnknown)
{
	STDMETHOD(Use)() PURE;
	STDMETHOD(GetMaxVolume)(int* maxVolume) PURE;
	STDMETHOD(GetCurVolume)(int* curVolume) PURE;
};
//ICreateCar используетс€ дл€ присвоени€ имени реализуемому  
//объекту и задани€ максимальной скорости
DECLARE_INTERFACE_(ICreate, IUnknown)
{
	STDMETHOD(SetName)(BSTR Name) PURE;
	STDMETHOD(SetMaxVolume)(int maxVl) PURE;
};

#endif // _INTERFACES
