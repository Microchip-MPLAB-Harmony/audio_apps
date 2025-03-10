 /*******************************************************************************
  USB Audio class definitions

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_audio_local.h

  Summary:
    USB Audio class definitions

  Description:
    This file describes the Audio class specific definitions.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
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
// DOM-IGNORE-END

#ifndef USB_DEVICE_AUDIO_LOCAL_H
#define USB_DEVICE_AUDIO_LOCAL_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "usb/usb_device.h"
#include "usb/src/usb_device_local.h"
#include "usb/usb_device_audio_v1_0.h"


/* MISRA C-2012 Rule 5.1 deviate:2, Rule 5.2 deviate:2, Rule 6.1 deviate:1, Rule 8.6 deviate:1 
   Deviation record ID - H3_USB_MISRAC_2012_R_5_1_DR_1, H3_USB_MISRAC_2012_R_5_2_DR_1 
   H3_USB_MISRAC_2012_R_6_1_DR_1,and H3_USB_MISRAC_2012_R_8_6_DR_1*/

/* Smallest possible value of Endpoint maxpacketSize */ 
#define M_USB_DEVICE_AUDIO_MIN_EP_SZ 8U 

// *****************************************************************************
/* Audio flags.

  Summary:
 state of an audio streaming interface.

  Description:


  Remarks:
    This structure is internal to the Audio function driver.
 */ 
typedef enum
{
    USB_DEVICE_AUDIO_STRMNG_INTFC_NOT_INITIALIZED = 0,
    USB_DEVICE_AUDIO_STRMNG_INTFC_INITIALIZED

}USB_DEVICE_AUDIO_STRMNG_INTFC_STATE;


// *****************************************************************************
/* USB Device Audio Transfer direction

  Summary:
    USB Device Audio Transfer direction

  Description:
    This enumeration defines the possible USB Device Audio device transfer direction.

  Remarks:
    None.
*/
typedef enum
{
    /* Audio Read */
    USB_DEVICE_AUDIO_READ = 0,

    /* Audio Write */
    USB_DEVICE_AUDIO_WRITE = 1

} USB_DEVICE_AUDIO_TRANSFER_DIRECTION;


// *****************************************************************************
/* Audio flags.

  Summary:
   Flags for tracking internal status.

  Description:


  Remarks:
    This structure is internal to the Audio function driver.
*/

typedef union U_USB_DEVICE_AUDIO_FLAGS
{
    struct
    {
        uint8_t audioControlInterfaceReady:1;
    };
    uint8_t allFlags;
}USB_DEVICE_AUDIO_FLAGS;


// *****************************************************************************
/* USB Device Audio Function Driver IRP object.

  Summary:
    USB Device Audio Function Driver IRP object.

  Description:
    IRP object used by the Audio to service application requests.

  Remarks:
    None.
*/
typedef struct
{

   USB_DEVICE_IRP irp;

   USB_DEVICE_AUDIO_INDEX iAudio;

}USB_DEVICE_AUDIO_IRP_OBJECT;

// *****************************************************************************
/* USB Device Audio Endpoint Instance structure .

  Summary:
    USB Device Audio Endpoint Instance.

  Description:
    This structure can be used for storing Audio endpoint parameters.

  Remarks:
    None.
*/
typedef struct
{
    /* End point address */
    uint8_t epAddr;

    /* End point maximum payload */
    uint16_t epMaxPacketSize;

    /* Indicates if the endpoint is Enabled or not */ 
    bool status;
}USB_DEVICE_AUDIO_EP_INSTANCE;

// *****************************************************************************
/* USB Device Audio Streaming Interface Alternate settings.

  Summary:
    USB Device Audio Streaming Interface Alternate settings.

  Description:
    This structure can be used for storing Audio Streaming Interface alternate settings. 

  Remarks:
    None.
*/
typedef struct
{
    /* Number of Endpoints in this interface. In an Audio Streaming interface
     number of Endpoints present can be 0, 1 or 2*/
    uint8_t numEndPoints;

    /* Audio Data Endpoint  */
    USB_DEVICE_AUDIO_EP_INSTANCE isoDataEp;

    /* Audio Sync Endpoint*/
    USB_DEVICE_AUDIO_EP_INSTANCE isoSyncEp;

}USB_DEVICE_AUDIO_STREAMING_INTERFACE_ALTERNATE_SETTING;

// *****************************************************************************
/* USB Device Audio Streaming Interface structure

  Summary:
    USB Device Audio Streaming Interface structure

  Description:
    This structure can be used for storing Audio Streaming Interface.

  Remarks:
    None.
*/
typedef struct
{

    /* Interface number */
    uint8_t interfaceNum;

    /* Currently active alternate setting */
    uint8_t activeSetting;

    /* Indicates if any endpoint is active on this interface. */ 
    USB_DEVICE_AUDIO_STRMNG_INTFC_STATE state;

    /* Array of Alternate settings for a Streaming Interface*/
    USB_DEVICE_AUDIO_STREAMING_INTERFACE_ALTERNATE_SETTING  alterntSetting[USB_DEVICE_AUDIO_MAX_ALTERNATE_SETTING];

}USB_DEVICE_AUDIO_STREAMING_INTERFACE;


// *****************************************************************************
/* USB Device Audio Interface collection

  Summary:
    USB Device Audio Interface collection

  Description:
    This structure can be used for storing Audio Interface Collection.

  Remarks:
    None.
*/
typedef struct
{
    /* Audio Control interface number */
    uint8_t bControlInterfaceNum;

    /* Alternate setting for Audio Control Interface*/
    uint8_t bControlAltSetng;
    
    /* Number of streaming interfaces */
    uint8_t numStreamingInf;

    /* Audio spec in BCD 0x100 or 0x200 */
    uint16_t bcdADC;

    /* Optional interrupt ep info */
    USB_DEVICE_AUDIO_EP_INSTANCE intEp;

    /* Presence or absence of the interrupt EP */
    bool isIntEpExists;

    /* Array Audio streaming Interfaces */
    USB_DEVICE_AUDIO_STREAMING_INTERFACE streamInf[USB_DEVICE_AUDIO_MAX_STREAMING_INTERFACES];

}USB_DEVICE_AUDIO_INTERFACE_COLLECTION;



// *****************************************************************************
/* USB Device Audio Instance Structure

  Summary:
    USB Device Audio Instance Structure

  Description:
    This is Audio Instance Structure.

  Remarks:
    None.
*/
typedef struct
{
    /* Device layer instance associated with this function driver instance */
    USB_DEVICE_HANDLE devLayerHandle;

    /* Instance index */
    USB_DEVICE_AUDIO_INDEX audioIndex;

    /* Audio Interface Collection*/
    USB_DEVICE_AUDIO_INTERFACE_COLLECTION infCollection;

    /* Application callback */
    USB_DEVICE_AUDIO_EVENT_HANDLER appEventCallBack;

    /* Application user data */
    uintptr_t userData;

    /* Flags for indicating status*/
    USB_DEVICE_AUDIO_FLAGS flags;

    /* Transmit Queue Size*/
    uint32_t queueSizeWrite;

    /* Receive Queue Size */
    uint32_t queueSizeRead;

    /* Status Send Queue Size */
    uint32_t queueSizeStatusSend;
    
     /* Current Queue Size Write */
    volatile uint32_t currentQSizeWrite;

     /* Current Queue Size Read */
    volatile uint32_t currentQSizeRead;

    /* Current Queue Size Status Send */ 
    volatile uint32_t currentQSizeStatusSend; 

}USB_DEVICE_AUDIO_INSTANCE;


// *****************************************************************************
/* USB Device Audio Instance IRP Data

  Summary:
    USB Device Audio Instance IRP Data

  Description:
    This is structure is passed to an IRP for the Audio Device layer to retrieve
    the details of the transfer when IRP callback is occurred. 

  Remarks:
    None.
*/
typedef struct
{
    /* Audio Instance Number*/
    USB_DEVICE_AUDIO_INDEX iAudio;
    
    /* Audio streaming Interface Number*/
    uint8_t interfaceNum;
    
    /* Audio Transfer direction */
    USB_DEVICE_AUDIO_TRANSFER_DIRECTION direction;
    
} USB_DEVICE_AUDIO_IRP_DATA;

// *****************************************************************************
/* Audio Common data object

  Summary:
    Object used to keep track of data that is common to all instances of the
    Audio function driver.

  Description:
    This object is used to keep track of any data that is common to all
    instances of the Audio function driver.

  Remarks:
    None.
*/
typedef struct
{
    /* Set to true if all members of this structure
       have been initialized once */
    bool isMutexAudioIrpInitialized;

    /* Mutex to protect client object pool */
    OSAL_MUTEX_DECLARE(mutexAUDIOIRP);

} USB_DEVICE_AUDIO_COMMON_DATA_OBJ;

// *****************************************************************************
// *****************************************************************************
// Section: Extern Data
// *****************************************************************************
// *****************************************************************************
extern USB_DEVICE_IRP gUSBDeviceAudioIRP[USB_DEVICE_AUDIO_QUEUE_DEPTH_COMBINED];
extern USB_DEVICE_AUDIO_IRP_DATA gUSBDeviceAudioIrpData [USB_DEVICE_AUDIO_QUEUE_DEPTH_COMBINED];
extern USB_DEVICE_AUDIO_INSTANCE gUsbDeviceAudioInstance[USB_DEVICE_AUDIO_INSTANCES_NUMBER];
extern USB_DEVICE_AUDIO_COMMON_DATA_OBJ gUSBDeviceAudioCommonDataObj;


// *****************************************************************************
// *****************************************************************************
// Section: Prototypes for Local functions. 
// *****************************************************************************
// *****************************************************************************
USB_DEVICE_AUDIO_RESULT F_USB_DEVICE_AUDIO_Transfer
(
    USB_DEVICE_AUDIO_INDEX iAudio,
    USB_DEVICE_AUDIO_TRANSFER_HANDLE *transferHandle,
    uint8_t interfaceNum ,
    void * data ,
    size_t size,
    USB_DEVICE_AUDIO_TRANSFER_DIRECTION direction
);

void F_USB_DEVICE_AUDIO_TransferIRPCallBack ( USB_DEVICE_IRP * irp );
void F_USB_DEVICE_AUDIO_StatusSendIRPCallBack ( USB_DEVICE_IRP * irp ); 

void F_USB_DEVICE_AUDIO_Initialize
(
    SYS_MODULE_INDEX iAudio,
    DRV_HANDLE usbDeviceHandle,
    void* funcDriverInit,
    uint8_t interfaceNumber,
    uint8_t alternateSetting,
    uint8_t descriptorType, 
    uint8_t * pDescriptor
);

void F_USB_DEVICE_AUDIO_ControlTransferHandler
(
    SYS_MODULE_INDEX iAudio,
    USB_DEVICE_EVENT controlEvent,
    USB_SETUP_PACKET* controlEventData
);


void F_USB_DEVICE_AUDIO_Deinitialize ( SYS_MODULE_INDEX funcDriverIndex );

void F_USB_DEVICE_AUDIO_SetupPacketHandler
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    USB_SETUP_PACKET* controlEventData
);
void F_USB_DEVICE_AUDIO_GlobalInitialize (void);
void F_USB_DEVICE_AUDIO_TransferAbortAllow(USB_DEVICE_IRP * irp); 
void F_USB_DEVICE_AUDIO_TransferAbortPrevent(USB_DEVICE_IRP * irp); 
void F_USB_DEVICE_AUDIO_StatusSendAbortAllow(USB_DEVICE_IRP * irp); 
void F_USB_DEVICE_AUDIO_StatusSendAbortPrevent(USB_DEVICE_IRP * irp); 


#if defined USB_DEVICE_AUDIO_TRANSFER_ABORT_NOTIFY 
    #define M_USB_DEVICE_AUDIO_TransferCompleteCallback(x) F_USB_DEVICE_AUDIO_TransferAbortAllow(x)
    #define M_USB_DEVICE_AUDIO_StatusSendCompleteCallback(x) F_USB_DEVICE_AUDIO_StatusSendAbortAllow(x)
#else
    #define M_USB_DEVICE_AUDIO_TransferCompleteCallback(x) F_USB_DEVICE_AUDIO_TransferAbortPrevent(x)
    #define M_USB_DEVICE_AUDIO_StatusSendCompleteCallback(x) F_USB_DEVICE_AUDIO_StatusSendAbortPrevent(x)
#endif

/* MISRAC 2012 deviation block end */
#endif
 /************ End of file *************************************/
