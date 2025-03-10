/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
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

#include "device.h"
#include "plib_clock.h"
#include "interrupts.h"




/*********************************************************************************
Initialize Slow Clock (SLCK)
*********************************************************************************/

static void CLK_SlowClockInitialize(void)
{
    /* 32KHz Crystal Oscillator is selected as the Slow Clock (SLCK) source.
       Enable 32KHz Crystal Oscillator  */
    SUPC_REGS->SUPC_CR |= SUPC_CR_KEY_PASSWD | SUPC_CR_XTALSEL_CRYSTAL_SEL;

    /* Wait until the 32K Crystal oscillator clock is ready and
       Slow Clock (SLCK) is switched to 32KHz Oscillator */
    while ((SUPC_REGS->SUPC_SR & SUPC_SR_OSCSEL_Msk) == 0U)
    {
    }

}


/*********************************************************************************
Initialize Main Clock (MAINCK)
*********************************************************************************/
static void CLK_MainClockInitialize(void)
{

    /* Enable the RC Oscillator */
    PMC_REGS->CKGR_MOR|= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCRCEN_Msk;

    /* Wait until the RC oscillator clock is ready. */
    while( (PMC_REGS->PMC_SR & PMC_SR_MOSCRCS_Msk) != PMC_SR_MOSCRCS_Msk)
    {

    }

    /* Configure the RC Oscillator frequency */
    PMC_REGS->CKGR_MOR = (PMC_REGS->CKGR_MOR & ~CKGR_MOR_MOSCRCF_Msk) | CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCRCF_8_MHz;

    /* Wait until the RC oscillator clock is ready */
    while( (PMC_REGS->PMC_SR& PMC_SR_MOSCRCS_Msk) != PMC_SR_MOSCRCS_Msk)
    {

    }

    /* Main RC Oscillator is selected as the Main Clock (MAINCK) source.
       Switch Main Clock (MAINCK) to the RC Oscillator clock */
    PMC_REGS->CKGR_MOR = (PMC_REGS->CKGR_MOR & ~CKGR_MOR_MOSCSEL_Msk) | CKGR_MOR_KEY_PASSWD;

}

/*********************************************************************************
Initialize PLLA (PLLACK)
*********************************************************************************/

static void CLK_PLLAInitialize(void)
{
    /* Configure and Enable PLLA */
    PMC_REGS->CKGR_PLLAR = CKGR_PLLAR_ZERO(0U) | CKGR_PLLAR_PLLACOUNT(0x3fU) |
                              CKGR_PLLAR_MULA(5999U) | CKGR_PLLAR_PLLAEN(1U) ;

    while ( (PMC_REGS->PMC_SR & PMC_SR_LOCKA_Msk) != PMC_SR_LOCKA_Msk)
    {

    }

}

/*********************************************************************************
Initialize PLLB (PLLBCK)
*********************************************************************************/

static void CLK_PLLBInitialize(void)
{
    /* Configure and Enable PLLB */
    PMC_REGS->CKGR_PLLBR = CKGR_PLLBR_ZERO(0) | CKGR_PLLBR_PLLBCOUNT(0x3f) |
                              CKGR_PLLBR_MULB(1463) | CKGR_PLLBR_PLLBEN(1);

    while ( (PMC_REGS->PMC_SR & PMC_SR_LOCKB_Msk) != PMC_SR_LOCKB_Msk)
    {
        /* Wait */
    }

}

/*********************************************************************************
Initialize Master clock (MCK)
*********************************************************************************/

static void CLK_MasterClockInitialize(void)
{
    /* Program PMC_MCKR.PRES and wait for PMC_SR.MCKRDY to be set   */
    PMC_REGS->PMC_MCKR = (PMC_REGS->PMC_MCKR & ~PMC_MCKR_PRES_Msk) | PMC_MCKR_PRES_CLK_1| PMC_MCKR_PLLADIV2_Msk;
    while ((PMC_REGS->PMC_SR & PMC_SR_MCKRDY_Msk) != PMC_SR_MCKRDY_Msk)
    {

    }

    /* Program PMC_MCKR.CSS and Wait for PMC_SR.MCKRDY to be set    */
    PMC_REGS->PMC_MCKR = (PMC_REGS->PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_PLLA_CLK;
    while ((PMC_REGS->PMC_SR & PMC_SR_MCKRDY_Msk) != PMC_SR_MCKRDY_Msk)
    {

    }

}




/*********************************************************************************
Initialize Programmable Clock (PCKx)
*********************************************************************************/

static void CLK_ProgrammableClockInitialize(void)
{
    /* Disable selected programmable clock  */
    PMC_REGS->PMC_SCDR = PMC_SCDR_PCK2_Msk | PMC_SCDR_PCK4_Msk | PMC_SCDR_PCK7_Msk;

    /* Configure selected programmable clock    */
    PMC_REGS->PMC_PCK[2]= PMC_PCK_CSS_PLLB_CLK | PMC_PCK_PRES(3);
    PMC_REGS->PMC_PCK[4]= PMC_PCK_CSS_PLLB_CLK | PMC_PCK_PRES(3);
    PMC_REGS->PMC_PCK[7]= PMC_PCK_CSS_PLLB_CLK | PMC_PCK_PRES(0);

    /* Enable selected programmable clock   */
    PMC_REGS->PMC_SCER =    PMC_SCER_PCK2_Msk | PMC_SCER_PCK4_Msk | PMC_SCER_PCK7_Msk;

    while( (PMC_REGS->PMC_SR & (PMC_SR_PCKRDY2_Msk | PMC_SR_PCKRDY4_Msk | PMC_SR_PCKRDY7_Msk) ) != (PMC_SR_PCKRDY2_Msk | PMC_SR_PCKRDY4_Msk | PMC_SR_PCKRDY7_Msk))
    {
        /* Wait for clock to be ready   */
    }


}


/*********************************************************************************
Clock Initialize
*********************************************************************************/
void CLOCK_Initialize( void )
{
    /* Initialize Slow Clock */
    CLK_SlowClockInitialize();

    /* Initialize Main Clock */
    CLK_MainClockInitialize();

    /* Initialize PLLA */
    CLK_PLLAInitialize();

    /* Initialize PLLB */
    CLK_PLLBInitialize();

    /* Initialize Master Clock */
    CLK_MasterClockInitialize();


    /* Initialize Programmable Clock */
    CLK_ProgrammableClockInitialize();

    /* Enable Peripheral Clock */
    PMC_REGS->PMC_PCER0 = 0xc11880;
}

