/*******************************************************************************
  I2SC PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_i2sc0.h

  Summary:
    I2SC0 PLIB Header File

  Description:
    This file has the prototypes of all the interfaces provided for one
    particular instance of the Inter-IC Sound Controller (I2SC) peripheral.

*******************************************************************************/

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

#ifndef PLIB_I2SC0_H
#define PLIB_I2SC0_H

#include <stdint.h>
#include <stdbool.h>

#include "device.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus  

    extern "C" {

#endif

/****************************** I2SC0 Interface *********************************/

void I2SC0_Initialize(void);

uint32_t I2SC0_LRCLK_Get(void);
//KEEP THIS - Not used for G55
#if 0
uint32_t I2SC0_GenericClockSet(const uint8_t div2);
uint32_t I2SC0_ProgrammableClockSet(const uint8_t pClkNum, const uint8_t div2);
uint32_t I2SC0_PLLAClockSet(const uint8_t div, const uint8_t mul);
#endif //0

//KEEP THIS - G55 I2SC Plib Functionality
void     I2SC0_Enable_Transmission(void);
void     I2SC0_Disable_Transmission(void);
void     I2SC0_Enable_Reception(void);
void     I2SC0_Disable_Reception(void);
void     I2SC0_Enable_Clocks(void);
void     I2SC0_Disable_Clocks(void);
uint32_t I2SC0_Get_Status(void);

#define USE_PDC1
#define PDC1_I2SC0 ((pdc_registers_t *)0x40000200U)
#define PDC2_I2SC0 ((pdc_registers_t *)0x40000100U)

//******************** PDC G55 Specific Definitions ****************************
typedef enum
{
    /* Data was transferred successfully. */
    PDC_TX_COMPLETE,
    PDC_RX_COMPLETE,

    /* Error while processing the request */
    PDC_TRANSFER_ERROR

} PDC_TRANSFER_EVENT;

typedef struct pdc_packet {
	/** Start address of the transfer packet data. */
	uint32_t ul_addr;
	/** Transfer packet size (in units of the peripheral data width). */
	uint32_t ul_size;
} pdc_packet_t;

typedef void (*PDC_CHANNEL_CALLBACK) (PDC_TRANSFER_EVENT event, uintptr_t contextHandle);

typedef struct
{
    uint8_t                inUse;
    PDC_CHANNEL_CALLBACK   txCallback;
    PDC_CHANNEL_CALLBACK   rxCallback;
    uintptr_t              context;
    uint8_t                busyStatus;

} PDC_CH_OBJECT;  


void PDC_Initialize(void);
void PDC_I2SC0_ChannelStartTransfer(void);
void PDC_I2SC0_ChannelTransfer(const void * txAddr, 
                               const void * rxAddr, 
                               size_t blockSize_bytes);
void PDC_I2SC0_ChannelNextTxTransfer(const void * txAddr, 
                               size_t blockSize_bytes);
void PDC_I2SC0_ChannelNextRxTransfer(const void * rxAddr, 
                               size_t blockSize_bytes);
void PDC_TxChannelCallbackRegister(const PDC_CHANNEL_CALLBACK txEventHandler, 
                                   const uintptr_t contextHandle);
void PDC_RxChannelCallbackRegister(const PDC_CHANNEL_CALLBACK rxEventHandler, 
                                   const uintptr_t contextHandle);
void PDC_TransferCompleteHandler(void);
bool PDC_ChannelIsBusy(void);
bool PDC_ChannelEndTransmit(void);
bool PDC_ChannelEndReceive(void);
void PDC_ChannelDisable(void);

extern PDC_CH_OBJECT  pdcChObj;

/* Provide C++ Compatibility */
#ifdef __cplusplus

    }
    
#endif

#endif // PLIB_I2SC0_H

/*******************************************************************************
 End of File
*/
