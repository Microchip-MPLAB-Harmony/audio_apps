/*******************************************************************************
  System Initialization File

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits,
    and allocates any necessary global system resources,
 *******************************************************************************/

// DOM-IGNORE-BEGIN
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "configuration.h"
#include "definitions.h"
#include "device.h"


// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************
#pragma config TCM_CONFIGURATION = 0
#pragma config SECURITY_BIT = CLEAR
#pragma config BOOT_MODE = SET




// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
/* Following MISRA-C rules are deviated in the below code block */
/* MISRA C-2012 Rule 7.2 - Deviation record ID - H3_MISRAC_2012_R_7_2_DR_1 */
/* MISRA C-2012 Rule 11.1 - Deviation record ID - H3_MISRAC_2012_R_11_1_DR_1 */
/* MISRA C-2012 Rule 11.3 - Deviation record ID - H3_MISRAC_2012_R_11_3_DR_1 */
/* MISRA C-2012 Rule 11.8 - Deviation record ID - H3_MISRAC_2012_R_11_8_DR_1 */
// <editor-fold defaultstate="collapsed" desc="DRV_I2C Instance 0 Initialization Data">

/* I2C Client Objects Pool */
static DRV_I2C_CLIENT_OBJ drvI2C0ClientObjPool[DRV_I2C_CLIENTS_NUMBER_IDX0];

/* I2C Transfer Objects Pool */
static DRV_I2C_TRANSFER_OBJ drvI2C0TransferObj[DRV_I2C_QUEUE_SIZE_IDX0];

/* I2C PLib Interface Initialization */
static const DRV_I2C_PLIB_INTERFACE drvI2C0PLibAPI = {

    /* I2C PLib Transfer Read Add function */
    .read_t = (DRV_I2C_PLIB_READ)TWIHS0_Read,

    /* I2C PLib Transfer Write Add function */
    .write_t = (DRV_I2C_PLIB_WRITE)TWIHS0_Write,


    /* I2C PLib Transfer Write Read Add function */
    .writeRead = (DRV_I2C_PLIB_WRITE_READ)TWIHS0_WriteRead,

    /*I2C PLib Transfer Abort function */
    .transferAbort = (DRV_I2C_PLIB_TRANSFER_ABORT)TWIHS0_TransferAbort,

    /* I2C PLib Transfer Status function */
    .errorGet = (DRV_I2C_PLIB_ERROR_GET)TWIHS0_ErrorGet,

    /* I2C PLib Transfer Setup function */
    .transferSetup = (DRV_I2C_PLIB_TRANSFER_SETUP)TWIHS0_TransferSetup,

    /* I2C PLib Callback Register */
    .callbackRegister = (DRV_I2C_PLIB_CALLBACK_REGISTER)TWIHS0_CallbackRegister,
};


static const DRV_I2C_INTERRUPT_SOURCES drvI2C0InterruptSources =
{
    /* Peripheral has single interrupt vector */
    .isSingleIntSrc                        = true,

    /* Peripheral interrupt line */
    .intSources.i2cInterrupt             = (int32_t)TWIHS0_IRQn,
};

/* I2C Driver Initialization Data */
static const DRV_I2C_INIT drvI2C0InitData =
{
    /* I2C PLib API */
    .i2cPlib = &drvI2C0PLibAPI,

    /* I2C Number of clients */
    .numClients = DRV_I2C_CLIENTS_NUMBER_IDX0,

    /* I2C Client Objects Pool */
    .clientObjPool = (uintptr_t)&drvI2C0ClientObjPool[0],

    /* I2C TWI Queue Size */
    .transferObjPoolSize = DRV_I2C_QUEUE_SIZE_IDX0,

    /* I2C Transfer Objects */
    .transferObjPool = (uintptr_t)&drvI2C0TransferObj[0],

    /* I2C interrupt sources */
    .interruptSources = &drvI2C0InterruptSources,

    /* I2C Clock Speed */
    .clockSpeed = DRV_I2C_CLOCK_SPEED_IDX0,
};
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="DRV_I2S Instance 0 Initialization Data">

/* I2S PLIB Interface Initialization */
DRV_I2S_PLIB_INTERFACE drvI2S0PlibAPI =
{
    .I2S_LRCLK_Get = (DRV_I2S_LRCLK_GET)SSC_LRCLK_Get,  
};

/* I2S Driver Initialization Data */
DRV_I2S_INIT drvI2S0InitData =
{
    /* I2S PLIB API */
    .i2sPlib = &drvI2S0PlibAPI,

    /* I2S IRQ */
    .interruptI2S = DRV_I2S_INT_SRC_IDX0,

    /* I2S Number of clients */
    .numClients = DRV_I2S_CLIENTS_NUMBER_IDX0,

    /* I2S Queue Size */
    .queueSize = DRV_I2S_QUEUE_SIZE_IDX0,  

    .dmaChannelTransmit = DRV_I2S_XMIT_DMA_CH_IDX0,
    .dmaChannelReceive  = DRV_I2S_RCV_DMA_CH_IDX0,
    .i2sTransmitAddress = (void *)&(SSC_REGS->SSC_THR),
    .i2sReceiveAddress = (void *)&(SSC_REGS->SSC_RHR),

    /************ code specific to SAM E70 ********************/
    .interruptDMA = XDMAC_IRQn,
    /************ code specific to SAM E70 ********************/
    .dmaDataLength = DRV_I2S_DATA_LENGTH_IDX0,
};

// </editor-fold>

/*** CODEC Driver Initialization Data ***/
const DRV_WM8904_INIT drvwm8904Codec0InitData =
{
    .i2sDriverModuleIndex = DRV_WM8904_I2S_DRIVER_MODULE_INDEX_IDX0,
    .i2cDriverModuleIndex = DRV_WM8904_I2C_DRIVER_MODULE_INDEX_IDX0,
    .masterMode = DRV_WM8904_I2S_MASTER_MODE,
    .samplingRate = DRV_WM8904_AUDIO_SAMPLING_RATE,
    .volume = DRV_WM8904_VOLUME,
    .audioDataFormat = DRV_WM8904_AUDIO_DATA_FORMAT_MACRO,
    .enableMicInput = DRV_WM8904_ENABLE_MIC_INPUT,
    .enableMicBias = DRV_WM8904_ENABLE_MIC_BIAS,
    .micGain = DRV_WM8904_MIC_GAIN
};




// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************
/* Structure to hold the object handles for the modules in the system. */
SYSTEM_OBJECTS sysObj;

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************
/******************************************************
 * USB Driver Initialization
 ******************************************************/
 
static void DRV_USB_VBUSPowerEnable(uint8_t port, bool enable)
{
    /* Note: When operating in Host mode, the application can specify a Root 
       hub port enable function. The USB Host Controller driver init data 
       structure has a member for specifying the root hub enable function. 
       This parameter should point to Root hub port enable function. If this 
       parameter is NULL, it implies that the port is always enabled. 
       
       This function generated by MHC to let the user enable the root hub. 
       User must use the MHC pin configuration utility to configure the pin 
       used for enabling VBUS  */
    if (enable == true)
    {
        /* Enable the VBUS */
        VBUS_AH_PowerEnable();
    }
    else
    {
        /* Disable the VBUS */
        VBUS_AH_PowerDisable();
    }
}

static const DRV_USBHSV1_INIT drvUSBInit =
{
    /* Interrupt Source for USB module */
    .interruptSource = USBHS_IRQn,

    /* System module initialization */
    .moduleInit = {0},

    /* USB Controller to operate as USB Host */
    .operationMode = DRV_USBHSV1_OPMODE_HOST,

    /* To operate in USB Normal Mode */
    .operationSpeed = DRV_USBHSV1_DEVICE_SPEEDCONF_NORMAL,

    /* Identifies peripheral (PLIB-level) ID */
    .usbID = USBHS_REGS,
    
   /* USB Host Power Enable. USB Driver uses this function to Enable the VBUS */ 
   .portPowerEnable = DRV_USB_VBUSPowerEnable,

            
    /* Root hub available current in milliamperes */
    .rootHubAvailableCurrent = 500,
};


// <editor-fold defaultstate="collapsed" desc="File System Initialization Data">

 const SYS_FS_MEDIA_MOUNT_DATA sysfsMountTable[SYS_FS_VOLUME_NUMBER] =
{
    {
        .mountName = SYS_FS_MEDIA_IDX0_MOUNT_NAME_VOLUME_IDX0,
        .devName   = SYS_FS_MEDIA_IDX0_DEVICE_NAME_VOLUME_IDX0,
        .mediaType = SYS_FS_MEDIA_TYPE_IDX0,
        .fsType   = SYS_FS_TYPE_IDX0
    },
};


static const SYS_FS_FUNCTIONS FatFsFunctions =
{
    .mount             = FATFS_mount,
    .unmount           = FATFS_unmount,
    .open              = FATFS_open,
    .read_t              = FATFS_read,
    .close             = FATFS_close,
    .seek              = FATFS_lseek,
    .fstat             = FATFS_stat,
    .getlabel          = FATFS_getlabel,
    .currWD            = FATFS_getcwd,
    .getstrn           = FATFS_gets,
    .openDir           = FATFS_opendir,
    .readDir           = FATFS_readdir,
    .closeDir          = FATFS_closedir,
    .chdir             = FATFS_chdir,
    .chdrive           = FATFS_chdrive,
    .write_t             = FATFS_write,
    .tell              = FATFS_tell,
    .eof               = FATFS_eof,
    .size              = FATFS_size,
    .mkdir             = FATFS_mkdir,
    .remove_t            = FATFS_unlink,
    .setlabel          = FATFS_setlabel,
    .truncate          = FATFS_truncate,
    .chmode            = FATFS_chmod,
    .chtime            = FATFS_utime,
    .rename_t            = FATFS_rename,
    .sync              = FATFS_sync,
    .putchr            = FATFS_putc,
    .putstrn           = FATFS_puts,
    .formattedprint    = FATFS_printf,
    .testerror         = FATFS_error,
    .formatDisk        = (FORMAT_DISK)FATFS_mkfs,
    .partitionDisk     = FATFS_fdisk,
    .getCluster        = FATFS_getclusters
};




static const SYS_FS_REGISTRATION_TABLE sysFSInit [ SYS_FS_MAX_FILE_SYSTEM_TYPE ] =
{
    {
        .nativeFileSystemType = FAT,
        .nativeFileSystemFunctions = &FatFsFunctions
    }
};
// </editor-fold>



// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="SYS_TIME Initialization Data">

static const SYS_TIME_PLIB_INTERFACE sysTimePlibAPI = {
    .timerCallbackSet = (SYS_TIME_PLIB_CALLBACK_REGISTER)TC0_CH0_TimerCallbackRegister,
    .timerStart = (SYS_TIME_PLIB_START)TC0_CH0_TimerStart,
    .timerStop = (SYS_TIME_PLIB_STOP)TC0_CH0_TimerStop ,
    .timerFrequencyGet = (SYS_TIME_PLIB_FREQUENCY_GET)TC0_CH0_TimerFrequencyGet,
    .timerPeriodSet = (SYS_TIME_PLIB_PERIOD_SET)TC0_CH0_TimerPeriodSet,
    .timerCompareSet = (SYS_TIME_PLIB_COMPARE_SET)TC0_CH0_TimerCompareSet,
    .timerCounterGet = (SYS_TIME_PLIB_COUNTER_GET)TC0_CH0_TimerCounterGet,
};

static const SYS_TIME_INIT sysTimeInitData =
{
    .timePlib = &sysTimePlibAPI,
    .hwTimerIntNum = TC0_CH0_IRQn,
};

// </editor-fold>



// *****************************************************************************
// *****************************************************************************
// Section: Local initialization functions
// *****************************************************************************
// *****************************************************************************

/* MISRAC 2012 deviation block end */

/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize ( void* data )
{

    /* MISRAC 2012 deviation block start */
    /* MISRA C-2012 Rule 2.2 deviated in this file.  Deviation record ID -  H3_MISRAC_2012_R_2_2_DR_1 */


    EFC_Initialize();
  
    CLOCK_Initialize();
	PIO_Initialize();

    XDMAC_Initialize();



	RSWDT_REGS->RSWDT_MR = RSWDT_MR_WDDIS_Msk;	// Disable RSWDT 

	WDT_REGS->WDT_MR = WDT_MR_WDDIS_Msk; 		// Disable WDT 

  

 
    TC0_CH0_TimerInitialize(); 
     
    
	SSC_Initialize();

	BSP_Initialize();
	TWIHS0_Initialize();


    /* MISRAC 2012 deviation block start */
    /* Following MISRA-C rules deviated in this block  */
    /* MISRA C-2012 Rule 11.3 - Deviation record ID - H3_MISRAC_2012_R_11_3_DR_1 */
    /* MISRA C-2012 Rule 11.8 - Deviation record ID - H3_MISRAC_2012_R_11_8_DR_1 */

    /* Initialize I2C0 Driver Instance */
    sysObj.drvI2C0 = DRV_I2C_Initialize(DRV_I2C_INDEX_0, (SYS_MODULE_INIT *)&drvI2C0InitData);

    /* Initialize I2S0 Driver Instance */
    sysObj.drvI2S0 = DRV_I2S_Initialize(DRV_I2S_INDEX_0, (SYS_MODULE_INIT *)&drvI2S0InitData);

    sysObj.drvwm8904Codec0 = DRV_WM8904_Initialize(DRV_WM8904_INDEX_0, (SYS_MODULE_INIT *)&drvwm8904Codec0InitData);


    /* MISRA C-2012 Rule 11.3, 11.8 deviated below. Deviation record ID -  
    H3_MISRAC_2012_R_11_3_DR_1 & H3_MISRAC_2012_R_11_8_DR_1*/
        
    sysObj.sysTime = SYS_TIME_Initialize(SYS_TIME_INDEX_0, (SYS_MODULE_INIT *)&sysTimeInitData);
    
    /* MISRAC 2012 deviation block end */

    /* Initialize the USB Host layer */
    sysObj.usbHostObject0 = USB_HOST_Initialize (( SYS_MODULE_INIT *)& usbHostInitData );    

    /* Initialize USB Driver */ 
    sysObj.drvUSBHSV1Object = DRV_USBHSV1_Initialize(DRV_USBHSV1_INDEX_0, (SYS_MODULE_INIT *) &drvUSBInit);    

    /*** File System Service Initialization Code ***/
    (void) SYS_FS_Initialize( (const void *) sysFSInit );


    /* MISRAC 2012 deviation block end */
    APP_Initialize();


    NVIC_Initialize();


    /* MISRAC 2012 deviation block end */
}

/*******************************************************************************
 End of File
*/
