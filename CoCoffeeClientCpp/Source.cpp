#include "interfaces.h"
#include "iid.h"
#include <iostream>
using namespace std;

int main()
{
	CoInitialize(NULL); // This parameter is reserved, 
					   // and should be NULL

	HRESULT hr; 
	IClassFactory* pCF = NULL;
	ICreate* pICreateCoffee = NULL;
	IStats* pStats = NULL;
	IFilling* pFilling = NULL;

	hr = CoGetClassObject(CLSID_CoCoffee, CLSCTX_INPROC_SERVER,
		NULL, IID_IClassFactory, (void**)&pCF);

	// Make a CoCar & get ICreateCar.
	hr = pCF->CreateInstance(NULL, IID_ICreate,
		(void**)&pICreateCoffee);
	pCF->Release();

	if (SUCCEEDED(hr))
	{
		pICreateCoffee->SetMaxVolume(30);
		BSTR Name = SysAllocString(L"Shazzam!");
		pICreateCoffee->SetName(Name);
		SysFreeString(Name);

		// Now get IStats
		hr = pICreateCoffee->QueryInterface(IID_IStats,
			(void**)&pStats);
		pICreateCoffee->Release();
	}

	if (SUCCEEDED(hr))
	{
		// Show my coffee!
		pStats->DisplayStats();
		hr = pStats->QueryInterface(IID_IFilling,
			(void**)&pFilling);
	}

	if (SUCCEEDED(hr))
	{
		int maxVol = 0;
		int curVol = 0;
		pFilling->GetMaxVolume(&maxVol);
		pFilling->GetCurVolume(&curVol);

		do	// Zoom!
		{
			pFilling->Use();
			pFilling->GetCurVolume(&curVol);
			cout << "Volume is: " << curVol << endl;
		} while (curVol >= 10);

		// Gotta convert to char array.
		char buff[80];
		BSTR bstr;
		pStats->GetName(&bstr);
		WideCharToMultiByte(CP_ACP, NULL, bstr, -1, buff,
			80, NULL, NULL);
		cout << buff << " is Empty" << endl << endl;
		SysFreeString(bstr);

		if (pFilling) pFilling->Release();
		if (pStats) pStats->Release();
	}

	CoUninitialize();
	return 0;
}
