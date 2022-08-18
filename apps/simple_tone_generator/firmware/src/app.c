/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
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

#include "app.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_I2C_TEMP_SENSOR_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

// 48 samples, played out at 48,000 samples per second => 1 kHz tone
int16_t samples [NUM_SAMPLES] =
{                        
0, -4061, -8059, -11911, -15566, -18950, -22013, -24695,
-26961, -28757, -30072, -30861, -31132, -30861, -30071, -28758,
-26961, -24695, -22013, -18950, -15566, -11911, -8060, -4059,
0, 4064, 8058, 11910, 15569, 18946, 22016, 24693,
26963, 28757, 30070, 30864, 31128, 30865, 30068, 28760,
26959, 24697, 22011, 18953, 15562, 11915, 8054, 4066
};

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )
 */

void APP_Initialize ( void )
{
    /* Initialize the Temperature Sensor Application data */
    appData.state          = APP_STATE_CODEC_OPEN;
    
    appData.sample_index = 0;
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )
 */

void APP_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( appData.state)
    {           
        case APP_STATE_CODEC_OPEN:
        {
			// see if codec is done initializing
            SYS_STATUS status = DRV_CODEC_Status(sysObjdrvCodec0);
            if (SYS_STATUS_READY == status)
            {
                // This means the driver can now be be opened.
                /* A client opens the driver object to get an Handle */
                appData.codec_handle = DRV_CODEC_Open(DRV_CODEC_INDEX_0, 
                    DRV_IO_INTENT_WRITE | DRV_IO_INTENT_EXCLUSIVE);
                
                if(appData.codec_handle != DRV_HANDLE_INVALID)
                {                       
                    appData.state = APP_STATE_IDLE;
                    LED1_On();      // indicate codec opened
                }            
            }
        }
        break;                                              
        
        case APP_STATE_IDLE:
        {      
            if (I2SC0_REGS->I2SC_SR & I2SC_SR_TXRDY_Msk)
            {
                // send each one twice (left, right))
                I2SC0_REGS->I2SC_THR = samples[appData.sample_index >> 1];

                appData.sample_index++;                    
                if (appData.sample_index >= 2*NUM_SAMPLES)
                {
                    appData.sample_index = 0;

                    LED2_Toggle();            
                }
            }
        }
        break;            
    }    
}

/*******************************************************************************
 End of File
 */