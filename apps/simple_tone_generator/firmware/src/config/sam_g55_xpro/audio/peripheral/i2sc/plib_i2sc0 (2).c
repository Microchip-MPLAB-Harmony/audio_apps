/*******************************************************************************
  I2SC PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_i2sc0.c

  Summary:
    I2SC0 Source File

  Description:
    This file has the implementation of all the interfaces provided for one
    particular instance of the Inter-IC Sound Controller (I2SC) peripheral.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2018-2019 Microchip Technology Inc. and its subsidiaries.
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

#include "plib_i2sc0.h"

// *****************************************************************************
// *****************************************************************************
// Section: I2SC0 Implementation
// *****************************************************************************
// *****************************************************************************

void I2SC0_Initialize ( void )
{
    // Disable and reset the I2SC
    I2SC0_REGS->I2SC_CR = I2SC_CR_TXDIS_Msk | I2SC_CR_RXDIS_Msk | I2SC_CR_CKDIS_Msk;
    I2SC0_REGS->I2SC_CR = I2SC_CR_SWRST_Msk;
       
    I2SC0_REGS->I2SC_MR = I2SC_MR_MODE(1) |		// Master/Slave Mode		
                            I2SC_MR_DATALENGTH(0x4) |	// Data Word Length
                            I2SC_MR_RXMONO(0) |		// Receiver Mono/Stereo
                            I2SC_MR_RXDMA(0) |		// # of DMA Channels for Receiver
                            I2SC_MR_RXLOOP(0) | 	// Loopback Test Mode
                            I2SC_MR_TXMONO(0) |		// Transmitter Mono/Stereo
                            I2SC_MR_TXDMA(0) |		// # of DMA Channels for Transmitter
                            I2SC_MR_TXSAME(0) |		// Transmit Data When Underrun
                            I2SC_MR_IMCKDIV(15) |	// Selected Clock to IMCK Ratio
                            I2SC_MR_IMCKFS(0x1F) |		// Master Clock to Sample Rate Ratio
                            I2SC_MR_IMCKMODE(1) |	// Master Clock Mode
                            I2SC_MR_IWS(0);		// Slot Width
    
   //KEEP THIS-  Not Enabled Here
    // Enable the I2SC
   // I2SC0_REGS->I2SC_CR = I2SC_CR_TXEN_Msk | I2SC_CR_RXEN_Msk | I2SC_CR_CKEN_Msk;
   // while(!(I2SC0_REGS->I2SC_SR & I2SC_SR_TXEN_Msk));
    
   //Interrupts
   //I2SC0_REGS->I2SC_IER = I2SC_IER_ENDRX_Msk |  //End of Reception 
   //                       I2SC_IER_ENDTX_Msk;   //End of Transmission 
}

uint32_t I2SC0_LRCLK_Get(void)
{
    // for I2S format, will sync on low to high transition
    volatile uint32_t ret = ((PIOA_REGS->PIO_PDSR >> 1) & 0x1);
    return ret;    
}


//KEEP THIS -- G55 PDC Dma Controller
//*************************** G55 PDC Specific Code ***************************
void I2SC0_Enable_Transmission(void)
{
    I2SC0_REGS->I2SC_CR = I2SC_CR_TXEN(1);  //Transmit Enable
}

void I2SC0_Disable_Transmission(void)
{
    I2SC0_REGS->I2SC_CR = I2SC_CR_TXDIS(1);  //Transmit Disable
}

void I2SC0_Enable_Reception(void)
{
    I2SC0_REGS->I2SC_CR = I2SC_CR_RXEN(1);  //Receive Enable
}

void I2SC0_Disable_Reception(void)
{
    I2SC0_REGS->I2SC_CR = I2SC_CR_RXDIS(1);  //Receive Disable
}

void I2SC0_Enable_Clocks(void)
{
    I2SC0_REGS->I2SC_CR = I2SC_CR_CKEN(1);  //Clock enable
}

void I2SC0_Disable_Clocks(void)
{
    I2SC0_REGS->I2SC_CR = I2SC_CR_CKDIS(1);  //Clock Disable
}

uint32_t I2SC0_Get_Status(void)    
{
    return I2SC0_REGS->I2SC_SR;
}

void I2SC0_InterruptHandler()
{   
    PDC_TransferCompleteHandler();
}


//******************************** PDC API ************************************
//******************************************************************************
//  Setup PDC DMA for the I2SC0
//******************************************************************************

PDC_CH_OBJECT  pdcChObj;

void PDC_Initialize()
{
    pdcChObj.txCallback = NULL;
    pdcChObj.rxCallback = NULL;

    pdcChObj.context = 0;
    pdcChObj.busyStatus = false;
}

//******************************************************************************
//  End of DMA Transfer Interrupt Callback
//******************************************************************************
void PDC_TxChannelCallbackRegister(const PDC_CHANNEL_CALLBACK txEventHandler, 
                                   const uintptr_t contextHandle )
{
    pdcChObj.txCallback = txEventHandler;
    pdcChObj.context  = contextHandle;
}
//******************************************************************************
//  End of DMA Transfer Interrupt Callback
//******************************************************************************
void PDC_RxChannelCallbackRegister( const PDC_CHANNEL_CALLBACK rxEventHandler, 
                                   const uintptr_t contextHandle )
{
    pdcChObj.rxCallback = rxEventHandler;
    pdcChObj.context  = contextHandle;
}

//******************************************************************************
//******************************************************************************
void PDC_TransferCompleteHandler()
{
        if (NULL != pdcChObj.rxCallback)
        {
            pdcChObj.rxCallback(PDC_TRANSFER_ERROR, pdcChObj.context);
        }
}


//******************************************************************************
//  Initiate DMA Transfer
//******************************************************************************
void PDC_I2SC0_ChannelTransfer(const void *txAddr, 
                               const void *rxAddr,
                               size_t blockSize_bytes)
{
    pdc_registers_t * pdc1 = PDC1_I2SC0;   //TRANSMIT 
    pdc_registers_t * pdc2 = PDC2_I2SC0;   //RECEIVE
    pdc_packet_t pdc_i2sc_packet_tx, pdc_i2sc_packet_rx;
         
    //TX Buffer
    pdc_i2sc_packet_tx.ul_addr = (uint32_t)txAddr;
    pdc_i2sc_packet_tx.ul_size = blockSize_bytes/2; //#16 bit words
    //pdc_i2sc_packet_tx.ul_size = blockSize_bytes/4; //#32 bit words

    //RX Buffer
    pdc_i2sc_packet_rx.ul_addr = (uint32_t)rxAddr;
    pdc_i2sc_packet_rx.ul_size = blockSize_bytes/2; //#16 bit words
    //pdc_i2sc_packet_rx.ul_size = blockSize_bytes/4; //#32 bit words
  
    //Registers PDC 
    pdc1->PDC_PERIPH_TPR = pdc_i2sc_packet_tx.ul_addr;
    pdc1->PDC_PERIPH_TCR = pdc_i2sc_packet_tx.ul_size;
    
    //pdc1->rx init
    pdc1->PDC_PERIPH_RPR = pdc_i2sc_packet_rx.ul_addr;
    pdc1->PDC_PERIPH_RCR = pdc_i2sc_packet_rx.ul_size;    
    
    //Registers PDC2
    pdc2->PDC_PERIPH_TPR = 0;
    pdc2->PDC_PERIPH_TCR = 1;
    pdc2->PDC_PERIPH_RPR = 0;
    pdc2->PDC_PERIPH_RCR = 1;
}

void PDC_I2SC0_ChannelStartTransfer(void)
{
    pdc_registers_t * pdc1 = PDC1_I2SC0;
    
    //Enable transfer
    pdc1->PDC_PERIPH_PTCR = PDC_PERIPH_PTCR_RXTEN(1) | PDC_PERIPH_PTCR_TXTEN(1);  

    //Enable transmit
    I2SC0_Enable_Transmission();
    
    //Enable recv
    I2SC0_Enable_Reception();
    
    //Enable i2s clock
    I2SC0_Enable_Clocks();

    pdcChObj.busyStatus = true;
} //End PDC_ChannelTransfer()

//******************************************************************************
//  Continue DMA Transfer
//******************************************************************************

void PDC_I2SC0_ChannelNextTxTransfer(const void *txAddr, 
                               size_t blockSize_bytes)
{
    pdc_registers_t * pdc1 = PDC1_I2SC0;
    pdc_packet_t pdc_i2sc_packet_tx;
         
    //TX Buffer
    pdc_i2sc_packet_tx.ul_addr = (uint32_t)txAddr;
    pdc_i2sc_packet_tx.ul_size = blockSize_bytes/2;//#16 bit words
    //pdc_i2sc_packet_tx.ul_size = blockSize_bytes/4;//#32 bit words
  
    //Registers PDC 
    pdc1->PDC_PERIPH_TNPR = pdc_i2sc_packet_tx.ul_addr;
    pdc1->PDC_PERIPH_TNCR = pdc_i2sc_packet_tx.ul_size;
} //End PDC_ChannelNextTxTransfer()

void PDC_I2SC0_ChannelNextRxTransfer(const void *rxAddr, 
                               size_t blockSize_bytes)
{
    pdc_registers_t * pdc1 = PDC1_I2SC0;
    pdc_packet_t pdc_i2sc_packet_rx;

    //RX Buffer
    pdc_i2sc_packet_rx.ul_addr = (uint32_t)rxAddr;
    pdc_i2sc_packet_rx.ul_size = blockSize_bytes/2; //#16 bit words
    //pdc_i2sc_packet_rx.ul_size = blockSize_bytes/4; //#32 bit words
  
    //Registers PDC    
    pdc1->PDC_PERIPH_RNPR = pdc_i2sc_packet_rx.ul_addr;
    pdc1->PDC_PERIPH_RNCR = pdc_i2sc_packet_rx.ul_size;
} //End PDC_ChannelNextRxTransfer()

//******************************************************************************
// Check if Channel is Busy
//******************************************************************************
bool PDC_ChannelIsBusy()
{
	return (!(I2SC0_Get_Status() & I2SC_SR_RXBUFF(1)));
}

//******************************************************************************
// Check if Transmit finished
//******************************************************************************
bool PDC_ChannelEndTransmit(void)
{
	return (I2SC0_Get_Status() & I2SC_SR_ENDTX_Msk);
}

//******************************************************************************
// Check if Receive finished
//******************************************************************************
bool PDC_ChannelEndReceive(void)
{
	return (I2SC0_Get_Status() & I2SC_SR_ENDRX_Msk);
}

//******************************************************************************
// Disable I2SC0 DMA
//******************************************************************************
void PDC_ChannelDisable()
{
    I2SC0_REGS->I2SC_CR = I2SC_CR_RXDIS(1);  //Receive Disable
    I2SC0_REGS->I2SC_CR = I2SC_CR_TXDIS(1);  //Transmit Disable
}

/*******************************************************************************
 End of File
*/

