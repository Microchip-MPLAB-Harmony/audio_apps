/*******************************************************************************
* Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#include "app_globals.h"

const char * ERROR_STR[6] = 
    { "i2sc0 Not Ready",    //0 
      "i2sc0 Event Error",  //1 
      "i2sc0 Buffer Error", //2 
      "USB Not Ready",      //3
      "USB Buffer Error",   //4
      "Generic Error",      //5
    };

bool errState = false;

/* Application's state machine's initial state. */
/*
    APP_STATE_INIT = 0,
    APP_STATE_USB_DEVICE_OPEN,
    APP_STATE_I2SC0_OPEN,
    APP_STATE_I2SC0_SET_BUFFER_HANDLER,
    APP_STATE_INITIAL_USB_READ_REQUESTS,
    APP_STATE_INITIAL_CODEC_WRITEREAD_REQUESTS,
    APP_STATE_MUTE_AUDIO_PLAYBACK,
    APP_STATE_USB_INTERFACE_ALTERNATE_SETTING_RCVD,
    APP_STATE_SAMPLING_FREQUENCY_CHANGE_HP,
    APP_STATE_SAMPLING_FREQUENCY_CHANGE_MP,
    //APP_STATE_USB_INTERFACE_ALTERNATE_SETTING_RCVD_HP, //headphone
    //APP_STATE_USB_INTERFACE_ALTERNATE_SETTING_RCVD_MP, //microphone
    APP_STATE_WAIT_FOR_CONFIGURATION,
    APP_STATE_PROCESS_DATA,
    APP_STATE_IDLE,
    APP_STATE_ERROR,
*/

const char * stateStr[NUMSTATES] =
{
    "_INIT\r\n",
    "_USB_OPEN\r\n",
    "_I2SC0_OPEN\r\n",
    "_I2SC0_SET_HANDLER\r\n",
    "_INITIAL_USB_RW\r\n",
    "_INITIAL_I2SC0_WR\r\n",
    "_MUTE\r\n",
    "_ALTERNATE_SETTING\r\n",
    "_FREQ_CHANGE_HP\r\n",
    "_FREQ_CHANGE_MP\r\n",
    //"_USB_INTERFACE_ALTERNATE_SETTING_RCVD_HP"\r\n", //headphone
    //"_USB_INTERFACE_ALTERNATE_SETTING_RCVD_MP"\r\n", //microphone
    "_WAIT\r\n",
    "_PROC\r\n",
    "_IDLE\r\n",
    "_ERROR\r\n",
};

const char * usbDevEventStr[] =
{
    "unknown 0",
    "USB_DEVICE:_ERROR",          //1
    "USB_DEVICE:_RESET",          //2 
    "USB_DEVICE:_RESUMED",        //3
    "USB_DEVICE:_SUSPENDED",      //4 
    "unknown 5",
    "unknown 6",
    "USB_DEVICE:_SOF",            //7 
    "USB_DEVICE:_POWER_DETECTED", //8 
    "USB_DEVICE:_POWER_REMOVED",  //9
    "USB_DEVICE:_CONFIGURED",
    "USB_DEVICE:_DECONFIGURED",
    "USB_DEVICE:_CONTROL_TRANSFER_ABORTED",
    "USB_DEVICE:_CONTROL_TRANSFER_DATA_RECEIVED",
    "USB_DEVICE:_CONTROL_TRANSFER_SETUP_REQUEST",
    "USB_DEVICE:_CONTROL_TRANSFER_DATA_SENT",
    "USB_DEVICE:_ENDPOINT_READ_COMPLETE",
    "USB_DEVICE:_ENDPOINT_WRITE_COMPLETE",
    "USB_DEVICE:_SET_DESCRIPTOR",
    "USB_DEVICE:_SYNCH_FRAME",
};

const char * usbAudioEventStr[] =
{
    "USB_AUDIO:_WRITE_COMPLETE ",
    "USB_AUDIO:_READ_COMPLETE ",
    "USB_AUDIO:_STATUS_SEND_COMPLETE ", 
    "USB_AUDIO:_INTERFACE_SETTING_CHANGED",
    "USB_AUDIO:_CONTROL_TRANSFER_DATA_RECEIVED",
    "USB_AUDIO:_CONTROL_TRANSFER_DATA_SENT",
    "USB_AUDIO:_CONTROL_TRANSFER_UNKNOWN",
    "USB_AUDIO:_CONTROL_SET_CUR",
    "USB_AUDIO:_CONTROL_SET_MIN",
    "USB_AUDIO:_CONTROL_SET_MAX",
    "USB_AUDIO:_CONTROL_SET_RES",
    "USB_AUDIO:_ENTITY_SET_MEM",
    "USB_AUDIO:_CONTROL_GET_CUR",
    "USB_AUDIO:_CONTROL_GET_MIN",
    "USB_AUDIO:_CONTROL_GET_MAX",
    "USB_AUDIO:_CONTROL_GET_RES",
    "USB_AUDIO:_ENTITY_GET_MEM",
    "USB_AUDIO:_ENTITY_GET_STAT",
};