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
    
#define BUTTON_DEBOUNCE 50
#define LONG_BUTTON_PRESS 1000

#undef NOPRINT
#ifdef NOPRINT
#define SYS_PRINT(fmt, ...)    
#define SYS_MESSAGE(fmt)      
#else
#define SYS_PRINT(fmt, ...)    SYS_DEBUG_PRINT(0, fmt, ##__VA_ARGS__)
#define SYS_MESSAGE(fmt)       SYS_DEBUG_PRINT(0, fmt)
#endif

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // USER_H
/*******************************************************************************
 End of File
*/
