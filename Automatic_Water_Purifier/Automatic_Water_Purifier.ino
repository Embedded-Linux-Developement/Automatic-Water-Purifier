/*******************************************************************************
 *  External Includes
*******************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "Automatic_Water_Purifier.h"
#include "ESP32_NVM_Stack.h"
#include "Generic_Utilityes.h"
#include "System_Utilityes.h"


/*******************************************************************************
 *  Variables and Constense
*******************************************************************************/
static uint8 Cold_Init = STD_OFF;
/*******************************************************************************
 *  Functions Extern deceleration
*******************************************************************************/


/*******************************************************************************
 *  Class Objects.
*******************************************************************************/

/*******************************************************************************
 *  Startup Functions
*******************************************************************************/
void setup()
{
  /* Enable Cold Init*/
  Cold_Init = STD_OFF;

  /* Init Debug Trace, if enabled...*/
  Init_Trace();

  /* Initate the Micro Settings. */
  Init_MCU();
  /* Perform NVM read operatations.*/
  Init_NVM_Stack();

  /* Test NVM based on the configuration.*/
  NVM_READ_Write_Test();

  /* Initialise all timmer and External interrupts*/
  Init_GPT_ICU();
}

void loop()
{ 
  uint8 Temp;
  /* Excute first time only.*/
  if(Cold_Init == STD_OFF)
  {
    /* Dissable Cold Init*/
    Cold_Init = STD_ON;


     //Nvm_Write_Each(NVM_ID_Seting_HighPresureAction, (uint32) Recovery_On_PowerOn);

  }
  



}

/*
===========================================================================
===========================================================================
                      Custom Functions 
===========================================================================
===========================================================================
*/




