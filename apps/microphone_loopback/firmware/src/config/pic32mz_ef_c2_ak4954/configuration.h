/*******************************************************************************
  System Configuration Header

  File Name:
    configuration.h

  Summary:
    Build-time configuration header for the system defined by this project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options

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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/

#include "user.h"
#include "device.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: System Configuration
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************
/* TIME System Service Configuration Options */
#define SYS_TIME_INDEX_0                            (0)
#define SYS_TIME_MAX_TIMERS                         (5)
#define SYS_TIME_HW_COUNTER_WIDTH                   (32)
#define SYS_TIME_HW_COUNTER_PERIOD                  (4294967295U)
#define SYS_TIME_HW_COUNTER_HALF_PERIOD             (SYS_TIME_HW_COUNTER_PERIOD>>1)
#define SYS_TIME_CPU_CLOCK_FREQUENCY                (198000000)
#define SYS_TIME_COMPARE_UPDATE_EXECUTION_CYCLES    (620)



// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************
/* I2C Driver Instance 0 Configuration Options */
#define DRV_I2C_INDEX_0                       0
#define DRV_I2C_CLIENTS_NUMBER_IDX0           1
#define DRV_I2C_QUEUE_SIZE_IDX0               8
#define DRV_I2C_CLOCK_SPEED_IDX0              50000

/* I2S Driver Instance 0 Configuration Options */
#define DRV_I2S_INDEX_0                0
#define DRV_I2S_CLIENTS_NUMBER_IDX0    1
#define DRV_I2S_QUEUE_DEPTH_COMBINED                 (2*8)
#define DRV_I2S_QUEUE_SIZE_IDX0        8
#define DRV_I2S_DATA_LENGTH_IDX0       16
#define DRV_I2S_INT_SRC_IDX0           _DMA0_VECTOR
#define DRV_I2S_XMIT_DMA_CH_IDX0       SYS_DMA_CHANNEL_0
#define DRV_I2S_RCV_DMA_CH_IDX0        SYS_DMA_CHANNEL_1

/* I2C Driver Common Configuration Options */
#define DRV_I2C_INSTANCES_NUMBER              (1U)


/*** Codec Driver Configuration ***/

#define DRV_AK4954_CLIENTS_NUMBER                           1
#define DRV_AK4954_INSTANCES_NUMBER                         1

#define DRV_AK4954_I2S_MASTER_MODE                              false
#define DRV_AK4954_AUDIO_SAMPLING_RATE                      48000
#define DRV_AK4954_VOLUME	                      	        200
#define DRV_AK4954_AUDIO_DATA_FORMAT_MACRO             	    DRV_AK4954_AUDIO_DATA_FORMAT_I2S_16BIT_24BIT
#define DRV_AK4954_WHICH_MIC_INPUT                          MIC1
#define DRV_AK4954_ENABLE_MIC_BIAS                          true
#define DRV_AK4954_MIC_GAIN	                      	        20
#define DRV_AK4954_MCLK_SAMPLE_FREQ_MULTPLIER               256
#define DRV_AK4954_BCLK_BIT_CLK_DIVISOR                     4
#define DRV_AK4954_DELAY_INITIALIZATION                     false

#define DRV_AK4954_I2S_DRIVER_MODULE_INDEX_IDX0             DRV_I2S_INDEX_0
#define DRV_AK4954_I2C_DRIVER_MODULE_INDEX_IDX0             DRV_I2C_INDEX_0
/* CODEC Driver Abstraction definition */

#define DRV_CODEC_INDEX_0                                   DRV_AK4954_INDEX_0
#define sysObjdrvCodec0                                     sysObj.drvak4954Codec0
#define DRV_CODEC_I2S_MASTER_MODE                           DRV_AK4954_I2S_MASTER_MODE

#define DRV_CODEC_BUFFER_HANDLE                             DRV_AK4954_BUFFER_HANDLE
#define DRV_CODEC_BUFFER_HANDLE_INVALID                     DRV_AK4954_BUFFER_HANDLE_INVALID
#define DRV_CODEC_BUFFER_EVENT_HANDLER                      DRV_AK4954_BUFFER_EVENT_HANDLER
#define DRV_CODEC_BUFFER_EVENT                              DRV_AK4954_BUFFER_EVENT
#define DRV_CODEC_BUFFER_EVENT_COMPLETE                     DRV_AK4954_BUFFER_EVENT_COMPLETE
#define DRV_CODEC_BUFFER_EVENT_ERROR                        DRV_AK4954_BUFFER_EVENT_ERROR
#define DRV_CODEC_BUFFER_EVENT_ABORT                        DRV_AK4954_BUFFER_EVENT_ABORT

#define DRV_CODEC_COMMAND_EVENT_HANDLER                     DRV_AK4954_COMMAND_EVENT_HANDLER
#define DRV_CODEC_AUDIO_SAMPLING_RATE                       DRV_AK4954_AUDIO_SAMPLING_RATE
#define DRV_CODEC_WHICH_MIC_INPUT                           DRV_AK4954_WHICH_MIC_INPUT
#define DRV_CODEC_MIC_GAIN                                  DRV_AK4954_MIC_GAIN
#define DRV_CODEC_CHANNEL_LEFT                              DRV_AK4954_CHANNEL_LEFT
#define DRV_CODEC_CHANNEL_RIGHT                             DRV_AK4954_CHANNEL_RIGHT
#define DRV_CODEC_CHANNEL_LEFT_RIGHT                        DRV_AK4954_CHANNEL_LEFT_RIGHT

#define DRV_CODEC_Initialize                                DRV_AK4954_Initialize
#define DRV_CODEC_Deinitialize                              DRV_AK4954_Deinitialize
#define DRV_CODEC_Status                                    DRV_AK4954_Status
#define DRV_CODEC_ClientReady                               DRV_AK4954_ClientReady
#define DRV_CODEC_Tasks                                     DRV_AK4954_Tasks
#define DRV_CODEC_Open                                      DRV_AK4954_Open
#define DRV_CODEC_Close                                     DRV_AK4954_Close
#define DRV_CODEC_CommandEventHandlerSet                    DRV_AK4954_CommandEventHandlerSet
#define DRV_CODEC_BufferEventHandlerSet                     DRV_AK4954_BufferEventHandlerSet
#define DRV_CODEC_BufferAddWrite                            DRV_AK4954_BufferAddWrite
#define DRV_CODEC_BufferAddRead                             DRV_AK4954_BufferAddRead
#define DRV_CODEC_BufferAddWriteRead                        DRV_AK4954_BufferAddWriteRead
#define DRV_CODEC_WriteQueuePurge                           DRV_AK4954_WriteQueuePurge
#define DRV_CODEC_ReadQueuePurge                            DRV_AK4954_ReadQueuePurge
#define DRV_CODEC_SamplingRateSet                           DRV_AK4954_SamplingRateSet
#define DRV_CODEC_SamplingRateGet                           DRV_AK4954_SamplingRateGet
#define DRV_CODEC_VolumeSet                                 DRV_AK4954_VolumeSet
#define DRV_CODEC_VolumeGet                                 DRV_AK4954_VolumeGet
#define DRV_CODEC_MuteOn                                    DRV_AK4954_MuteOn
#define DRV_CODEC_MuteOff                                   DRV_AK4954_MuteOff
#define DRV_CODEC_MicGainSet                                DRV_AK4954_MicGainSet
#define DRV_CODEC_MicGainGet                                DRV_AK4954_MicGainGet
#define DRV_CODEC_MicMuteOn                                 DRV_AK4954_MicMuteOn
#define DRV_CODEC_MicMuteOff                                DRV_AK4954_MicMuteOff
#define DRV_CODEC_GetI2SDriver                              DRV_AK4954_GetI2SDriver
#define DRV_CODEC_LRCLK_Sync                                DRV_AK4954_LRCLK_Sync
#define DRV_CODEC_EnableInitialization                      DRV_AK4954_EnableInitialization    
#define DRV_CODEC_IsInitializationDelayed                   DRV_AK4954_IsInitializationDelayed         

/* I2S Driver Common Configuration Options */
#define DRV_I2S_INSTANCES_NUMBER              1



// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // CONFIGURATION_H
/*******************************************************************************
 End of File
*/
