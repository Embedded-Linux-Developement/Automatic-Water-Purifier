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

/* Handle for BackGroundMoniteringTask */
TaskHandle_t BackGroundMoniteringTask_Handle;

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

  /* Init the water Flow meter*/
  Init_PulseCounter();

  /* Initialise all timmer and External interrupts*/
  Init_GPT_ICU();

  /* Initate all required Perodic task*/

  /* Initate Low Priority Background Process Monitering Task */
  xTaskCreatePinnedToCore(
      BackGroundMoniteringTask,         /* Task function. */
      "BackGroundMoniteringTask",       /* name of task. */
      5120,                             /* 5K Stack size of task */
      NULL,                             /* parameter of the task */
      20,                               /* priority of the task */
      &BackGroundMoniteringTask_Handle, /* Task handle to keep track of created task */
      1);                               /* pin task to core 1, Along with loop() function. */


      
}

void loop()
{ 


  /* TRigger Cold Init Statement if any*/
  IfCold_Init();







  /* Keep this Loop Ideal for around 1 Second. As Not expected to do much critival processing*/
  delay(1000);

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



/*
===========================================================================
===========================================================================
                      Custom Additional task 
===========================================================================
===========================================================================
*/


/* ********************************************************************************
 * Task for process back ground for Monitering different paramater.
   Periodicity:-  200ms
   Priority   :-  20 (Lowest)
 * *********************************************************************************/
void BackGroundMoniteringTask( void * pvParameters ){
  /* Loop for the task.*/
  for(;;){

   /********************************************************************************
    *  Add Code after this line....
    * ******************************************************************************
   */

    /* Trigger function to do monitering and log the info in every 200ms */
     Monitor_ControlSystem();

   
   /* Switch task for 200ms */
   vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}



