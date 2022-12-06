#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <SETUPAPI.H>

//----------------------------------------------
#define INPUT_REPORT_SIZE	64
#define OUTPUT_REPORT_SIZE	64
//----------------------------------------------

typedef struct _HIDD_ATTRIBUTES {
	ULONG   Size; // = sizeof (struct _HIDD_ATTRIBUTES)
	USHORT  VendorID;
	USHORT  ProductID;
	USHORT  VersionNumber;
} HIDD_ATTRIBUTES, *PHIDD_ATTRIBUTES;

typedef VOID(__stdcall *PHidD_GetProductString)(HANDLE, PVOID, ULONG);
typedef VOID(__stdcall *PHidD_GetHidGuid)(LPGUID);
typedef BOOLEAN(__stdcall *PHidD_GetAttributes)(HANDLE, PHIDD_ATTRIBUTES);
typedef BOOLEAN(__stdcall *PHidD_SetFeature)(HANDLE, PVOID, ULONG);
typedef BOOLEAN(__stdcall *PHidD_GetFeature)(HANDLE, PVOID, ULONG);

//----------------------------------------------

HINSTANCE                       hHID = NULL;
PHidD_GetProductString          HidD_GetProductString = NULL;
PHidD_GetHidGuid                HidD_GetHidGuid = NULL;
PHidD_GetAttributes             HidD_GetAttributes = NULL;
PHidD_SetFeature                HidD_SetFeature = NULL;
PHidD_GetFeature                HidD_GetFeature = NULL;
HANDLE                          DeviceHandle = INVALID_HANDLE_VALUE;

unsigned int moreHIDDevices = TRUE;
unsigned int HIDDeviceFound = FALSE;

unsigned int terminaAbruptaEInstantaneamenteElPrograma = 0;

void Load_HID_Library(void) {
	hHID = LoadLibrary("HID.DLL");
	if (!hHID) {
		printf("Failed to load HID.DLL\n");
		return;
	}

	HidD_GetProductString = (PHidD_GetProductString)GetProcAddress(hHID, "HidD_GetProductString");
	HidD_GetHidGuid = (PHidD_GetHidGuid)GetProcAddress(hHID, "HidD_GetHidGuid");
	HidD_GetAttributes = (PHidD_GetAttributes)GetProcAddress(hHID, "HidD_GetAttributes");
	HidD_SetFeature = (PHidD_SetFeature)GetProcAddress(hHID, "HidD_SetFeature");
	HidD_GetFeature = (PHidD_GetFeature)GetProcAddress(hHID, "HidD_GetFeature");

	if (!HidD_GetProductString
		|| !HidD_GetAttributes
		|| !HidD_GetHidGuid
		|| !HidD_SetFeature
		|| !HidD_GetFeature) {
		printf("Couldn't find one or more HID entry points\n");
		return;
	}
}

int Open_Device(unsigned short int RICH_VENDOR_ID, unsigned short int RICH_USBHID_GENIO_ID) {
	HDEVINFO							DeviceInfoSet;
	GUID								InterfaceClassGuid;
	SP_DEVICE_INTERFACE_DATA			DeviceInterfaceData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	pDeviceInterfaceDetailData;
	HIDD_ATTRIBUTES						Attributes;
	DWORD								Result;
	DWORD								MemberIndex = 0;
	DWORD								Required;

	//Validar si se "cargó" la biblioteca (DLL)
	if (!hHID)
		return (0);

	//Obtener el Globally Unique Identifier (GUID) para dispositivos HID
	HidD_GetHidGuid(&InterfaceClassGuid);
	//Sacarle a Windows la información sobre todos los dispositivos HID instalados y activos en el sistema
	// ... almacenar esta información en una estructura de datos de tipo HDEVINFO
	DeviceInfoSet = SetupDiGetClassDevs(&InterfaceClassGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
	if (DeviceInfoSet == INVALID_HANDLE_VALUE)
		return (0);

	//Obtener la interfaz de comunicación con cada uno de los dispositivos para preguntarles información específica
	DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
	while (!HIDDeviceFound) {
		// ... utilizando la variable MemberIndex ir preguntando dispositivo por dispositivo ...
		moreHIDDevices = SetupDiEnumDeviceInterfaces(DeviceInfoSet, NULL, &InterfaceClassGuid,
			MemberIndex, &DeviceInterfaceData);
		if (!moreHIDDevices) {
			// ... si llegamos al fin de la lista y no encontramos al dispositivo ==> terminar y marcar error
			SetupDiDestroyDeviceInfoList(DeviceInfoSet);
			return (0); //No more devices found
		}
		else {
			//Necesitamos preguntar, a través de la interfaz, el PATH del dispositivo, para eso ...
			// ... primero vamos a ver cuántos caracteres se requieren (Required)
			Result = SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, NULL, 0, &Required, NULL);
			pDeviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Required);
			if (pDeviceInterfaceDetailData == NULL) {
				printf("Error en SetupDiGetDeviceInterfaceDetail\n");
				return (0);
			}
			//Ahora si, ya que el "buffer" fue preparado (pDeviceInterfaceDetailData{DevicePath}), vamos a preguntar PATH
			pDeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
			Result = SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &DeviceInterfaceData, pDeviceInterfaceDetailData,
				Required, NULL, NULL);
			if (!Result) {
				printf("Error en SetupDiGetDeviceInterfaceDetail\n");
				free(pDeviceInterfaceDetailData);
				return(0);
			}
			//Para este momento ya sabemos el PATH del dispositivo, ahora hay que preguntarle ...
			// ... su VID y PID, para ver si es con quien nos interesa comunicarnos
			printf("Found? ==> ");
			printf("Device: %s\n", pDeviceInterfaceDetailData->DevicePath);

			//Obtener un "handle" al dispositivo
			DeviceHandle = CreateFile(pDeviceInterfaceDetailData->DevicePath,
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				(LPSECURITY_ATTRIBUTES)NULL,
				OPEN_EXISTING,
				0,
				NULL);

			if (DeviceHandle == INVALID_HANDLE_VALUE) {
				printf("¡¡¡Error en el CreateFile!!!\n");
			}
			else {
				//Preguntar por los atributos del dispositivo
				Attributes.Size = sizeof(Attributes);
				Result = HidD_GetAttributes(DeviceHandle, &Attributes);
				if (!Result) {
					printf("Error en HIdD_GetAttributes\n");
					CloseHandle(DeviceHandle);
					free(pDeviceInterfaceDetailData);
					return(0);
				}
				//Analizar los atributos del dispositivo para verificar el VID y PID
				printf("MemberIndex=%d, VID=%04x, PID=%04x\n", MemberIndex, Attributes.VendorID, Attributes.ProductID);
				printf("Comparing to VID=%04x, PID=%04x\n", RICH_VENDOR_ID, RICH_USBHID_GENIO_ID);

				if ((Attributes.VendorID == RICH_VENDOR_ID) && (Attributes.ProductID == RICH_USBHID_GENIO_ID)) {
					printf("USB/HID GenIO ==> ");
					printf("Device: %s\n", pDeviceInterfaceDetailData->DevicePath);
					HIDDeviceFound = TRUE;
				}
				else
					CloseHandle(DeviceHandle);

			}
			MemberIndex++;
			free(pDeviceInterfaceDetailData);
			if (HIDDeviceFound) {
				printf("Dispositivo HID solicitado ... ¡¡¡localizado!!!, presione <ENTER>\n");
				getchar();
			}
		}
	}
	return(1);
}


int modifyLed(numLed, valueLed) {
	DWORD BytesRead = 0;
	DWORD BytesWritten = 0;
	unsigned char reporteSalida[OUTPUT_REPORT_SIZE + 1];
	int status = 0;
	reporteSalida[0] = 0x00;
	reporteSalida[1] = numLed;
	reporteSalida[2] = valueLed;
	status = WriteFile(DeviceHandle, reporteSalida, OUTPUT_REPORT_SIZE + 1, &BytesWritten, NULL);
	if (!status)
		printf("Error en el WriteFile %d %d\n", GetLastError(), BytesWritten);
	else
		printf("Se envio al LED %d el dato %d\n", numLed, valueLed);
	return status;
}

int leerMatriculas() {
	DWORD BytesRead = 0;
	DWORD BytesWritten = 0;
	unsigned char reporteEntrada[INPUT_REPORT_SIZE + 1];
	unsigned char reporteSalida[OUTPUT_REPORT_SIZE + 1];
	int status = 0;
	reporteSalida[0] = 0x00;
	reporteSalida[1] = 0x82;
	reporteSalida[2] = 0;

	status = WriteFile(DeviceHandle, reporteSalida, OUTPUT_REPORT_SIZE + 1, &BytesWritten, NULL);
	if (!status)
		printf("Error en el WriteFile %d %d\n", GetLastError(), BytesWritten);
	memset(&reporteEntrada, 0, INPUT_REPORT_SIZE + 1);
	status = ReadFile(DeviceHandle, reporteEntrada, INPUT_REPORT_SIZE + 1, &BytesRead, NULL);
	if (!status)
		printf("Error en el ReadFile: %d\n", GetLastError());
	else {
		char frase[INPUT_REPORT_SIZE];
		int i;
		for (i = 0; i < INPUT_REPORT_SIZE; i++)
		{
			if (reporteEntrada[i + 2] == 0) break;
			frase[i] = (char)reporteEntrada[i + 2];

		}
		printf("Duenos: %.*s\n", i, frase);
	}
	return status;
}


int leerSwitches() {
	DWORD BytesRead = 0;
	DWORD BytesWritten = 0;
	unsigned char reporteEntrada[INPUT_REPORT_SIZE + 1];
	unsigned char reporteSalida[OUTPUT_REPORT_SIZE + 1];
	int status = 0;

	reporteSalida[0] = 0x00;
	reporteSalida[1] = 0x81;
	reporteSalida[2] = 0;

	status = WriteFile(DeviceHandle, reporteSalida, OUTPUT_REPORT_SIZE + 1, &BytesWritten, NULL);
	if (!status)
		printf("Error en el WriteFile %d %d\n", GetLastError(), BytesWritten);

	memset(&reporteEntrada, 0, INPUT_REPORT_SIZE + 1);
	status = ReadFile(DeviceHandle, reporteEntrada, INPUT_REPORT_SIZE + 1, &BytesRead, NULL);
	if (!status)
		printf("Error en el ReadFile: %d\n", GetLastError());
	else
		printf("Switches: %d %d %d\n", reporteEntrada[2],
			reporteEntrada[3],
			reporteEntrada[4]);

	return status;
}

void Close_Device(void) {
	if (DeviceHandle != NULL) {
		CloseHandle(DeviceHandle);
		DeviceHandle = NULL;
	}
}
int Touch_Device(void) {
	int dato = 1;
	int numLED = 1;

	if (DeviceHandle == NULL)	//Validar que haya comunicacion con el dispositivo
		return 0;

	int input;
	printf("\n\n1 - Modificar Leds\n");
	printf("2 - Leer Swtiches\n");
	printf("3 - Leer Dueños\n");
	printf("4 - Salir\n");
	printf("Que Hago? = ");
	scanf_s("%d", &input);

	switch (input)
	{
	case 1:
		printf("Numero de LED ( 1 2 3 ) = ");
		scanf_s("%d", &numLED);
		printf("Valor LED 0 o 1 = ");
		scanf_s("%d", &dato);
		modifyLed(numLED, dato);
		break;
	case 2:
		leerSwitches();
		break;
	case 3:
		leerMatriculas();
		break;
	default:
		return 0;
		break;
	}

	return 1;
}

void main() {
	Load_HID_Library();
	unsigned short int vendorId;
	unsigned short int productId;
	printf("Vendor Id = ");
	scanf_s("%hu", &vendorId);
	printf("Product Id = ");
	scanf_s("%x", &productId);
	if (Open_Device(vendorId, productId)) {
		while ((!_kbhit())
			&& (!terminaAbruptaEInstantaneamenteElPrograma)) {
			int result = Touch_Device();
			if (!result) {
				printf("Error\n");
				break;
			}
			Sleep(1000);
		}
	}
	else {
		printf(">No lo encontre :(\n");
	}
	Close_Device();
}