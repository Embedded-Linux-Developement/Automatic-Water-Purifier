/*******************************************************************************
 *  External Includes
*******************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "MyStdTypes.h"
#include "Generic_Utilityes.h"


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
                      Public Generic functions
===========================================================================
===========================================================================
*/

/* ************************************************************************
 * Function to get time difference with respect to current time, 
 *    Shall consider over flow case also.
 * ************************************************************************
 * */
unsigned long Get_Time_Elapse(unsigned long Reference_Time)
{
  /* Variable to store the difference in time.*/
  unsigned long Delta_Time = 0;
  unsigned long Current_Time = 0;

  /* For tracing the the function call.*/
  Trace_Function_Call();

  /*Get current time*/
  Current_Time = millis();

  /* Check if overflow is happened. In case of overflow current value shall be smaller than the Reference time*/
  if (Current_Time < Reference_Time)
  {
    Delta_Time = Current_Time + (0xFFFFFFFF - Reference_Time);
  }
  else /* No over flow detected*/
  {
    Delta_Time = Current_Time - Reference_Time;
  }

  /* Return the difference*/
  return (Delta_Time);
}


/* ************************************************************************
 * Function to get Random string.
 * ************************************************************************
 * */
void Get_Randam_String(uint16 String_Length, uint8 *OutPutStringBuffer)
{
  uint16 LoopIndex;
  uint8 randomValue;

  /* For tracing the the function call.*/
  Trace_Function_Call();

  /* Loop for each element.*/
  for (LoopIndex = 0; LoopIndex < (String_Length -1); LoopIndex++)
  {
    /* get a random number.*/
    randomValue = random(0, 37);

    /* store random numeric*/
    if (randomValue > 26)
    {
      OutPutStringBuffer[LoopIndex] = (uint8)(randomValue - 26U) + '0';
    }
    else /* store random alphabet*/
    {

      OutPutStringBuffer[LoopIndex] = (uint8)(randomValue + 'a');
    }
  }
  /* Add null pointer at the end*/
  OutPutStringBuffer[String_Length -1] = '\0';
}


/* ************************************************************************
 * Function to Check wheather the input value is within the tolerance of.
 *    targeted value.
 *   Shall Return :- E_OK      => Within the targeted range 
 *                   E_NOT_OK  => Outside the targered limit.
 * ************************************************************************
 */
uint8 ADC_Check_Tolerance(uint32 InputValue, uint32 TargetedValue, uint8 ToleranceAllowed)
{

  uint8 Return_Value = E_NOT_OK;
  uint32 UpperCutoff;
  uint32 LowerCutoff;

  /* Get upper cutoff Value*/
  UpperCutoff = TargetedValue + (uint32)((uint32)(System_ADC_Max_Value * ToleranceAllowed) / 100U);
  /* RE-correct Uppercut off, if Overflow detected.*/
  UpperCutoff = ((UpperCutoff >= TargetedValue) ? UpperCutoff : 0xFFFFFFFFU);

  /* Get Lower cutoff Value*/
  LowerCutoff = TargetedValue - (uint32)((uint32)(System_ADC_Max_Value * ToleranceAllowed) / 100U);
  /* RE-correct Lower off, if Under flow detected.*/
   LowerCutoff = ((LowerCutoff <= TargetedValue )? LowerCutoff : 0x00000000U) ;

  /* Check wheather is within the Tolerance limit..*/
  if( (InputValue <= UpperCutoff) && (InputValue >= LowerCutoff) )
  {
    /* Set return as OK*/
    Return_Value = E_OK;
  }
  else /* Out side tolerance Limit*/
  {
    /* Set return as NOT OK*/
    Return_Value = E_NOT_OK;
  }

  return(Return_Value);
}




