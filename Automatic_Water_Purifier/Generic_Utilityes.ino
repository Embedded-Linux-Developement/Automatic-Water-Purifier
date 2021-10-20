/*******************************************************************************
 *  External Includes
 *******************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "MyStdTypes.h"
#include "Generic_Utilityes.h"

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
E-mail:- Jerryonwork@gmail.com
Date  :- 15 Sep 2021
version:- V2.0.1

*******************************************************************************************************/

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
  for (LoopIndex = 0; LoopIndex < (String_Length - 1); LoopIndex++)
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
  OutPutStringBuffer[String_Length - 1] = '\0';
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
  LowerCutoff = ((LowerCutoff <= TargetedValue) ? LowerCutoff : 0x00000000U);

  // Debug_Trace("TargetedValue = %d:- LowerCutoff = %d, InputValue = %d, UpperCutoff = %d .", TargetedValue, LowerCutoff, InputValue, UpperCutoff);

  /* Check wheather is within the Tolerance limit..*/
  if ((InputValue <= UpperCutoff) && (InputValue >= LowerCutoff))
  {
    /* Set return as OK*/
    Return_Value = E_OK;
  }
  else /* Out side tolerance Limit*/
  {
    /* Set return as NOT OK*/
    Return_Value = E_NOT_OK;
  }

  return (Return_Value);
}




/*
===========================================================================
===========================================================================
          Functions ADC window filtering
===========================================================================
==========================================================================
*/


/* Macro representing Maximum configured ADC for Filtering, If its not configured for filtering same shall be read directely using the interface, Raw value.*/
#define Max_Filter_Configured_ADC 4

/*Macro defining the periodicity of the background processing task.*/
#define ADC_Filtering_Task_Periodicity_ms 30

/*Macro representing Maximum Possible ADC value can read, based on the ADC channel resolution.*/
#define Max_ADC_channelResolution 4096

/* Data type required for doing filtering of input ADC values*/

/* Structure to Configuration paramaters ADC filtering channels.*/
typedef struct ADC_filter_Config_Table_Tag
{
  int ADC_ChannelGPIO_ID;        /* Provide the GPIO ID for for the required ADC channel, used this ID to read using "analogRead" */
  uint16 FilterWindowTime_ms;    /* This variable define the Window time for the respective ADC channel.
                                           Filtered output shall be average ADC value in the configured "FilterWindowTime_ms" 
                                    Criteria for selecting the Window:-
                                        1. ((FilterWindowTime_ms / ADC_Filtering_Task_Periodicity_ms) * 4096) shall able to accomidate into variable of type "double" based on the platform selected.  */

  uint32 Max_Dead_Time_ms;        /* MAcro representing Maximum dead time after last ADC processing, 
                                    If last Processed time is grater than the dead time, 
                                    Recommenced to select the half of the Window time.
                                    The shall consider reading directely using ADC interface.*/
} ADC_filter_Config_Table_Type;


/* Configuration table for all applicable ADC channel. If any channel requested outside this group then shall do a direct reading.*/
ADC_filter_Config_Table_Type ADC_filter_Config_Table[Max_Filter_Configured_ADC]{
/*ADC_ChannelGPIO_ID,   FilterWindowTime_ms,   Max_Dead_Time_ms */
{    35             ,         600           ,      300            },   /* ADC channel for LDR 1 @ GPIO 35*/
{    34             ,         600           ,      300            },   /* ADC channel for LDR 2 @ GPIO 34*/
{    33             ,         300           ,      150            },   /* ADC channel for OverFlow Detection @ GPIO 33*/
{    32             ,         300           ,      150            }    /* ADC channel for High Presere Detection @ GPIO 32*/
};



/* Structure to Configuration paramaters ADC filtering channels.*/
typedef struct ADC_filter_RunTime_Table_Tag
{
  double ADC_PreFiltered_Value;        /* Shall populate at runtime with current filtered value*/
  uint32 LastProcessedTime;            /* Represent the last processed time.*/

} ADC_filter_RunTime_Table_Type;


/* Create table for Runtime Data storage.*/
ADC_filter_RunTime_Table_Type ADC_filter_RunTime_Table[Max_Filter_Configured_ADC];

/* Mutex to protect the data in Runtime Table*/
portMUX_TYPE ADC_filter_RunTime_Table_Mux = portMUX_INITIALIZER_UNLOCKED;

/*Macro representing Invalid ADC value, Please select Never achievable value..*/
#define Invalid_ADC_Value 0xFFFFU

/* ************************************************************************
 * This Privite Function to read the processed ADC value based Filter designed.
 * *************************************************************************/
uint16 Sys_Read_Processed_ADC_Value(int GPIO_Port_pin)
{
  uint16 ADC_Return_Value = Invalid_ADC_Value;
  uint16 LoopIndex;
  double Current_Accumulated_Average;
  uint16 Calculated_Window_Tick;
  uint32 Current_Channel_Time;

  /* Loop for Each channel to get the matching Index.*/
  for (LoopIndex = 0; ((LoopIndex < Max_Filter_Configured_ADC) && (ADC_Return_Value == Invalid_ADC_Value)); LoopIndex++)
  {
    /* Check if matching with requested ID.*/
    if (ADC_filter_Config_Table[LoopIndex].ADC_ChannelGPIO_ID == GPIO_Port_pin)
    {

      /* Enter in to Critical Section*/
      portENTER_CRITICAL(&ADC_filter_RunTime_Table_Mux);

      Current_Accumulated_Average = ADC_filter_RunTime_Table[LoopIndex].ADC_PreFiltered_Value;
      Current_Channel_Time = ADC_filter_RunTime_Table[LoopIndex].LastProcessedTime;

      /* Exit from Critical Section. */
      portEXIT_CRITICAL(&ADC_filter_RunTime_Table_Mux);

      /* Check if Last processing time passed Dead time.*/
      if (Get_Time_Elapse(Current_Channel_Time) <= ADC_filter_Config_Table[LoopIndex].Max_Dead_Time_ms)
      {
        /* Calculate Tick for this ADC channel*/
        Calculated_Window_Tick = (uint16)(ADC_filter_Config_Table[LoopIndex].FilterWindowTime_ms / ADC_Filtering_Task_Periodicity_ms);

        /* Calculate final filtered value.*/
        ADC_Return_Value = (uint16)(Current_Accumulated_Average / Calculated_Window_Tick);
      }
      else /* Last processed time is elapsed grater than Dead time*/
      {
        Debug_Trace(" ADC filtering for Channel mapped to GPIO ID %d, missed for more than configured dead time (%dms).", GPIO_Port_pin, ADC_filter_Config_Table[LoopIndex].Max_Dead_Time_ms);
        /* Exit the loop*/
        LoopIndex = Max_Filter_Configured_ADC + 1;
        /* Do Direct Reading*/
        ADC_Return_Value = analogRead(GPIO_Port_pin);
      }

    } /* End of If matching the GPIO ID*/
  }   /* End of for loop*/

  /* If requested ADC channel is not configured for filtering.*/
  if (ADC_Return_Value == Invalid_ADC_Value)
  {
    Debug_Trace(" ADC filtering Not configured for Channel mapped to GPIO ID %d, Do doing direct read...", GPIO_Port_pin);
    /* At present ADC filtering logic are not implemented so reading directely from the ADC.*/
    ADC_Return_Value = analogRead(GPIO_Port_pin);
  }

  return (ADC_Return_Value);
}

/* ************************************************************************
 * This Privite Function to read the processed ADC value for Non critical features only...
 * *************************************************************************/
uint16 NON_CriticalSys_Read_Processed_ADC_Value(int GPIO_Port_pin)
{
  uint16 ADC_Return_Value = Invalid_ADC_Value;
  uint16 LoopIndex;
  double Current_Accumulated_Average;
  uint16 Calculated_Window_Tick;
  uint32 Current_Channel_Time;

  /* Loop for Each channel to get the matching Index.*/
  for (LoopIndex = 0; ((LoopIndex < Max_Filter_Configured_ADC) && (ADC_Return_Value == Invalid_ADC_Value)); LoopIndex++)
  {
    /* Check if matching with requested ID.*/
    if (ADC_filter_Config_Table[LoopIndex].ADC_ChannelGPIO_ID == GPIO_Port_pin)
    {


      Current_Accumulated_Average = ADC_filter_RunTime_Table[LoopIndex].ADC_PreFiltered_Value;
      Current_Channel_Time = ADC_filter_RunTime_Table[LoopIndex].LastProcessedTime;

      /* Check if Last processing time passed Dead time.*/
      if (Get_Time_Elapse(Current_Channel_Time) <= ADC_filter_Config_Table[LoopIndex].Max_Dead_Time_ms)
      {
        /* Calculate Tick for this ADC channel*/
        Calculated_Window_Tick = (uint16)(ADC_filter_Config_Table[LoopIndex].FilterWindowTime_ms / ADC_Filtering_Task_Periodicity_ms);

        /* Calculate final filtered value.*/
        ADC_Return_Value = (uint16)(Current_Accumulated_Average / Calculated_Window_Tick);
      }
      else /* Last processed time is elapsed grater than Dead time*/
      {
        Debug_Trace(" ADC filtering for Channel mapped to GPIO ID %d, missed for more than configured dead time (%dms).", GPIO_Port_pin, ADC_filter_Config_Table[LoopIndex].Max_Dead_Time_ms);
        /* Exit the loop*/
        LoopIndex = Max_Filter_Configured_ADC + 1;
        /* Do Direct Reading*/
        ADC_Return_Value = analogRead(GPIO_Port_pin);
      }

    } /* End of If matching the GPIO ID*/
  }   /* End of for loop*/

  /* If requested ADC channel is not configured for filtering.*/
  if (ADC_Return_Value == Invalid_ADC_Value)
  {
    Debug_Trace(" ADC filtering Not configured for Channel mapped to GPIO ID %d, Do doing direct read...", GPIO_Port_pin);
    /* At present ADC filtering logic are not implemented so reading directely from the ADC.*/
    ADC_Return_Value = analogRead(GPIO_Port_pin);
  }

  return (ADC_Return_Value);
}



/* ************************************************************************
 * Function to Init the ADC processing dates.
 * *************************************************************************/
void Init_ADC_BackEndFilter(void)
{
  uint16 LoopIndex;
  /* to get the tic value*/
  uint16 CalculatedTick;

  /*To store simulated max possible value based on the configuration of window.*/
  double Max_Possible_Value;

  /* Loop for Each channel to read and store the Init Value.*/
  for (LoopIndex = 0; LoopIndex < Max_Filter_Configured_ADC; LoopIndex++)
  {
    ADC_filter_RunTime_Table[LoopIndex].ADC_PreFiltered_Value = 0;
    ADC_filter_RunTime_Table[LoopIndex].LastProcessedTime = 0;

    /* Check Wheather the Configuration is based on the criteria.*/

    /* Check lose of window based on the task Timming.*/
    CalculatedTick = (uint16)(ADC_filter_Config_Table[LoopIndex].FilterWindowTime_ms / ADC_Filtering_Task_Periodicity_ms);
    if ((CalculatedTick * ADC_Filtering_Task_Periodicity_ms) != ADC_filter_Config_Table[LoopIndex].FilterWindowTime_ms)
    {
      Debug_Trace("Filter Window timming for ADC @ GPIO ID %d is changed to %dms, But Configured is %dms.", ADC_filter_Config_Table[LoopIndex].ADC_ChannelGPIO_ID, ADC_filter_Config_Table[LoopIndex].FilterWindowTime_ms);
    }

    /* Check id window configured is grater than period tic, else, Do not consider.*/
    if (ADC_filter_Config_Table[LoopIndex].FilterWindowTime_ms < ADC_Filtering_Task_Periodicity_ms)
    {

#if 0 /* Use below Print id delay is not used*/
      /* Based on configuration ist not possible to accomidate into cirrent design, So performing reset.*/
      /* Not using Debug trace, because reset is going to trigger.*/
      Serial.write("ADC Filter:-Configuration error for GPIO ID :- ");
      Serial.print(ADC_filter_Config_Table[LoopIndex].ADC_ChannelGPIO_ID, DEC);
      Serial.write(" , Window time value configured is less than periodicity of the filtering task.");
      Serial.write(" Configured Window = ");
      Serial.print(ADC_filter_Config_Table[LoopIndex].FilterWindowTime_ms, DEC);
      Serial.write("\n");
#else
      Debug_Trace("ADC Filter:-Configuration error for GPIO ID :- %d  , Window time value configured is less than periodicity of the filtering task.", ADC_filter_Config_Table[LoopIndex].ADC_ChannelGPIO_ID);
      Debug_Trace("Configured Window = %d",ADC_filter_Config_Table[LoopIndex].FilterWindowTime_ms);
      /* Add delay 15 Sec to slow down reset.*/
      Delay_In_ms(15000);
#endif
      Perform_Reset();
    }

    /* Check if Max possible value*/
    Max_Possible_Value = (CalculatedTick * Max_ADC_channelResolution);
    /* Check if Over flow detected, avoid the change is floating precition, so consider tolerance of +/- 1 with expected value*/
    if (((double)(Max_Possible_Value / Max_ADC_channelResolution) <= (double)(CalculatedTick + 1)) &&
        ((double)(Max_Possible_Value / Max_ADC_channelResolution) >= (double)(CalculatedTick - 1)))
    {
      /* Do nothing, Configuration is correct.. */
    }
    else /* if Configuratation is not correct.*/
    {

#if 0 /* Use below Print id delay is not used*/
      /* Based on the configuration cannot Accumilate, So triggering reset. */
      /* Not using Debug trace, because reset is going to trigger.*/
      Serial.write("ADC Filter:-Configuration error for GPIO ID :- ");
      Serial.print(ADC_filter_Config_Table[LoopIndex].ADC_ChannelGPIO_ID, DEC);
      Serial.write(" , Based on Window time Max possible accumulated avarage value is grater than the used variable sizes.\n");
      Serial.write(" Please consider Criteria, ((FilterWindowTime_ms / ADC_Filtering_Task_Periodicity_ms) * 4096) shall able to accomidate into variable of type \"double\" based on the platform selected. ");
      Serial.write("\n");
#else
      Debug_Trace("ADC Filter:-Configuration error for GPIO ID :- %d , Based on Window time Max possible accumulated avarage value is grater than the used variable sizes.", ADC_filter_Config_Table[LoopIndex].ADC_ChannelGPIO_ID);
      Debug_Trace(" Please consider Criteria, ((FilterWindowTime_ms / ADC_Filtering_Task_Periodicity_ms) * 4096) shall able to accomidate into variable of type \"double\" based on the platform selected. ");
     
      Debug_Trace("Max_Possible_Value = %f, CalculatedTick = %d, Max_ADC_channelResolution = %d", Max_Possible_Value, CalculatedTick,Max_ADC_channelResolution);
      Debug_Trace("(double)(Max_Possible_Value / Max_ADC_channelResolution) = %f", (double)(Max_Possible_Value / Max_ADC_channelResolution));
      /* Add delay 15 Sec to slow down reset.*/
      Delay_In_ms(15000);
#endif

      Perform_Reset();
    }
  }

}

/* ************************************************************************
 * Function to process the ADC value in background and do filtering.
 * *************************************************************************/
void Process_ADC_BackEndFilter(void)
{
  uint16 LoopIndex;
  uint16 Current_ADC_Value;
  double Previous_Accumulated_Average;
  uint16 Calculated_Window_Tic;
  uint32 Current_Time;

  /* Loop for Each channel to read and store the Average Value.*/
  for (LoopIndex = 0; LoopIndex < Max_Filter_Configured_ADC; LoopIndex++)
  {
    /* Read the ADC value based on the configuration*/
    Current_ADC_Value = analogRead(ADC_filter_Config_Table[LoopIndex].ADC_ChannelGPIO_ID);

    /* Reading previous value, from table without critical section protection,
      because, Its writting in the same this loop, So No issue it seems. */
    Previous_Accumulated_Average = ADC_filter_RunTime_Table[LoopIndex].ADC_PreFiltered_Value;

    /* Calculate the window Tick*/
    Calculated_Window_Tic = (uint16)(ADC_filter_Config_Table[LoopIndex].FilterWindowTime_ms / ADC_Filtering_Task_Periodicity_ms);

    /* Recalculate New Value*/

    /* Removed the (1 / Calculated_Window_Tic) watage from current accumulated value.*/
    Previous_Accumulated_Average = (double)(Previous_Accumulated_Average - (double)(Previous_Accumulated_Average / Calculated_Window_Tic));
    /* Add Newell received ADC value Value*/
    Previous_Accumulated_Average = (double)(Previous_Accumulated_Average + (double)(Current_ADC_Value));

    /* While reading get actual value after divide using Calculated_Window_Tic, in Sys_Read_Processed_ADC_Value() API,
      Because it save unwanted divide operatation at every cycle.*/

    /* Get current Time for updating Alive counter*/
    Current_Time = millis();

    /* Enter in to Critical Section*/
    portENTER_CRITICAL(&ADC_filter_RunTime_Table_Mux);

    ADC_filter_RunTime_Table[LoopIndex].ADC_PreFiltered_Value = Previous_Accumulated_Average;
    ADC_filter_RunTime_Table[LoopIndex].LastProcessedTime = Current_Time;

    /* Exit from Critical Section. */
    portEXIT_CRITICAL(&ADC_filter_RunTime_Table_Mux);

  } /* End of for loop.*/
}
