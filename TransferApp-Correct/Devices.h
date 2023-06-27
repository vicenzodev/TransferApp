#include <iostream>
#include <windows.h>
#include <fileapi.h>
#include <tchar.h>
#include <PortableDevice.h>
#include <PortableDeviceTypes.h>
#include <PortableDeviceApi.h>

class Devices{

public:
	Devices();

private:
	IPortableDeviceManager* pPortableDeviceManager;
	DWORD cPnPDeviceIDs;
	HRESULT devices;
};

Devices::Devices(){
	cPnPDeviceIDs = 0;
	devices = CoCreateInstance(
		CLSID_PortableDeviceManager,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pPortableDeviceManager));

	if (FAILED(devices)) {
		MessageBox(NULL, _T("Falhou em CoCreateInstance"), _T("TransferApp"), NULL);
	}

	if (SUCCEEDED(devices)) {
		devices = pPortableDeviceManager->GetDevices(NULL, &cPnPDeviceIDs);
		if (FAILED(devices)) {
			MessageBox(NULL,_T("Falhou em pegar o numero de dispositivos"),
				_T("TransferApp"), NULL);
		}
	}

	printf("\n%d Windows Portable Device(s) found on the system\n\n", cPnPDeviceIDs);
}