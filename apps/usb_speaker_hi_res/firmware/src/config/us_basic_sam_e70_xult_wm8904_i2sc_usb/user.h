/*******************************************************************************
  User Configuration Header

  File Name:
    user.h

  Summary:
    Build-time configuration header for the user defined by this project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    It only provides macro definitions for build-time configuration options

*******************************************************************************/

#ifndef USER_H
#define USER_H

#include <stdio.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: User Configuration macros
// *****************************************************************************
// *****************************************************************************


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#undef NOPRINT
#ifdef NOPRINT
#define SYS_PRINT(fmt, ...)    
#define SYS_MESSAGE(fmt)      
#else
#define SYS_PRINT(fmt, ...)    printf(fmt, ##__VA_ARGS__)
#define SYS_MESSAGE(fmt)       printf(fmt)
#endif


#undef APP_CODEC_MASTER

#endif // USER_H
/*******************************************************************************
 End of File
*/
