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
#include "Asynchronous_Morse_Code_Generator.h"
#include "Debug_Trace.h"

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
 *  Variables and Constense
*******************************************************************************/
static uint8 Cold_Init = STD_OFF;

/* Handle for BackGroundMoniteringTask */
TaskHandle_t Web_Server_Processing_Task_Handle;
/* Handle for ProcessControlSystem_Task */
TaskHandle_t ProcessControlSystem_Task_Handle;

/* Handle for ProcessWaterFlowRate_Task */
TaskHandle_t ProcessWaterFlowRate_Task_Handle;

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
  
  /* Init required variables*/
  Init_System_Utilityes_Variables();

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
      Web_Server_Processing_Task,         /* Task function. */
      "Web_Server_Processing_Task",       /* name of task. */
      5120,                               /* 5K Stack size of task */
      NULL,                               /* parameter of the task */
      1,                                  /* priority of the task, Grater the value Higher the priority.*/
      &Web_Server_Processing_Task_Handle, /* Task handle to keep track of created task */
      1);                                 /* pin task to core 1, Along with loop() function. */


  /* Initate High Priority control System Process Monitering Task. */
  xTaskCreatePinnedToCore(
      ProcessControlSystem_Task,        /* Task function. */
      "ProcessControlSystem_Task",      /* name of task. */
      5120,                             /* 5K Stack size of task */
      NULL,                             /* parameter of the task */
      20,                               /* priority of the task, Grater the value Higher the priority.*/
      &ProcessControlSystem_Task_Handle,/* Task handle to keep track of created task */
      0);                               /* pin task to core 1, Along with loop() function. */


  /* Initate Task for Calculating the water flow rate in Lpm. */
  xTaskCreatePinnedToCore(
      ProcessWaterFlowRate_Task,        /* Task function. */
      "ProcessWaterFlowRate_Task",      /* name of task. */
      1024,                             /* 5K Stack size of task */
      NULL,                             /* parameter of the task */
      5,                               /* priority of the task, Grater the value Higher the priority.*/
      &ProcessWaterFlowRate_Task_Handle,/* Task handle to keep track of created task */
      0);                               /* pin task to core 1, Along with loop() function. */



 /* Init the Morse code Generator  */
  Morse_Code_Init();
}

void loop()
{ 


  /* TRigger Cold Init Statement if any*/
  IfCold_Init();







  /* Keep this Loop Ideal for around 1 Second. As Not expected to do much critival processing*/
  Delay_In_ms(1000);

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
   Priority   :-  1 (Lowest)
   Core       :-  1
 * *********************************************************************************/
void Web_Server_Processing_Task( void * pvParameters ){

  /* Init the Web server, Only first time.*/
  Web_Server_Init();

  /* Loop for the task.*/
  for(;;){

   /********************************************************************************
    *  Add Code after this line....
    * ******************************************************************************
   */

    /* Trigger function to do monitering and log the info in every 200ms */
     Web_Server_Processing();

   
   /* Switch task for 200ms */
   vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}



/* ********************************************************************************
 * Task for process Main Control system based on the Different Inputs
   Periodicity:-  50ms
   Priority   :-  20 (Highest)
   Core       :-  0
 * *********************************************************************************/
void ProcessControlSystem_Task( void * pvParameters ){
  /* Loop for the task.*/
  for(;;){

   /********************************************************************************
    *  Add Code after this line....
    * ******************************************************************************
   */

    /* Trigger function to do processing in every 50ms */
     Process_ControlSystem();

   
   /* Switch task for 50ms */
   vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}


/* ********************************************************************************
 * Task for process water flow rate
   Periodicity:-  1000ms
   Priority   :-  5 (Highest)
   Core       :-  0
 * *********************************************************************************/
void ProcessWaterFlowRate_Task( void * pvParameters ){
  /* Loop for the task.*/
  for(;;){

   /********************************************************************************
    *  Add Code after this line....
    * ******************************************************************************
   */

    /* Trigger the runnable to do processing in every 1000ms */
     ProcessWaterFlowRate();

   
   /* Switch task for 1000ms */
   vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}


