/*******************************************************************************
 *  External Includes
*******************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "MyStdTypes.h"
#include "ESP32_NVM_Stack.h"
#include "Generic_Utilityes.h"
#include "System_Utilityes.h"


/*******************************************************************************
 *  Variables and Constense
*******************************************************************************/


/*******************************************************************************
 *  Functions Extern deceleration
*******************************************************************************/


/*******************************************************************************
 *  Class Objects.
*******************************************************************************/


/*
===========================================================================
===========================================================================
          Public functions related to System Operatations
===========================================================================
==========================================================================
*/

/* ************************************************************************
 * Function to Initialise all System related functions.
 * *************************************************************************/
void Init_MCU(void)
{
  /* Start WDG */


  /* Initializes all port settings.*/



}

/* ************************************************************************
 * Function to Initialise all Timmer and External Interrupt related settings.
 * *************************************************************************/
void Init_GPT_ICU(void)
{
  /* Initializes all timer related settings.*/

 /* Initializes all External interrupts.*/

}

/* ************************************************************************
 * Function to perform SW reset when ever any critical fault detected.
 * *************************************************************************/
void Perform_Reset(void)
{
  Debug_Trace("Dissable and Resetting the Water Purifier Due to Above mentioned error....");

  /* Dissable all Output.*/

  /* Perform Reset.*/
  ESP.restart();
}
