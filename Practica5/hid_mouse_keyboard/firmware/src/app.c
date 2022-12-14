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

/*Keyboard Report to be transmitted*/
KEYBOARD_INPUT_REPORT APP_MAKE_BUFFER_DMA_READY keyboardInputReport;
/* Keyboard output report */
KEYBOARD_OUTPUT_REPORT APP_MAKE_BUFFER_DMA_READY keyboardOutputReport;
/* Mouse Report */
MOUSE_REPORT mouseReport APP_MAKE_BUFFER_DMA_READY;
MOUSE_REPORT mouseReportPrevious APP_MAKE_BUFFER_DMA_READY;



// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

USB_DEVICE_HID_EVENT_RESPONSE APP_USBDeviceHIDEventHandler
(
    USB_DEVICE_HID_INDEX hidInstance,
    USB_DEVICE_HID_EVENT event,
    void * eventData,
    uintptr_t userData
)
{
    APP_DATA * appData = (APP_DATA *)userData;

    switch(event)
    {
        case USB_DEVICE_HID_EVENT_REPORT_SENT:

            /* This means the mouse report was sent.
             We are free to send another report */

            appData->isReportSentComplete = true;
            break;

        case USB_DEVICE_HID_EVENT_REPORT_RECEIVED:

            /* This means we have received a report */
            appData->isReportReceived = true;
            break;

        case USB_DEVICE_HID_EVENT_SET_IDLE:

             /* Acknowledge the Control Write Transfer */
           USB_DEVICE_ControlStatus(appData->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);

            /* save Idle rate recieved from Host */
            appData->idleRate 
                   = ((USB_DEVICE_HID_EVENT_DATA_SET_IDLE*)eventData)->duration;
            break;

        case USB_DEVICE_HID_EVENT_GET_IDLE:

            /* Host is requesting for Idle rate. Now send the Idle rate */
            USB_DEVICE_ControlSend(appData->deviceHandle, & (appData->idleRate),1);

            /* On successfully reciveing Idle rate, the Host would acknowledge back with a
               Zero Length packet. The HID function drvier returns an event
               USB_DEVICE_HID_EVENT_CONTROL_TRANSFER_DATA_SENT to the application upon
               receiving this Zero Length packet from Host.
               USB_DEVICE_HID_EVENT_CONTROL_TRANSFER_DATA_SENT event indicates this control transfer
               event is complete */ 

            break;

        case USB_DEVICE_HID_EVENT_SET_PROTOCOL:
            /* Host is trying set protocol. Now receive the protocol and save */
            appData->activeProtocol
                = ((USB_DEVICE_HID_EVENT_DATA_SET_PROTOCOL *)eventData)->protocolCode;

              /* Acknowledge the Control Write Transfer */
            USB_DEVICE_ControlStatus(appData->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);
            break;

        case  USB_DEVICE_HID_EVENT_GET_PROTOCOL:

            /* Host is requesting for Current Protocol. Now send the Idle rate */
             USB_DEVICE_ControlSend(appData->deviceHandle, &(appData->activeProtocol), 1);

             /* On successfully reciveing Idle rate, the Host would acknowledge
               back with a Zero Length packet. The HID function drvier returns
               an event USB_DEVICE_HID_EVENT_CONTROL_TRANSFER_DATA_SENT to the
               application upon receiving this Zero Length packet from Host.
               USB_DEVICE_HID_EVENT_CONTROL_TRANSFER_DATA_SENT event indicates
               this control transfer event is complete */
             break;

        case USB_DEVICE_HID_EVENT_CONTROL_TRANSFER_DATA_SENT:
            break;

        default:
            break;
    }

    return USB_DEVICE_HID_EVENT_RESPONSE_NONE;
}

/*******************************************************************************
  Function:
    void APP_USBDeviceEventHandler (USB_DEVICE_EVENT event,
        USB_DEVICE_EVENT_DATA * eventData)

  Summary:
    Event callback generated by USB device layer.

  Description:
    This event handler will handle all device layer events.

  Parameters:
    None.

  Returns:
    None.
 */

void APP_USBDeviceEventHandler(USB_DEVICE_EVENT event,
        void * eventData, uintptr_t context)
{
    USB_DEVICE_EVENT_DATA_CONFIGURED *configurationValue;

    switch(event)
    {
        case USB_DEVICE_EVENT_SOF:
            /* This event is used for switch debounce. This flag is reset
             * by the switch process routine. */
            appData.sofEventHasOccurred = true;
            appData.sofEventHasOccurred2 = true;
            appData.sofEventHasOccurred3 = true;
            break;
        case USB_DEVICE_EVENT_RESET:
        case USB_DEVICE_EVENT_DECONFIGURED:

            /* Device got deconfigured */

            appData.isConfigured = false;
            appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            BSP_LEDOn (APP_USB_LED_1);
            BSP_LEDOn (APP_USB_LED_2);
            BSP_LEDOff (APP_USB_LED_3);

            break;

        case USB_DEVICE_EVENT_CONFIGURED:

            /* Device is configured */

            configurationValue = (USB_DEVICE_EVENT_DATA_CONFIGURED *)eventData;
            if(configurationValue->configurationValue == 1)
            {
                appData.isConfigured = true;

                BSP_LEDOff ( APP_USB_LED_1 );
                BSP_LEDOff ( APP_USB_LED_2 );
                BSP_LEDOn ( APP_USB_LED_3 );

                /* Register the Application HID Event Handler. */

                USB_DEVICE_HID_EventHandlerSet(appData.hidInstance,
                        APP_USBDeviceHIDEventHandler, (uintptr_t)&appData);
            }
            break;

        case USB_DEVICE_EVENT_SUSPENDED:
            BSP_LEDOff ( APP_USB_LED_1 );
            BSP_LEDOn ( APP_USB_LED_2 );
            BSP_LEDOn ( APP_USB_LED_3 );
            break;

        case USB_DEVICE_EVENT_RESUMED:
        case USB_DEVICE_EVENT_POWER_DETECTED:
            /* Attach the device */
            USB_DEVICE_Attach (appData.deviceHandle);
            break;
        case USB_DEVICE_EVENT_POWER_REMOVED:
            /* There is no VBUS. We can detach the device */
            USB_DEVICE_Detach(appData.deviceHandle);
            break;
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

/********************************************************
 * Application switch press routine
 ********************************************************/

void APP_ProcessSwitchPress(void)
{
    /* This function checks if the switch is pressed and then
     * debounces the switch press*/

/* Check if a key was pressed */
    if(BSP_SWITCH_STATE_PRESSED == (BSP_SwitchStateGet(APP_USB_SWITCH_1)))
    {
        if(appData.ignoreSwitchPress)
        {
            /* This measn the key press is in progress */
            if(appData.sofEventHasOccurred)
            {
                /* A timer event has occurred. Update the debounce timer */
                appData.switchDebounceTimer ++;
                appData.sofEventHasOccurred = false;
                if(appData.switchDebounceTimer == APP_USB_SWITCH_DEBOUNCE_COUNT)
                {
                    /* Indicate that we have valid switch press. The switch is
                     * pressed flag will be cleared by the application tasks
                     * routine. We should be ready for the next key press.*/
                    appData.isSwitchPressed = true;
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

void APP_ProcessSwitchPress2(void)
{
    /* This function checks if the switch is pressed and then
     * debounces the switch press*/
    if(BSP_SWITCH_STATE_PRESSED == (BSP_SwitchStateGet(APP_USB_SWITCH_2)))
    {
        if(appData.ignoreSwitchPress2)
        {
            /* This means the key press is in progress */
            if(appData.sofEventHasOccurred2)
            {
                /* A timer event has occurred. Update the debounce timer */
                appData.switchDebounceTimer2 ++;
                appData.sofEventHasOccurred2 = false;
                if(appData.switchDebounceTimer2 == APP_USB_SWITCH_DEBOUNCE_COUNT)
                {
                    /* Indicate that we have valid switch press. The switch is
                     * pressed flag will be cleared by the application tasks
                     * routine. We should be ready for the next key press.*/
                    appData.isSwitchPressed2 = true;
                    appData.switchDebounceTimer2 = 0;
                    appData.ignoreSwitchPress2 = false;
                }
            }
        }
        else
        {
            /* We have a fresh key press */
            appData.ignoreSwitchPress2 = true;
            appData.switchDebounceTimer2 = 0;
        }
    }
    else
    {
        /* No key press. Reset all the indicators. */
        appData.ignoreSwitchPress2 = false;
        appData.switchDebounceTimer2 = 0;
        appData.sofEventHasOccurred2 = false;
    }
}

void APP_ProcessSwitchPress3(void)
{
    /* This function checks if the switch is pressed and then
     * debounces the switch press*/
    if(BSP_SWITCH_STATE_PRESSED == (BSP_SwitchStateGet(APP_USB_SWITCH_3)))
    {
        if(appData.ignoreSwitchPress3)
        {
            /* This means the key press is in progress */
            if(appData.sofEventHasOccurred3)
            {
                /* A timer event has occurred. Update the debounce timer */
                appData.switchDebounceTimer3 ++;
                appData.sofEventHasOccurred3 = false;
                if(appData.switchDebounceTimer3 == APP_USB_SWITCH_DEBOUNCE_COUNT)
                {
                    /* Indicate that we have valid switch press. The switch is
                     * pressed flag will be cleared by the application tasks
                     * routine. We should be ready for the next key press.*/
                    appData.isSwitchPressed3 = true;
                    appData.switchDebounceTimer3 = 0;
                    appData.ignoreSwitchPress3 = false;
                }
            }
        }
        else
        {
            /* We have a fresh key press */
            appData.ignoreSwitchPress3 = true;
            appData.switchDebounceTimer3 = 0;
        }
    }
    else
    {
        /* No key press. Reset all the indicators. */
        appData.ignoreSwitchPress3 = false;
        appData.switchDebounceTimer3 = 0;
        appData.sofEventHasOccurred3 = false;
    }
}

/********************************************************
 * Application Keyboard LED update routine.
 ********************************************************/

void APP_KeyboardLEDStatus(void)
{
    /* This measn we have a valid output report from the host*/

    if(keyboardOutputReport.ledState.numLock
            == KEYBOARD_LED_STATE_ON)
    {
        BSP_LEDOn(APP_USB_LED_2);
    }
    else
    {
        BSP_LEDOff(APP_USB_LED_2);
    }

    if(keyboardOutputReport.ledState.capsLock
            == KEYBOARD_LED_STATE_ON)
    {
        BSP_LEDOn(APP_USB_LED_1);
    }
    else
    {
        BSP_LEDOff(APP_USB_LED_1);
    }
}

/********************************************************
 * Application Keyboard Emulation Routine
 ********************************************************/

void APP_EmulateKeyboard(void)
{
    if(appData.functionMode == 1)
    {
        if(appData.isSwitchPressed2){
            appData.keyCodeArray.keyCode[0] = USB_HID_KEYBOARD_KEYPAD_KEYBOARD_PAGE_UP;
            appData.isSwitchPressed2 = false; 
        }else if(appData.isSwitchPressed3){
            appData.keyCodeArray.keyCode[0] = USB_HID_KEYBOARD_KEYPAD_KEYBOARD_PAGE_DOWN;
            appData.isSwitchPressed3 = false; 
        }else{
            appData.keyCodeArray.keyCode[0] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
        }
    }else
    {
        if(appData.isSwitchPressed2){
            appData.keyCodeArray.keyCode[0] = USB_HID_KEYBOARD_KEYPAD_KEYBOARD_TAB;
            appData.isSwitchPressed2 = false; 
        }else if(appData.isSwitchPressed3){
            appData.keyCodeArray.keyCode[0] = USB_HID_KEYBOARD_KEYPAD_KEYPAD_ENTER;
            appData.isSwitchPressed3 = false; 
        }else{
            appData.keyCodeArray.keyCode[0] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
        }
    }

    KEYBOARD_InputReportCreate(&appData.keyCodeArray,
            &appData.keyboardModifierKeys, &keyboardInputReport);

}

void APP_EmulateMouse(void)
{
    if(appData.isSwitchPressed2)
    {
        appData.mouseButton[0] = MOUSE_BUTTON_STATE_RELEASED;
        appData.mouseButton[1] = MOUSE_BUTTON_STATE_RELEASED;
        appData.xCoordinate = 50;
        appData.yCoordinate = 0; 
        appData.isSwitchPressed2 = false; 
    }else if(appData.isSwitchPressed3){
        appData.mouseButton[0] = MOUSE_BUTTON_STATE_RELEASED;
        appData.mouseButton[1] = MOUSE_BUTTON_STATE_RELEASED;
        appData.xCoordinate = -50;
        appData.yCoordinate = 0; 
        appData.isSwitchPressed3 = false; 
    }else{
        appData.mouseButton[0] = MOUSE_BUTTON_STATE_RELEASED;
        appData.mouseButton[1] = MOUSE_BUTTON_STATE_RELEASED;
        appData.xCoordinate = 0;
        appData.yCoordinate = 0;
    }
    MOUSE_ReportCreate(appData.xCoordinate, appData.yCoordinate,
        appData.mouseButton, &mouseReport);
}

/**********************************************
 * This function is called by when the device
 * is de-configured. It resets the application
 * state in anticipation for the next device
 * configured event
 **********************************************/

void APP_StateReset(void)
{
    appData.isReportReceived = false;
    appData.isReportSentComplete = true;
    appData.key = USB_HID_KEYBOARD_KEYPAD_KEYBOARD_A;
    appData.keyboardModifierKeys.modifierkeys = 0;
    memset(&keyboardOutputReport.data, 0, 64);
    appData.isSwitchPressed = false;
    appData.ignoreSwitchPress = false;
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

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    
    appData.deviceHandle = USB_DEVICE_HANDLE_INVALID;
    appData.isConfigured = false;

    /* Initialize the keycode array */
    appData.key = USB_HID_KEYBOARD_KEYPAD_KEYBOARD_A;
    appData.keyCodeArray.keyCode[0] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
    appData.keyCodeArray.keyCode[1] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
    appData.keyCodeArray.keyCode[2] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
    appData.keyCodeArray.keyCode[3] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
    appData.keyCodeArray.keyCode[4] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
    appData.keyCodeArray.keyCode[5] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
    
    /* Initialize the modifier keys */
    appData.keyboardModifierKeys.modifierkeys = 0;

    /* Initialize the led state */
    memset(&keyboardOutputReport.data, 0, 64);

    /* Initialize the switch state */
    appData.isSwitchPressed = false;
    appData.isSwitchPressed2 = false;
    appData.isSwitchPressed3 = false;
    appData.ignoreSwitchPress = false;
    appData.ignoreSwitchPress2 = false;
    appData.ignoreSwitchPress3 = false;
    
    appData.functionMode = 1;

    /* Initialize the HID instance index.  */
    appData.hidInstance = 0;

    /* Initialize tracking variables */
    appData.isReportReceived = false;
    appData.isReportSentComplete = true;

}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
		    /* Open the device layer */
            appData.deviceHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0,
                    DRV_IO_INTENT_READWRITE );

            if(appData.deviceHandle != USB_DEVICE_HANDLE_INVALID)
            {
                /* Register a callback with device layer to get event notification (for end point 0) */
                USB_DEVICE_EventHandlerSet(appData.deviceHandle,
                        APP_USBDeviceEventHandler, 0);

                appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            }
            else
            {
                /* The Device Layer is not ready to be opened. We should try
                 * again later. */
            }
            break;
        }

        case APP_STATE_WAIT_FOR_CONFIGURATION:

            /* Check if the device is configured. The
             * isConfigured flag is updated in the
             * Device Event Handler */

            if(appData.isConfigured)
            {
                /* Initialize the flag and place a request for a
                 * output report */

                appData.isReportReceived = false;

                USB_DEVICE_HID_ReportReceive(appData.hidInstance,
                        &appData.receiveTransferHandle,
                        (uint8_t *)&keyboardOutputReport,64);

                appData.state = APP_STATE_CHECK_IF_CONFIGURED;
            }

            break;

        case APP_STATE_CHECK_IF_CONFIGURED:

            /* This state is needed because the device can get
             * unconfigured asynchronously. Any application state
             * machine reset should happen within the state machine
             * context only. */

            if(appData.isConfigured)
            {
                appData.state = APP_STATE_SWITCH_PROCESS;
            }
            else
            {
                /* This means the device got de-configured.
                 * We reset the state and the wait for configuration */

                APP_StateReset();
                appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            }
            break;

        case APP_STATE_SWITCH_PROCESS:
            
            /* Process the switch state and go to the
             * next state. */
            
            APP_ProcessSwitchPress();
            APP_ProcessSwitchPress2();
            APP_ProcessSwitchPress3();
            if(appData.isSwitchPressed)
            {
                /* Toggle the mouse emulation with each switch press */
                if(appData.functionMode == 1){
                    appData.functionMode = 2;
                    BSP_LEDOff ( APP_USB_LED_1 );
                }else{
                    appData.functionMode = 1;
                    BSP_LEDOn ( APP_USB_LED_1 );
                }
                appData.isSwitchPressed = false;  
            } 

            if(appData.isSwitchPressed2)
            {
                BSP_LEDOn ( APP_USB_LED_2 );
            }else{
                BSP_LEDOff ( APP_USB_LED_2 );
            }
            if(appData.isSwitchPressed3)
            {
                BSP_LEDOn ( APP_USB_LED_3 );
            }else{
                BSP_LEDOff ( APP_USB_LED_3 );
            }
            
            appData.state = APP_STATE_CHECK_FOR_OUTPUT_REPORT;
            break;

        case APP_STATE_CHECK_FOR_OUTPUT_REPORT:

            if(appData.isReportReceived == true)
            {
                /* Update the LED and schedule and
                 * request */

                APP_KeyboardLEDStatus();

                appData.isReportReceived = false;
                USB_DEVICE_HID_ReportReceive(appData.hidInstance,
                        &appData.receiveTransferHandle,
                        (uint8_t *)&keyboardOutputReport,64);
            }

            appData.state = APP_STATE_EMULATE_KEYBOARD;
            break;

        case APP_STATE_EMULATE_KEYBOARD:

            if(appData.isReportSentComplete)
            {
                /* This means report can be sent*/
                               
                appData.isReportSentComplete = false;
                if(appData.functionMode == 1){
                    APP_EmulateKeyboard();
                    USB_DEVICE_HID_ReportSend(appData.hidInstance,
                        &appData.sendTransferHandle,
                        (uint8_t *)&keyboardInputReport,
                        sizeof(KEYBOARD_INPUT_REPORT));
                }else{
                    APP_EmulateMouse();
                    USB_DEVICE_HID_ReportSend(appData.hidInstance,
                    &appData.sendTransferHandle, 
                    (uint8_t*)&mouseReport,
                    sizeof(MOUSE_REPORT));
                }
            }
            appData.state = APP_STATE_CHECK_IF_CONFIGURED;
            break;

        case APP_STATE_ERROR:
            break;

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}
 

/*******************************************************************************
 End of File
 */

