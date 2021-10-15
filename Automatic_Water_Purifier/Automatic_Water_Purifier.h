
#ifndef Automatic_Water_Purifier_H
#define Automatic_Water_Purifier_H

#include "MyStdTypes.h"

/*****************************************************************************************************
File belongings to  Automatic_Water_Purifier program in githib, 
Link to Program GitHub Repository:- https://github.com/Embedded-Linux-Developement/Automatic-Water-Purifier
Description:- On of the file  Automatic Water Purifier, 
              Its a fully automatic water purifier Supporting code.

Copy Write:- 
Licence:- 
    <Automatic Water Purifier>
    Copyright (C) 2021  Jerry James

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

Auther:- Jerry James
E-mail:- Jerrymbc@gmail.com
Date  :- 15 Sep 2021
version:- V2.0.1

*******************************************************************************************************/

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
