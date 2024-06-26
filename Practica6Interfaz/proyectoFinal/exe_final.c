#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <SETUPAPI.H>

//----------------------------------------------
#define RICH_VENDOR_ID			0x0000
#define RICH_USBHID_GENIO_ID	0x2022

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

int Open_Device(void) {
	HDEVINFO							DeviceInfoSet;
	GUID								InterfaceClassGuid;
	SP_DEVICE_INTERFACE_DATA			DeviceInterfaceData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	pDeviceInterfaceDetailData;
	HIDD_ATTRIBUTES						Attributes;
	DWORD								Result;
	DWORD								MemberIndex = 0;
	DWORD								Required;

	//Validar si se "carg�" la biblioteca (DLL)
	if (!hHID)
		return (0);

	//Obtener el Globally Unique Identifier (GUID) para dispositivos HID
	HidD_GetHidGuid(&InterfaceClassGuid);
	//Sacarle a Windows la informaci�n sobre todos los dispositivos HID instalados y activos en el sistema
	// ... almacenar esta informaci�n en una estructura de datos de tipo HDEVINFO
	DeviceInfoSet = SetupDiGetClassDevs(&InterfaceClassGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
	if (DeviceInfoSet == INVALID_HANDLE_VALUE)
		return (0);

	//Obtener la interfaz de comunicaci�n con cada uno de los dispositivos para preguntarles informaci�n espec�fica
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
			//Necesitamos preguntar, a trav�s de la interfaz, el PATH del dispositivo, para eso ...
			// ... primero vamos a ver cu�ntos caracteres se requieren (Required)
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
				printf("���Error en el CreateFile!!!\n");
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
				printf("MemberIndex=%d,VID=%04x,PID=%04x\n", MemberIndex, Attributes.VendorID, Attributes.ProductID);
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
				printf("Dispositivo HID solicitado ... ���localizado!!!, presione <ENTER>\n");
				getchar();
			}
		}
	}
	return(1);
}

void Close_Device(void) {
	if (DeviceHandle != NULL) {
		CloseHandle(DeviceHandle);
		DeviceHandle = NULL;
	}
}

void Touch_Device(void) {
	DWORD BytesRead = 0;
	DWORD BytesWritten = 0;
	unsigned char reporteEntrada[INPUT_REPORT_SIZE + 1];
	unsigned char reporteSalida[OUTPUT_REPORT_SIZE + 1];
	int status = 0;
	static unsigned char dato = 0x01;
	static unsigned char numLED = 1;
	int* dato2 = NULL;
	int d1, d2, respuesta;
	int* d1ptr, *d2ptr, *rsptptr;
	float df1, df2, respuestaf;
	float* df1ptr, *df2ptr, *rsptfptr;

	if (DeviceHandle == NULL)	//Validar que haya comunicacion con el dispositivo
		return 0;

	df1 = -54.54;
	df2 = 200.8;
	printf("Voy a sumar %f + %f = ", df1, df2);
	reporteSalida[0] = 0x00;	//Dummy
	reporteSalida[1] = 0x20;	//SUMA
	df1ptr = (float*)&reporteSalida[2];
	*df1ptr = df1;
	df2ptr = (float*)&reporteSalida[6];
	*df2ptr = df2;
	status = WriteFile(DeviceHandle, reporteSalida, OUTPUT_REPORT_SIZE + 1, &BytesWritten, NULL);
	memset(&reporteEntrada, 0, INPUT_REPORT_SIZE + 1);
	status = ReadFile(DeviceHandle, reporteEntrada, INPUT_REPORT_SIZE + 1, &BytesRead, NULL);
	rsptfptr = (float*)&reporteEntrada[2];
	respuestaf = *rsptfptr;
	printf("%f\n", respuestaf);

	df1 = 782.7;
	df2 = 934.5;
	printf("Voy a restar %f - %f = ", df1, df2);
	reporteSalida[0] = 0x00;	//Dummy
	reporteSalida[1] = 0x21;	//Resta
	df1ptr = (float*)&reporteSalida[2];
	*df1ptr = df1;
	df2ptr = (float*)&reporteSalida[6];
	*df2ptr = df2;
	status = WriteFile(DeviceHandle, reporteSalida, OUTPUT_REPORT_SIZE + 1, &BytesWritten, NULL);
	memset(&reporteEntrada, 0, INPUT_REPORT_SIZE + 1);
	status = ReadFile(DeviceHandle, reporteEntrada, INPUT_REPORT_SIZE + 1, &BytesRead, NULL);
	rsptfptr = (float*)&reporteEntrada[2];
	respuestaf = *rsptfptr;
	printf("%f\n", respuestaf);

	df1 = 51.5;
	df2 = 6.38;
	printf("Voy a multiplicar %f * %f = ", df1, df2);
	reporteSalida[0] = 0x00;	//Dummy
	reporteSalida[1] = 0x22;	//Multi
	df1ptr = (float*)&reporteSalida[2];
	*df1ptr = df1;
	df2ptr = (float*)&reporteSalida[6];
	*df2ptr = df2;
	status = WriteFile(DeviceHandle, reporteSalida, OUTPUT_REPORT_SIZE + 1, &BytesWritten, NULL);
	memset(&reporteEntrada, 0, INPUT_REPORT_SIZE + 1);
	status = ReadFile(DeviceHandle, reporteEntrada, INPUT_REPORT_SIZE + 1, &BytesRead, NULL);
	rsptfptr = (float*)&reporteEntrada[2];
	respuestaf = *rsptfptr;
	printf("%f\n", respuestaf);

	df1 = 817.92;
	df2 = 32.452;
	printf("Voy a dividir %f / %f = ", df1, df2);
	reporteSalida[0] = 0x00;	//Dummy
	reporteSalida[1] = 0x23;	//Dividir
	df1ptr = (float*)&reporteSalida[2];
	*df1ptr = df1;
	df2ptr = (float*)&reporteSalida[6];
	*df2ptr = df2;
	status = WriteFile(DeviceHandle, reporteSalida, OUTPUT_REPORT_SIZE + 1, &BytesWritten, NULL);
	memset(&reporteEntrada, 0, INPUT_REPORT_SIZE + 1);
	status = ReadFile(DeviceHandle, reporteEntrada, INPUT_REPORT_SIZE + 1, &BytesRead, NULL);
	rsptfptr = (float*)&reporteEntrada[2];
	respuestaf = *rsptfptr;
	printf("%f\n", respuestaf);
}


void Touch_DeviceTerminal(void) {
	DWORD BytesRead = 0;
	DWORD BytesWritten = 0;
	unsigned char reporteEntrada[INPUT_REPORT_SIZE + 1];
	unsigned char reporteSalida[OUTPUT_REPORT_SIZE + 1];
	int status = 0;
	int d1, d2, respuesta;
	int *d1ptr, *d2ptr, *rsptptr;
	float df1, df2, respuestaf;
	float* df1ptr, *df2ptr, *rsptfptr;

	if (DeviceHandle == NULL)	//Validar que haya comunicacion con el dispositivo
		return;

	int command;
	printf("Comando = ");
	scanf_s("%d", &command);

	reporteSalida[0] = 0x00;	//Dummy
	switch (command)
	{
	case 10:
		reporteSalida[1] = 0x10;
		break;
	case 11:
		reporteSalida[1] = 0x11;
		break;
	case 12:
		reporteSalida[1] = 0x12;
		break;
	case 13:
		reporteSalida[1] = 0x13;
		break;
	case 20:
		reporteSalida[1] = 0x20;
		break;
	case 21:
		reporteSalida[1] = 0x21;
		break;
	case 22:
		reporteSalida[1] = 0x22;
		break;
	case 23:
		reporteSalida[1] = 0x23;
		break;
	}

	if (command == 10 || command == 11 || command == 12 || command == 13) {
		printf("Numero1 (Entero) = ");
		scanf_s("%d", &d1);
		printf("Numero2 (Entero) = ");
		scanf_s("%d", &d2);
		d1ptr = (int*)&reporteSalida[2];
		*d1ptr = d1;
		d2ptr = (int*)&reporteSalida[6];
		*d2ptr = d2;
	}
	else if (command == 20 || command == 21 || command == 22 || command == 23)
	{
		printf("Numero1 (Flotante) = ");
		scanf_s("%f", &df1);
		printf("Numero2 (Flotante) = ");
		scanf_s("%f", &df2);
		df1ptr = (float*)&reporteSalida[2];
		*df1ptr = df1;
		df2ptr = (float*)&reporteSalida[6];
		*df2ptr = df2;
	}

	if ((command == 13 && d2 == (int)0) || (command == 23 && df2 == (float)0)) {
		printf("Division Invalida\n\n");
		return;
	}

	status = WriteFile(DeviceHandle, reporteSalida, OUTPUT_REPORT_SIZE + 1, &BytesWritten, NULL);
	memset(&reporteEntrada, 0, INPUT_REPORT_SIZE + 1);
	status = ReadFile(DeviceHandle, reporteEntrada, INPUT_REPORT_SIZE + 1, &BytesRead, NULL);


	if (command == 10 || command == 11 || command == 12 || command == 13) {
		rsptptr = (int*)&reporteEntrada[2];
		respuesta = *rsptptr;
		printf("Respuesta = %d\n\n", respuesta);
	}
	else if (command == 20 || command == 21 || command == 22 || command == 23)
	{
		rsptfptr = (float*)&reporteEntrada[2];
		respuestaf = *rsptfptr;
		printf("Respuesta = %f\n\n", respuestaf);
	}
}

void main() {
	Load_HID_Library();
	if (Open_Device()) {
		printf("Vamos bien\n");
		while ((!_kbhit())
			&& (!terminaAbruptaEInstantaneamenteElPrograma)) {
			Touch_DeviceTerminal();
		}
	}
	else {
		printf(">:(\n");
	}
	Close_Device();
}