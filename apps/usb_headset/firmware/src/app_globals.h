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

/* 
 * File:   app_globals.h
 * Author: C16825
 *
 * Created on April 16, 2020, 3:45 PM
 */

#ifndef APP_GLOBALS_H
#define	APP_GLOBALS_H

#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define NUMSTATES 16
//#define NUMSTATES 12
extern const char * stateStr[NUMSTATES];
extern const char * usbDevEventStr[];
extern const char * usbAudioEventStr[];

typedef enum _ERROR_NUM 
    {ERR_CODEC, ERR_CODEC_EVENT, ERR_CODEC_BUFFER, 
     ERR_USB, ERR_USB_BUFFER, ERR_GENERIC} ERROR_NUM;
ERROR_NUM errNum;


extern const char * ERROR_STR[]; 
extern bool errState;

#ifdef	__cplusplus
}
#endif

#endif	/* APP_GLOBALS_H */

