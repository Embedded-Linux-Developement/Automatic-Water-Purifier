
#ifndef Automatic_Water_Purifier_H
#define Automatic_Water_Purifier_H

#include "MyStdTypes.h"

/*******************************************************************************
 *  For Other Configurations 
 *  1. Please configure NVM related points in "ESP32_NVM_Stack.h" file.
 *  2. Please configure Debug trace related settings in Generic_Utilityes.h file.
 *  3. For Port related configuration, please refer System_Utilityes.h file.
 * 
*******************************************************************************/


/*******************************************************************************
 *  Configuration Start
*******************************************************************************/

/* Following are the Configurations related to the Networking.*/
/* Default name for recovery Access Point.*/ 
/* If configured WiFi are not available then shall Automaticaly switch to below mentioned AP. 
   And after login into this access point you can configure new WiFi Pasword if needed.
   User name and pasword of AP is not configuriable because its a recovery mechanism.
   */
#define AP_Name "Automatic_Water_Purifier"
#define AP_Pasword "IamPayyampallil"




/*-----------------------------------------------------------------------------
 *  Configuration END
-------------------------------------------------------------------------------*/

/*******************************************************************************
 *  Program Specific Macros.
*******************************************************************************/


/*******************************************************************************
 *  Macro Functions
*******************************************************************************/



/*******************************************************************************
 *  Public Function Definations Functions
*******************************************************************************/



/*
===========================================================================
          Public functions related to System Operatations
===========================================================================
*/
extern void Init_MCU(void);
extern void Init_GPT_ICU(void);
extern void Perform_Reset(void);



#endif /* End of  Automatic_Water_Purifier_H */
