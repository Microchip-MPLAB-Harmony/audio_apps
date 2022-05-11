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
 * File:   assert.h
 * Author: C16825
 *
 * Created on July 29, 2020, 4:39 PM
 */

#ifndef ASSERT_H
#define	ASSERT_H

#include "system/debug/sys_debug.h"

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef SYS_ASSERT
#define SYS_ASSERT(test,msg) \
    ((test) \
        ? (void)0 \
        : __assert_func( \
            __FILE__, \
            __LINE__, \
            __PRETTY_FUNCTION__, \
            #msg, \
            #test) \
    )
#endif //SYS_ASSERT

void user_assert_func( char * file, int line, const char * func, char * msg, char * expr); 

#ifdef	__cplusplus
}
#endif

#endif	/* ASSERT_H */

