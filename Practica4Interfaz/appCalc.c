/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

/*****************************************
 * Buffer required for reading and sending
 * data over CDC
 *****************************************/
uint8_t APP_MAKE_BUFFER_DMA_READY readBuffer[64];

/**********************
 * Switch Prompt.
 ***********************/
const uint8_t __attribute__((aligned(16))) switchPrompt[] = "\r\nPUSH BUTTON PRESSED";
uint8_t APP_MAKE_BUFFER_DMA_READY miString[] = "                                 ";

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

//********************** LRSG v

#define TRANS_COUNT 8
#define EDO_COUNT 9

char chr = 0;

float acum1 = 0;
float mult1 = 1.0;
int count1 = 0;
int negFlag1 = 1;

float acum2 = 0;
float mult2 = 1.0;
int count2 = 0;
int negFlag2 = 1;

float floatRes = 0;
float res = 0;
int flag = 0;
enum Oper
{
    Suma,
    Resta,
    Mult,
    Div
};
enum Oper oper;

int edo = 0;
int edoAnt = 0;
int trans = 0;
int miPrintf_flag = 0;
int miStringCont = 0;
char auxString[] = "                                 ";

// 0-->Inv�lida
// 6-->Digito
// 7-->Operador
int chrTrans[TRANS_COUNT] =
    {0, '(', ')', '=', 8, 27, 6, 7};
int mtzTrans[EDO_COUNT][TRANS_COUNT] = {
    {0, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 99, 99, 2, 1},
    {2, 2, 2, 2, 99, 99, 3, 4},
    {3, 2, 2, 2, 99, 99, 2, 2},
    {4, 4, 4, 4, 99, 99, 5, 4},
    {5, 5, 7, 5, 99, 99, 6, 5},
    {6, 5, 5, 5, 99, 99, 5, 5},
    {7, 7, 7, 8, 99, 99, 7, 7},
    {8, 0, 0, 0, 0, 0, 0, 0}};

void miPrintf(char *s, int cont)
{
    int i;
    for (i = 0; i < cont; i++)
        miString[i] = s[i];
    miPrintf_flag = 1;
    miStringCont = cont;
}

int calcTrans(char chr)
{
    int trans = 0;
    if (
            ((chr >= '0') && (chr <= '9')) 
            || (chr == '.') 
            || (chr == '~')
       )
        return (6);
    switch (chr)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        return (7);
    }
    for (trans = 5; trans > 0; trans--)
        if (chr == chrTrans[trans])
            break;
    return (trans);
}

int sigEdo(int edo, int trans)
{
    return (mtzTrans[edo][trans]);
}

void acum1Cal()
{
    if (chr == '~'){
        if(count1 == 0){
            negFlag1 = -1;
            count1++;
            miPrintf(&chr, 1);
        }
        return;
    }
    if (chr == '.')
    {
        if (flag == 0)
        {
            flag = 1;
            count1++;
            miPrintf(&chr, 1);
        }
    }
    else
    {
        if (flag == 0)
        {
            acum1 *= 10;
            acum1 += (chr - '0');
        }
        else
        {
            mult1 *= (float)0.1;
            acum1 += ((chr - '0') * mult1);
        }
        count1++;
        miPrintf(&chr, 1);
    }
}

void acum2Calc()
{
    if (chr == '~'){
        if(count2 == 0){
            negFlag2 = -1;
            count2++;
            miPrintf(&chr, 1);
        }
        return;
    }
    else if (chr == '.')
    {
        if (flag == 0)
        {
            flag = 1;
            count2++;
            miPrintf(&chr, 1);
        }
    }
    else
    {
        if (flag == 0)
        {
            acum2 *= 10;
            acum2 += (chr - '0');
        }
        else
        {
            mult2 *= (float)0.1;
            acum2 += ((chr - '0') * mult2);
        }
        count2++;
        miPrintf(&chr, 1);
    }
}

int ejecutaEdo(int edo)
{
    static int i = 0;
    static int negativoFlag = 0;
    static int digitosCont = 0;
    static float auxRes = 0;
    switch (edo)
    {
    case 0:
        break;
    case 1:
        BSP_LEDOff(APP_USB_LED_1);
        BSP_LEDOff(APP_USB_LED_2);
        BSP_LEDOff(APP_USB_LED_3);
        acum1 = 0;
        mult1 = 1.0;
        flag = 0;
        count1 = 0;
        negFlag1 = 1;
        miPrintf(&chr, 1);
        break;
    case 2:
        acum1Cal();
        break;
    case 3:
        acum1Cal();
        return (2);
    case 4:
        BSP_LEDOn(APP_USB_LED_1);
        BSP_LEDOff(APP_USB_LED_2);
        BSP_LEDOff(APP_USB_LED_3);
        miPrintf(&chr, 1);
        switch (chr)
        {
        case '+':
            oper = Suma;
            break;
        case '-':
            oper = Resta;
            break;
        case '*':
            oper = Mult;
            break;
        case '/':
            oper = Div;
            break;
        }
        acum2 = 0; // Preparar la entrada al estado 4
        mult2 = 1.0;
        flag = 0;
        count2 = 0;
        negFlag2 = 1;
        break;
    case 5:
        BSP_LEDOff(APP_USB_LED_1);
        BSP_LEDOn(APP_USB_LED_2);
        BSP_LEDOff(APP_USB_LED_3);
        acum2Calc();
        break;
    case 6:
        acum2Calc();
        return (5);
    case 7:
        BSP_LEDOff(APP_USB_LED_1);
        BSP_LEDOff(APP_USB_LED_2);
        BSP_LEDOn(APP_USB_LED_3);
        miPrintf(&chr, 1);
        break;
    case 8:
        BSP_LEDOn(APP_USB_LED_1);
        BSP_LEDOn(APP_USB_LED_2);
        BSP_LEDOn(APP_USB_LED_3);

        acum1 = acum1 * negFlag1;
        acum2 = acum2 * negFlag2;
        switch (oper)
        {
        case Suma:
            res = acum1 + acum2;
            break;
        case Resta:
            res = acum1 - acum2;
            break;
        case Mult:
            res = acum1 * acum2;
            break;
        case Div:
            if (acum2)
                res = acum1 / acum2;
            else
                res = -1;
            break;
        }
        // printf("%d\n",res);
        if (res < 0)
        {
            negativoFlag = 1;
            res = -1 * res;
        }
        else
        {
            negativoFlag = 0;
        }
        float auxResFloat = res - (int)res;
        auxRes = res;
        digitosCont = 0;
        do
        {
            auxRes /= 10;
            digitosCont++;
        } while (auxRes >= (float)1);
        i = digitosCont;
        do
        {
            auxString[negativoFlag + i] = '0' + ((int)res % 10);
            res /= 10;
        } while (--i >= 0);
        int decimalCount = 0;
        if (auxResFloat > (float)0.0)
        {
            decimalCount++;
            auxString[digitosCont + negativoFlag + decimalCount] = '.';
            do
            {
                decimalCount++;
                auxResFloat = auxResFloat * 10;
                auxString[digitosCont + negativoFlag + decimalCount] = '0' + (int)auxResFloat;
                auxResFloat = auxResFloat - (int)auxResFloat;
            } while (auxResFloat > 0 && decimalCount < 5);
        }
        auxString[0] = '=';
        if (negativoFlag)
        {
            auxString[1] = '-';
        }
        auxString[digitosCont + 1 + negativoFlag + decimalCount] = 0x0D; // Carriage return
        miPrintf(&auxString[0], digitosCont + 1 + negativoFlag + 1 + decimalCount);
        return (0);
    case 99:
        // printf("\n<<<Captura cancelada>>>\n");
        return (0); // Estado aceptor, rompe la rutina y marca estado de salida
    }
    return (edo); // Para estados no aceptores regresar el estado ejecutado
}

//********************** LRSG

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/************************************************
 * CDC COM1 Application Event Handler
 ************************************************/

void APP_USBDeviceCDCEventHandler(
    USB_DEVICE_CDC_INDEX index,
    USB_DEVICE_CDC_EVENT event,
    void *pData,
    uintptr_t userData)
{

    APP_DATA *appDataObject;
    appDataObject = (APP_DATA *)userData;
    USB_CDC_CONTROL_LINE_STATE *controlLineStateData;
    USB_DEVICE_CDC_EVENT_DATA_READ_COMPLETE *eventDataRead;

    switch (event)
    {
    case USB_DEVICE_CDC_EVENT_GET_LINE_CODING:

        /* This means the host wants to know the current line
         * coding. This is a control transfer request. Use the
         * USB_DEVICE_ControlSend() function to send the data to
         * host.  */

        USB_DEVICE_ControlSend(appDataObject->deviceHandle,
                               (uint8_t *)&appDataObject->getLineCodingData, sizeof(USB_CDC_LINE_CODING));

        break;

    case USB_DEVICE_CDC_EVENT_SET_LINE_CODING:

        /* This means the host wants to set the line coding.
         * This is a control transfer request. Use the
         * USB_DEVICE_ControlReceive() function to receive the
         * data from the host */

        USB_DEVICE_ControlReceive(appDataObject->deviceHandle,
                                  (uint8_t *)&appDataObject->setLineCodingData, sizeof(USB_CDC_LINE_CODING));

        break;

    case USB_DEVICE_CDC_EVENT_SET_CONTROL_LINE_STATE:

        /* This means the host is setting the control line state.
         * Read the control line state. We will accept this request
         * for now. */

        controlLineStateData = (USB_CDC_CONTROL_LINE_STATE *)pData;
        appDataObject->controlLineStateData.dtr = controlLineStateData->dtr;
        appDataObject->controlLineStateData.carrier = controlLineStateData->carrier;

        USB_DEVICE_ControlStatus(appDataObject->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);

        break;

    case USB_DEVICE_CDC_EVENT_SEND_BREAK:

        /* This means that the host is requesting that a break of the
         * specified duration be sent. Read the break duration */

        appDataObject->breakData = ((USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK *)pData)->breakDuration;

        /* Complete the control transfer by sending a ZLP  */
        USB_DEVICE_ControlStatus(appDataObject->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);

        break;

    case USB_DEVICE_CDC_EVENT_READ_COMPLETE:

        /* This means that the host has sent some data*/
        eventDataRead = (USB_DEVICE_CDC_EVENT_DATA_READ_COMPLETE *)pData;
        appData.readIsComplete = true;
        appDataObject->numBytesRead = eventDataRead->length;
        break;

    case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED:

        /* The data stage of the last control transfer is
         * complete. For now we accept all the data */

        USB_DEVICE_ControlStatus(appDataObject->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);
        break;

    case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_SENT:

        /* This means the GET LINE CODING function data is valid. We dont
         * do much with this data in this demo. */

        break;

    case USB_DEVICE_CDC_EVENT_WRITE_COMPLETE:

        /* This means that the data write got completed. We can schedule
         * the next read. */

        appData.writeIsComplete = true;

        break;

    default:
        break;
    }
}

/*************************************************
 * Application Device Layer Event Handler
 *************************************************/

void APP_USBDeviceEventCallBack(USB_DEVICE_EVENT event, void *eventData, uintptr_t context)
{
    uint8_t configurationValue;

    switch (event)
    {
    case USB_DEVICE_EVENT_RESET:
    case USB_DEVICE_EVENT_DECONFIGURED:

        /* USB device is reset or device is deconfigured.  This means that
         * USB device layer is about to deininitialize all function drivers.
         * Update LEDs indication */

        BSP_LEDOn(APP_USB_LED_1);
        BSP_LEDOn(APP_USB_LED_2);
        BSP_LEDOff(APP_USB_LED_3);

        appData.deviceIsConfigured = false;

        break;

    case USB_DEVICE_EVENT_SOF:

        /* This event is used for switch debounce. This flag is reset
         * by the switch process routine. */
        appData.sofEventHasOccurred = true;
        break;

    case USB_DEVICE_EVENT_CONFIGURED:

        /* Check the configuration */
        configurationValue = ((USB_DEVICE_EVENT_DATA_CONFIGURED *)eventData)->configurationValue;
        ;
        if (configurationValue == 1)
        {
            /* The device is in configured state */
            BSP_LEDOff(APP_USB_LED_1);
            BSP_LEDOff(APP_USB_LED_2);
            BSP_LEDOn(APP_USB_LED_3);

            /* Register the CDC Device application event handler here.
             * Note how the appData object pointer is passed as the
             * user data */

            USB_DEVICE_CDC_EventHandlerSet(USB_DEVICE_CDC_INDEX_0, APP_USBDeviceCDCEventHandler, (uintptr_t)&appData);

            /* Mark that set configuration is complete */
            appData.deviceIsConfigured = true;
        }
        break;

    case USB_DEVICE_EVENT_SUSPENDED:

        /* Update LED indication */
        BSP_LEDOff(APP_USB_LED_1);
        BSP_LEDOn(APP_USB_LED_2);
        BSP_LEDOn(APP_USB_LED_3);
        break;

    case USB_DEVICE_EVENT_POWER_DETECTED:

        /* VBUS was detected. We can attach the device */
        USB_DEVICE_Attach(appData.deviceHandle);
        break;

    case USB_DEVICE_EVENT_POWER_REMOVED:

        /* VBUS is not available any more. Detach the device. */
        USB_DEVICE_Detach(appData.deviceHandle);
        break;

    /* These events are not used in this demo */
    case USB_DEVICE_EVENT_RESUMED:
    case USB_DEVICE_EVENT_ERROR:
    default:
        break;
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/************************************************
 * Application State Reset Function
 ************************************************/

bool APP_StateReset(void)
{
    /* This function returns true if the device
     * was reset  */

    bool retVal;

    if (!appData.deviceIsConfigured)
    {
        appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
        appData.readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
        appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
        appData.readIsComplete = true;
        appData.writeIsComplete = true;
        retVal = true;
    }
    else
    {
        retVal = false;
    }

    return (retVal);
}

/************************************************
 * Switch Procesing routine
 ************************************************/
void APP_SwitchStateProcess(void)
{
    /* Check if a key was pressed */
    if (BSP_SWITCH_STATE_PRESSED == (BSP_SwitchStateGet(APP_USB_SWITCH_1)))
    {
        if (appData.ignoreSwitchPress)
        {
            /* This measn the key press is in progress */
            if (appData.sofEventHasOccurred)
            {
                /* A timer event has occurred. Update the debounce timer */
                appData.switchDebounceTimer++;
                appData.sofEventHasOccurred = false;
                if (appData.switchDebounceTimer == APP_USB_SWITCH_DEBOUNCE_COUNT)
                {
                    /* Indicate that we have valid switch press. The switch is
                     * pressed flag will be cleared by the application tasks
                     * routine. We should be ready for the next key press.*/
                    appData.switchIsPressed = true;
                    appData.switchDebounceTimer = 0;
                    appData.ignoreSwitchPress = false;
                }
            }
        }
        else
        {
            /* We have a fresh key press */
            appData.ignoreSwitchPress = true;
            appData.switchDebounceTimer = 0;
        }
    }
    else
    {
        /* No key press. Reset all the indicators. */
        appData.ignoreSwitchPress = false;
        appData.switchDebounceTimer = 0;
        appData.sofEventHasOccurred = false;
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize(void)
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    /* Device Layer Handle  */
    appData.deviceHandle = USB_DEVICE_HANDLE_INVALID;

    /* Initial get line coding state */
    appData.getLineCodingData.bDataBits = 8;
    appData.getLineCodingData.dwDTERate = 9600;
    appData.getLineCodingData.bCharFormat = 0;
    appData.getLineCodingData.bParityType = 0;

    /* Read Transfer Handle */
    appData.readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

    /* Write Transfer Handle */
    appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

    /* Initialize the application flags */
    appData.readIsComplete = true;
    appData.writeIsComplete = true;
    appData.ignoreSwitchPress = false;
    appData.switchIsPressed = false;
    appData.deviceIsConfigured = false;
    appData.sofEventHasOccurred = false;

    /* Initialize all the switch related parameters */
    appData.switchDebounceTimer = 0;

    /* Assign the read buffer */
    appData.readBuffer = &readBuffer[0];
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks(void)
{
    /* Update the application state machine based
     * on the current state */
    int i;
    /* Update the switch press */
    APP_SwitchStateProcess();

    switch (appData.state)
    {
    case APP_STATE_INIT:

        /* Open the device layer */
        appData.deviceHandle = USB_DEVICE_Open(USB_DEVICE_INDEX_0, DRV_IO_INTENT_READWRITE);

        if (appData.deviceHandle != USB_DEVICE_HANDLE_INVALID)
        {
            /* Register a callback with device layer to get event notification (for end point 0) */
            USB_DEVICE_EventHandlerSet(appData.deviceHandle, APP_USBDeviceEventCallBack, 0);

            appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
        }
        else
        {
            /* The Device Layer is not ready to be opened. We should try
             * again later. */
        }

        break;

    case APP_STATE_WAIT_FOR_CONFIGURATION:

        /* Check if the device was configured */
        if (appData.deviceIsConfigured)
        {
            /* If the device is configured then lets start reading */
            appData.state = APP_STATE_SCHEDULE_READ;
        }
        break;

    case APP_STATE_SCHEDULE_READ:

        if (APP_StateReset())
        {
            break;
        }

        /* If a read is complete, then schedule a read
         * else wait for the current read to complete */

        appData.state = APP_STATE_WAIT_FOR_READ_COMPLETE;
        if (appData.readIsComplete)
        {
            appData.readIsComplete = false;
            appData.readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
            USB_DEVICE_CDC_Read(USB_DEVICE_CDC_INDEX_0, &appData.readTransferHandle, appData.readBuffer, APP_READ_BUFFER_SIZE);
            if (appData.readTransferHandle == USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID)
            {
                appData.state = APP_STATE_ERROR;
                break;
            }
        }

        break;

    case APP_STATE_WAIT_FOR_READ_COMPLETE:
    case APP_STATE_CHECK_SWITCH_PRESSED:

        if (APP_StateReset())
        {
            break;
        }

        /* Check if a character was received or a switch was pressed.
         * The isReadComplete flag gets updated in the CDC event handler. */

        if (appData.readIsComplete || appData.switchIsPressed)
        {
            appData.state = APP_STATE_SCHEDULE_WRITE;
        }

        break;

    case APP_STATE_SCHEDULE_WRITE:

        if (APP_StateReset())
        {
            break;
        }

        /* Setup the write */

        appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
        appData.writeIsComplete = true;
        appData.state = APP_STATE_WAIT_FOR_WRITE_COMPLETE;

        if (appData.switchIsPressed)
        {
            /* If the switch was pressed, then send the switch prompt*/
            appData.switchIsPressed = false;
            USB_DEVICE_CDC_Write(USB_DEVICE_CDC_INDEX_0, &appData.writeTransferHandle,
                                 switchPrompt, 23, USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
        }
        else
        {
            /* Else echo each received character by adding 1 */
            for (i = 0; i < appData.numBytesRead; i++)
            {
                if ((appData.readBuffer[i] != 0x0A) && (appData.readBuffer[i] != 0x0D))
                {
                    // appData.readBuffer[i] = appData.readBuffer[i] + 1;
                    chr = appData.readBuffer[i];
                    trans = calcTrans(chr); // Calcular la transici�n seg�n la entrada del teclado
                    if (trans)
                    {                                // Validar por transici�n valida (la transici�n 0 es inv�lida)
                        edoAnt = edo;                // Guardar el estado anterior
                        edo = sigEdo(edoAnt, trans); // Calcular el siguiente estado
                        if (edoAnt != edo)           // Solo si hay cambio de estado hay que ...
                            edo = ejecutaEdo(edo);   // ... ejecutar el nuevo estado y asignar estado de continuidad
                    }
                }
            }
            if (miPrintf_flag)
            {
                USB_DEVICE_CDC_Write(USB_DEVICE_CDC_INDEX_0, &appData.writeTransferHandle,
                                     miString, miStringCont, USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
                miPrintf_flag = 0;
                miStringCont = 0;
            }
            /*                USB_DEVICE_CDC_Write(USB_DEVICE_CDC_INDEX_0,
                                    &appData.writeTransferHandle,
                                    appData.readBuffer, appData.numBytesRead,
                                    USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);*/
        }

        break;

    case APP_STATE_WAIT_FOR_WRITE_COMPLETE:

        if (APP_StateReset())
        {
            break;
        }

        /* Check if a character was sent. The isWriteComplete
         * flag gets updated in the CDC event handler */

        if (appData.writeIsComplete)
        {
            appData.state = APP_STATE_SCHEDULE_READ;
        }

        break;

    case APP_STATE_ERROR:
        break;
    default:
        break;
    }
}

/*******************************************************************************
 End of File
 */
