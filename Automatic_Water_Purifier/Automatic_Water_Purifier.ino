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

  /* Perform NVM init, It must be called befor all init, because most of the configuration data are present bu NVM.*/
  Init_NVM_Stack();

  /* Test NVM based on the configuration.*/
  NVM_READ_Write_Test();

  /* Initate the Micro Settings. */
  Init_MCU();




  /* Initialise all timmer and External interrupts*/
  Init_GPT_ICU();
}




void loop()
{ 
  /* TRigger Cold Init Statement if any*/
  IfCold_Init();

  



}

/*
===========================================================================
===========================================================================
                      Custom Functions 
===========================================================================
===========================================================================
*/


/* ********************************************************************************
 * Function to Trigger all Cold Init Steps in Cyclic task.
 * *********************************************************************************/
void IfCold_Init(void)
{
    /* Excute first time only.*/
  if(Cold_Init == STD_OFF)
  {
    /* Dissable Cold Init*/
    Cold_Init = STD_ON;

    /*
    ================================================================
     * Please Place Cold Init Codes below.
    ================================================================
    */



  }
  else
  {
     /* Do nothing. */
  }
}



