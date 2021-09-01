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

