/*******************************************************************************
 *  External Includes
 *******************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "MyStdTypes.h"
#include "ESP32_NVM_Stack.h"
#include "Generic_Utilityes.h"
#include "System_Utilityes.h"




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
 *  System Utility related Configuration Start
 *******************************************************************************/

/* If configuration is On NVM*/
#if (System_Config_From_NVM_Support == STD_ON)

/* Define as blank, because Normal global variable needed to store NVM paramater*/
#define Config_Var

#else /* If configuration is not ON NVM*/

/* Convert global variables into const for storing its value.*/
#define Config_Var const

#endif /* End of #if (System_Config_From_NVM_Support == STD_ON)*/

/*******************************************************************************
 *  Following are the Global variables for each Used Port Pins
 *  Global variables are used because later same can be updated via Configuration.
 *******************************************************************************/

/*===========================================================================================*/
/*      Paramaters for UV Lamp Related                                                       */
/*===========================================================================================*/
/*Port Paramaters for UV Lamp control Repay. */
Config_Var uint8 P01_UV_Lamp_Relay = 16;             /*  GPIO 16 @Port Pin 21 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
Config_Var uint8 P02_UV_Lamp_Relay_ON_State = LOW;   /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
Config_Var uint8 P03_UV_Lamp_Relay_OFF_State = HIGH; /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/* Paramater to configure UV lamp Support*/
uint8 P2E_UV_Feedback_Support = UV_Feedback_Both; /*  Indicate the configuration for the UV lamp feedback.. */

/* Paramater for LDR 1 , to detect UV light operatation*/
Config_Var uint8 P04_UV_Lamp_Analog_LDR_1 = 35;            /*  Mapped to ADC 1_7, GPIO 35 @Port Pin 11 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
Config_Var uint16 P05_UV_Lamp_Analog_LDR_1_ON_Volt = 2500; /*  Represent the Voltage level representing the Active State / When UV is ON for LDR 1.*/
Config_Var uint16 P07_UV_Lamp_Analog_LDR_1_OFF_Volt = 125; /*  Represent the Voltage level representing the Active State / When UV is OFF for LDR 1.*/
Config_Var uint8 P09_UV_Lamp_Analog_LDR_1_Tolerance = 15;  /*  Persentage (%) of Max valye 4095, to make Tolerance a linear scale acceptable tolerance which can be considered.*/

/* Paramater for LDR 2 , to detect UV light operatation*/
Config_Var uint8 P0A_UV_Lamp_Analog_LDR_2 = 34;            /*  Mapped to ADC 1_6, GPIO 34 @Port Pin 12 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
Config_Var uint16 P0B_UV_Lamp_Analog_LDR_2_ON_Volt = 2500; /*  Represent the Voltage level representing the Active State / When UV is ON for LDR 2.*/
Config_Var uint16 P0D_UV_Lamp_Analog_LDR_2_OFF_Volt = 125; /*  Represent the Voltage level representing the Active State / When UV is OFF for LDR 2.*/
Config_Var uint8 P0F_UV_Lamp_Analog_LDR_2_Tolerance = 15;  /*  Persentage (%) of Max valye 4095, to make Tolerance a linear scale acceptable tolerance which can be considered.*/

/* Paramater to Set UV lamp turn ON Delay.*/
Config_Var uint16 P2F_UV_On_Delay_Time_In_ms = 5000; /*  Indicate the configuration for the UV lamp turned ON time.. */

/*===========================================================================================*/
/*      Paramaters Related to Input flow                                                     */
/*===========================================================================================*/

/*Port Paramaters related in InLine Input Solinode Relay control */
Config_Var uint8 P10_InLineInputSolenoid_Relay = 17;             /*  GPIO 16 @Port Pin 22 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
Config_Var uint8 P11_InLineInputSolenoid_Relay_ON_State = LOW;   /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
Config_Var uint8 P12_InLineInputSolenoid_Relay_OFF_State = HIGH; /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/* Paramater represent time to Solenoid to take action / water start flow.*/
Config_Var uint16 P31_InLineInput_Delay_Time_In_ms = 1000; /*  Indicate the configuration for the time to Solenoid action get effective.. */

/*===========================================================================================*/
/*      Paramaters Related to Booster Pump                                                   */
/*===========================================================================================*/
/* Paramater to Specify Wheather Booster motor required to support.*/
Config_Var uint8 P13_InputBoostMotor_Support = STD_ON; /*  STD_ON ==> Support Booster motor, STD_OFF ==> Shall not Support Booster motor. */

/*Port Paramaters related to Input Booster Motor Relay control */
Config_Var uint8 P14_InputBoostMotor_Relay = 18;             /*  GPIO 18 @Port Pin 24 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
Config_Var uint8 P15_InputBoostMotor_Relay_ON_State = LOW;   /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
Config_Var uint8 P16_InputBoostMotor_Relay_OFF_State = HIGH; /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/*Port Paramaters related in input Solinode to control flow of Booster Motor */
Config_Var uint8 P17_InputBoostSolenoid_Relay = 19;             /*  GPIO 19 @Port Pin 25 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
Config_Var uint8 P18_InputBoostSolenoid_Relay_ON_State = LOW;   /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
Config_Var uint8 P19_InputBoostSolenoid_Relay_OFF_State = HIGH; /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/* Paramater represent time to Booster Motor & Solinode to take action / water start flow.*/
Config_Var uint16 P33_InputBoost_Delay_Time_In_ms = 1000; /*  Indicate the configuration for the time to Booster Motor & Solinode action get effective.. */

/*===========================================================================================*/
/*      Paramaters Related to RO motor Pump                                                  */
/*===========================================================================================*/

/* Paramater to Specify Wheather RO Pump required to support.*/
Config_Var uint8 P1A_RO_Motor_Support = STD_ON; /*  STD_ON ==> Support RO pump, STD_OFF ==> Shall not Support RO Pump. */

/*Port Paramaters related to RO Motor Relay control */
Config_Var uint8 P1B_RO_Motor_Relay = 5;              /*  GPIO 5 @Port Pin 23 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
Config_Var uint8 P1C_RO_Motor_Relay_ON_State = LOW;   /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
Config_Var uint8 P1D_RO_Motor_Relay_OFF_State = HIGH; /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/*Port Paramaters related to the Solinode to control flow of RO Motor */
Config_Var uint8 P1E_RO_Solenoid_Relay = 5;              /*  GPIO 5 @Port Pin 23 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
Config_Var uint8 P1F_RO_Solenoid_Relay_ON_State = LOW;   /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
Config_Var uint8 P20_RO_Solenoid_Relay_OFF_State = HIGH; /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/* Paramater represent time to RO Motor & Solinode to take action / water start flow.*/
Config_Var uint16 P35_RO_Delay_Time_In_ms = 1000; /*  Indicate the configuration for the time to RO Motor & Solinode action get effective.. */

/*===========================================================================================*/
/*      Other Analog Input Port  paramaters                                                  */
/*===========================================================================================*/

/* Paramater for High Presere Detection, to Avoid malfunctioning*/
Config_Var uint8 P21_Analog_HighPresere = 32;             /*  Mapped to ADC 1_4, GPIO 32 @Port Pin 10 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
Config_Var uint16 P22_Analog_HighPresere_ON_Volt = 3800;  /*  Represent the Voltage level representing the High presure is Not Full. OFF for Over flow sensor.*/
Config_Var uint16 P24_Analog_HighPresere_OFF_Volt = 1834; /*  Represent the Voltage level representing the High presure is Not Full. OFF for Over flow sensor.*/
Config_Var uint8 P26_Analog_HighPresere_Tolerance = 20;   /*  Persentage (%) of Max valye 4095, to make Tolerance a linear scale acceptable tolerance which can be considered.*/

/* Paramater represent High Pressure colling Time .
  ==> Once High pressure is detected SHall waite for colling time to leaps..*/
Config_Var uint16 P37_HighPresere_CollingTime_In_ms = 5000; /*  Indicate the High Pressure colling Time... */

/* Paramater for OverFlow Detection and to stop the filtering. */
Config_Var uint8 P27_Analog_OverFlow = 33;             /*  Mapped to ADC 1_5, GPIO 33 @Port Pin 9 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
Config_Var uint16 P28_Analog_OverFlow_ON_Volt = 3800;  /*  Represent the Voltage level representing the Tank is Full. ON for Over flow sensor.*/
Config_Var uint16 P2A_Analog_OverFlow_OFF_Volt = 1843; /*  Represent the Voltage level representing the Tank is Not Full. OFF for Over flow sensor.*/
Config_Var uint8 P2C_Analog_OverFlow_Tolerance = 20;   /*  Persentage (%) of Max valye 4095, to make Tolerance a linear scale acceptable tolerance which can be considered.*/

/* Paramater represent OverFlow colling Time .
  ==> Once OverFlow is detected SHall waite for colling time to leaps..*/
Config_Var uint16 P39_OverFlow_CollingTime_In_ms = 5000; /*  Indicate the OverFlow colling Time... */

/*===========================================================================================*/
/*      Water flow meter Input Port  paramaters                                              */
/*===========================================================================================*/
Config_Var uint8 P2D_WaterFlowSensor_Input = 4; /* GPIO 4 @Port Pin 20 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */

/*-----------------------------------------------------------------------------
 *  System Utility related Configuration END
-------------------------------------------------------------------------------*/

/*******************************************************************************
 *  Variables and Constense
 *******************************************************************************/

/* Variable to store the current UV lamp state set by SW.*/
static Sys_UV_Lamp_Status UV_Lamp_Current_Status = UV_Lamp_OFF;
/* Variable to store the Time at which UV light Started / Stopped.*/
static uint32 UV_Lamp_Start_Time = Int_Zero;
/* Mutex to protect the Global variable for UV-Lamp*/
portMUX_TYPE UV_Lamp_Mux = portMUX_INITIALIZER_UNLOCKED;

/* Variable to store the current IN-Line request set by SW.*/
static Sys_Operatation_Status InLineInput_Current_Status = Operatation_OFF;
/* Variable to store the Time at which In-Line Input Started / stoped.*/
static uint32 InLineInput_Start_Time = Int_Zero;
/* Mutex to protect the Global variable for InLineInput*/
portMUX_TYPE InLineInput_Mux = portMUX_INITIALIZER_UNLOCKED;

/* Variable to store the current Input Boost request set by SW.*/
static Sys_Operatation_Status InputBoost_Current_Status = Operatation_OFF;
/* Variable to store the Time at which InputBoost Input Started / stoped.*/
static uint32 InputBoost_Start_Time = Int_Zero;
/* Mutex to protect the Global variable for InputBoost*/
portMUX_TYPE InputBoost_Mux = portMUX_INITIALIZER_UNLOCKED;

/* Variable to store the current Input RO request set by SW.*/
static Sys_Operatation_Status InputRO_Current_Status = Operatation_OFF;
/* Variable to store the Time at which Input RO Input Started / stoped.*/
static uint32 InputRO_Start_Time = Int_Zero;
/* Mutex to protect the Global variable for InputRO*/
portMUX_TYPE InputRO_Mux = portMUX_INITIALIZER_UNLOCKED;

/* Variable to store the current High presure sensor input.*/
static Sensor_InputStatus_Status Sensor_HighPressure_Status = Sensor_OFF;
/* Variable to store the Time at which High presure sensor input Started / stoped.*/
static uint32 Sensor_HighPressure_Start_Time = Int_Zero;
/* Mutex to protect the Global variable for Sensor HighPressure*/
portMUX_TYPE Sensor_HighPressure_Mux = portMUX_INITIALIZER_UNLOCKED;

/* Variable to store the current OverFlow sensor input.*/
static Sensor_InputStatus_Status Sensor_OverFlow_Status = Sensor_OFF;
/* Variable to store the Time at which OverFlow sensor input Started / stoped.*/
static uint32 Sensor_OverFlow_Start_Time = Int_Zero;
/* Mutex to protect the Global variable for Sensor OverFlow*/
portMUX_TYPE Sensor_OverFlow_Mux = portMUX_INITIALIZER_UNLOCKED;

/* Variable to store the init status of the Operatation.*/
System_Operatation_Status Current_Operatation_Status = Init_State;
System_Operatation_Status Previous_Operatation_Status = Init_State;

/*Macro function to get current state*/
#define Get_Current_Opp_State() Current_Operatation_Status

/* Macro function to update the state*/
#define Set_Current_Opp_State(Req_State)                      \
  {                                                           \
    Previous_Operatation_Status = Current_Operatation_Status; \
    Current_Operatation_Status = Req_State;                   \
  }

/* Macro to check wheather any state is changes.*/
#define Is_Opp_State_Changed() (Previous_Operatation_Status != Current_Operatation_Status)

/* Macro to Print the state Change.*/
#define Log_State_Changed(Change_Commend) \
  {                                       \
    if (Is_Opp_State_Changed())           \
    {                                     \
      Debug_Trace(Change_Commend);        \
    }                                     \
  }

/* Macro indicating processing of current state completed at-lest once*/
#define State_Change_completed() (Previous_Operatation_Status = Current_Operatation_Status)

/*---------------------------------------------------------------------------------
                       Variables related to Water flow
-----------------------------------------------------------------------------------*/

/* Maximum flow above below value is not possible, So considered for invalided*/
#define Invalue_Flow_Value_InL 65000

/* Variable to store the water flow detected when state changed to "Normal_Tank_Not_Full" */
double Water_Flow_At_Normal_Tank_Not_Full = 0;

static uint32 CounterOverflow;            /* Variable to store the over flow count */
pcnt_isr_handle_t user_isr_handle = NULL; /* User ISR handler for Interrupt */

/* Mutex to protect the Global variable for Waterflow*/
portMUX_TYPE Waterflow_Mux = portMUX_INITIALIZER_UNLOCKED;

/* Create a array of 60 location to store all water flowed between each second for calculating flow rate*/
double Water_FlowRate_PerSec[60];
/* Use to store the Next Index to be filed.*/
uint8 Water_FlowRate_Log_Current_Index = 0;
/* Use to store Instantinous Index, Once reached 60, shall hold there.*/
uint8 Water_FlowRate_Log_Instantaneous_Index = 0;
/* Store Previous Logged Value. Shall help to detect first case and avoid travising buffer*/
double Previous_Section_Value = Invalue_Flow_Value_InL;

/*Store final processed Instantaneous flow value.*/
double Final_Instantinous_Flow_In_LpM = Invalue_Flow_Value_InL;

/* Global Variable to store the High flow rate detected.*/
uint8 HighWater_Flow_Detected = false;

/* Global Variable to store the High flow rate detected.*/
uint8 LowWater_Flow_Detected = false;

/*******************************************************************************
 *  Functions Forward decleratations deceleration
 *******************************************************************************/

/*This function is to Control UV Lamp operatations*/

static void ShutDown_All(void);

static void Control_UV_Lamp(Sys_UV_Lamp_Status InputRequest);
static Sys_UV_Lamp_Feedback_Status Get_UV_Lamp_Feedback(void);
static char *GetStatus_UV_Lamp_Sensor_Raw_Value(void);

static void Control_InLineInput(Sys_Operatation_Status InputRequest);
static Sys_Operatation_Status GetStatus_InLineInput(void);

static void Control_BoostInput(Sys_Operatation_Status InputRequest);
static Sys_Operatation_Status GetStatus_BoostInput(void);

static void Control_ROInput(Sys_Operatation_Status InputRequest);
static Sys_Operatation_Status GetStatus_ROInput(void);

static Sensor_InputStatus_Status GetStatus_HighPresere(void);
static uint16 GetStatus_HighPresere_Sensor_Raw_Value(void);

static Sensor_InputStatus_Status GetStatus_OverFlow(void);
static uint16 GetStatus_OverFlow_Sensor_Raw_Value(void);

/*******************************************************************************
 *  Class Objects.
 *******************************************************************************/

/*
===========================================================================
===========================================================================
          Privite functions related to Control system System
===========================================================================
==========================================================================

/* ************************************************************************
 * Function to master ShutDown the filtering.
 * *************************************************************************/
void ShutDown_All(void)
{
  // Debug_Trace("Requested Complete ShutDown..");

  /* Switch off the Motor and solinode*/
  Control_ROInput(Operatation_OFF);

  /* Switch off the Motor and solinode*/
  Control_BoostInput(Operatation_OFF);

  /* Disconnect the Inlet Solenoids*/
  Control_InLineInput(Operatation_OFF);

  /* Switch off the UV light.*/
  Control_UV_Lamp(UV_Lamp_OFF);
}

/* ************************************************************************
 * This function is to Control UV Lamp operatations
 * *************************************************************************/
void Control_UV_Lamp(Sys_UV_Lamp_Status InputRequest)
{
  /* Variable to store current Time ( To avoid in mutex protection)*/
  uint32 Temp_Time;
  /* Variable to store Pin Status ( To avoid in mutex protection)*/
  uint32 Temp_PinStatus = 0xFFU;

  /* Get the current time value*/
  Temp_Time = millis();
  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&UV_Lamp_Mux);

  /* Power ON the Lamp is requested.*/
  if (InputRequest == UV_Lamp_ON)
  {
    /* Update Current time, if previous state is OFF*/
    if (UV_Lamp_Current_Status == UV_Lamp_OFF)
    {
      /* Reset the Start time*/
      UV_Lamp_Start_Time = Temp_Time;

      /*Print Debug Info.*/
      Debug_Trace("Requested UV lamp to turn ON...");
    }

    /* Switch ON the UV light.*/
    Temp_PinStatus = P02_UV_Lamp_Relay_ON_State;
    /* Up date the status.*/
    UV_Lamp_Current_Status = UV_Lamp_ON;
  }
  else if (InputRequest == UV_Lamp_OFF)
  {

    /* Update Current time, if previous state is ON*/
    if (UV_Lamp_Current_Status == UV_Lamp_ON)
    {
      /* Reset the Start time*/
      UV_Lamp_Start_Time = Temp_Time;

      /*Print Debug Info.*/
      Debug_Trace("Requested UV lamp to turn OFF...");
    }

    /* Switch off the UV light.*/
    Temp_PinStatus = P03_UV_Lamp_Relay_OFF_State;
    /* Up date the status.*/
    UV_Lamp_Current_Status = UV_Lamp_OFF;
  }
  else
  {
    /* Do nothing because, request is not valied.*/
  }

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&UV_Lamp_Mux);

  /* If port Pin Required to update*/
  if (Temp_PinStatus != 0xFFU)
  {
    /* Switch ON / OFF Port Pin based on the result.*/
    digitalWrite(P01_UV_Lamp_Relay, Temp_PinStatus);
  }
}

/* ************************************************************************
 * This function is to Get Feedback status of UV Lamp operatations.
 * *************************************************************************/
Sys_UV_Lamp_Feedback_Status Get_UV_Lamp_Feedback(void)
{
  /* Return variable..*/
  Sys_UV_Lamp_Feedback_Status ReturnStatus = UV_Lamp_Feedback_Fault;
  Sys_UV_Lamp_Feedback_Status LDR_1_Status = UV_Lamp_Feedback_Fault;
  Sys_UV_Lamp_Feedback_Status LDR_2_Status = UV_Lamp_Feedback_Fault;
  uint16 UV_LDR_1_ADC_Value;
  uint16 UV_LDR_2_ADC_Value;

  /* Read ADC value of both LDR. Filtering of ADC is not considered for now... */
  UV_LDR_1_ADC_Value = Sys_Read_Processed_ADC_Value(P04_UV_Lamp_Analog_LDR_1);
  UV_LDR_2_ADC_Value = Sys_Read_Processed_ADC_Value(P0A_UV_Lamp_Analog_LDR_2);

  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&UV_Lamp_Mux);

  /* Check if configuration of feedback is enabled*/
  if (UV_Feedback_None != P2E_UV_Feedback_Support)
  {

    /* Check if enough time elapsed after UV Lamp is turned ON*/
    if (Get_Time_Elapse(UV_Lamp_Start_Time) >= P2F_UV_On_Delay_Time_In_ms)
    {

      /* Check if LDR 1 detected as UV light ON*/
      if (ADC_Check_Tolerance((uint32)UV_LDR_1_ADC_Value, (uint32)P05_UV_Lamp_Analog_LDR_1_ON_Volt, P09_UV_Lamp_Analog_LDR_1_Tolerance) == E_OK)
      {
        /* Check if Current UV lamp state is also ON, Else decleared as fault*/
        LDR_1_Status = (UV_Lamp_Current_Status == UV_Lamp_ON) ? UV_Lamp_Feedback_ON : UV_Lamp_Feedback_Fault;
      }
      /* Check wheather status is OFF.*/
      else if (ADC_Check_Tolerance((uint32)UV_LDR_1_ADC_Value, (uint32)P07_UV_Lamp_Analog_LDR_1_OFF_Volt, P09_UV_Lamp_Analog_LDR_1_Tolerance) == E_OK)
      {
        /* Check if Current UV lamp state is also OFF, Else decleared as fault*/
        LDR_1_Status = (UV_Lamp_Current_Status == UV_Lamp_OFF) ? UV_Lamp_Feedback_OFF : UV_Lamp_Feedback_Fault;
      }
      else /* Unknown State detected, So setting as fault.*/
      {
        LDR_1_Status = UV_Lamp_Feedback_Fault;
      }

      /* Check if LDR 2 detected as UV light ON*/
      if (ADC_Check_Tolerance((uint32)UV_LDR_2_ADC_Value, (uint32)P0B_UV_Lamp_Analog_LDR_2_ON_Volt, P0F_UV_Lamp_Analog_LDR_2_Tolerance) == E_OK)
      {
        /* Check if Current UV lamp state is also ON, Else decleared as fault*/
        LDR_2_Status = (UV_Lamp_Current_Status == UV_Lamp_ON) ? UV_Lamp_Feedback_ON : UV_Lamp_Feedback_Fault;
      }
      /* Check wheather status is OFF.*/
      else if (ADC_Check_Tolerance((uint32)UV_LDR_2_ADC_Value, (uint32)P0D_UV_Lamp_Analog_LDR_2_OFF_Volt, P0F_UV_Lamp_Analog_LDR_2_Tolerance) == E_OK)
      {
        /* Check if Current UV lamp state is also OFF, Else decleared as fault*/
        LDR_2_Status = (UV_Lamp_Current_Status == UV_Lamp_OFF) ? UV_Lamp_Feedback_OFF : UV_Lamp_Feedback_Fault;
      }
      else /* Unknown State detected, So setting as fault.*/
      {
        LDR_2_Status = UV_Lamp_Feedback_Fault;
      }

      /* If feedback config is to check Both then, */
      if (P2E_UV_Feedback_Support == UV_Feedback_Any)
      {
        /* Check if any LDR report same status are not fault detected.*/
        if (((LDR_1_Status == UV_Lamp_Feedback_OFF) || (LDR_1_Status == UV_Lamp_Feedback_ON)) && (LDR_1_Status != UV_Lamp_Feedback_Fault))
        {
          /* Update correct status.*/
          ReturnStatus = LDR_1_Status;
        }
        /* Check Second LDR status.*/
        else if (((LDR_2_Status == UV_Lamp_Feedback_OFF) || (LDR_2_Status == UV_Lamp_Feedback_ON)) && (LDR_2_Status != UV_Lamp_Feedback_Fault))
        {
          /* Update correct status.*/
          ReturnStatus = LDR_2_Status;
        }
        else /* Report fault as both LDR get failed.*/
        {
          ReturnStatus = UV_Lamp_Feedback_Fault;
        }
      }
      else /* All other cases inclusing Both are enabled...*/
      {
        /* Check if Both LDR report same status are not fault detected.*/
        if ((LDR_2_Status == LDR_1_Status) && (LDR_1_Status != UV_Lamp_Feedback_Fault))
        {
          /* Update correct status.*/
          ReturnStatus = LDR_1_Status;
        }
        else /* Report fault.*/
        {
          ReturnStatus = UV_Lamp_Feedback_Fault;
        }
      }
    }
    else /* If time is Not Elapsed yet to read the feedback status.*/
    {
      /* Set status feedback is in progress..*/
      ReturnStatus = UV_Lamp_Feedback_InProgres;
    }
  }
  else /* If Feedback is Dissabled.*/
  {
    /* Check if current state is UN-Init*/
    if (UV_Lamp_UnInit != UV_Lamp_Current_Status)
    {
      /* Set the return value based on the current status.*/
      ReturnStatus = ((UV_Lamp_Current_Status == UV_Lamp_ON) ? UV_Lamp_Feedback_ON : UV_Lamp_Feedback_OFF);
    }
    else
    {
      /* DO Nothing...*/
    }
  }

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&UV_Lamp_Mux);

  /* Return final status*/
  return (ReturnStatus);
}

/* ************************************************************************
 * This function is get the High Presere Sensor Raw Value.
 * Value shall be process and converted in to string
 * This interface shall provide its global variable, But its Not Mutely exclusive.
 * *************************************************************************/
char *GetStatus_UV_Lamp_Sensor_Raw_Value(void)
{
  /* Static variable to Keep the return pointer alive..*/
  static char Return_Buffer[70];
  uint16 UV_LDR_1_ADC_Value;
  uint16 UV_LDR_2_ADC_Value;

  /* Read ADC value of both LDR. Filtering of ADC is not considered for now... */
  UV_LDR_1_ADC_Value = Sys_Read_Processed_ADC_Value(P04_UV_Lamp_Analog_LDR_1);
  UV_LDR_2_ADC_Value = Sys_Read_Processed_ADC_Value(P0A_UV_Lamp_Analog_LDR_2);

  sprintf(Return_Buffer, "UV Sensor 1 = %d, UV Sensor 2 = %d ", UV_LDR_1_ADC_Value, UV_LDR_2_ADC_Value);

  return ((char *)&Return_Buffer[0]);
}

/* ************************************************************************
 * This function is to Control InLine waterInput operatations
 * *************************************************************************/
void Control_InLineInput(Sys_Operatation_Status InputRequest)
{

  /* Variable to store current Time ( To avoid in mutex protection)*/
  uint32 Temp_Time;
  /* Variable to store Pin Status ( To avoid in mutex protection)*/
  uint32 Temp_PinStatus = 0xFFU;

  /* Get the current time value*/
  Temp_Time = millis();

  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&InLineInput_Mux);

  /* If input request is to ON*/
  if (InputRequest == Operatation_ON)
  {
    /* If previous status is OFF, then Update States changed Time*/
    if (Operatation_OFF == InLineInput_Current_Status)
    {
      /* Reset the Start time*/
      InLineInput_Start_Time = Temp_Time;

      /*Print Debug Info.*/
      Debug_Trace("Requested Inline solenoid valve to turn ON...");
    }
    else
    {
      /* Do Nothing...*/
    }

    /* Update the Output pin state*/
    Temp_PinStatus = P11_InLineInputSolenoid_Relay_ON_State;
    /* Update current status*/
    InLineInput_Current_Status = Operatation_ON;
  }
  /* If input request is to make it OFF*/
  else if (InputRequest == Operatation_OFF)
  {
    /* If previous status is OFF, then Update States changed Time*/
    if (Operatation_ON == InLineInput_Current_Status)
    {
      /* Reset the Stope time*/
      InLineInput_Start_Time = Temp_Time;

      /*Print Debug Info.*/
      Debug_Trace("Requested Inline solenoid valve to turn OFF...");
    }
    else
    {
      /* Do Nothing...*/
    }

    /* Update the Output pin state*/
    Temp_PinStatus = P12_InLineInputSolenoid_Relay_OFF_State;
    /* Update current status*/
    InLineInput_Current_Status = Operatation_OFF;
  }
  else
  {
    /* Do Nothing...*/
  }

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&InLineInput_Mux);

  /* If port Pin Required to update*/
  if (Temp_PinStatus != 0xFFU)
  {
    /* Switch ON / OFF Port Pin based on the result.*/
    digitalWrite(P10_InLineInputSolenoid_Relay, Temp_PinStatus);
  }
}

/* ************************************************************************
 * This function is get the status of the InLineInput request
 * *************************************************************************/
Sys_Operatation_Status GetStatus_InLineInput(void)
{
  Sys_Operatation_Status Return_Value;

  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&InLineInput_Mux);

  /* Check the Time is over or not.*/
  if (Get_Time_Elapse(InLineInput_Start_Time) >= P31_InLineInput_Delay_Time_In_ms)
  {
    /* Updare the status based on the current state.*/
    Return_Value = InLineInput_Current_Status;
  }
  else /* Still change is in progress*/
  {
    /* Set status to in progress..*/
    Return_Value = Operatation_InProgres;
  }

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&InLineInput_Mux);

  return (Return_Value);
}

/* ************************************************************************
 * This function is to Control Booster pump operatations
 * *************************************************************************/
void Control_BoostInput(Sys_Operatation_Status InputRequest)
{

  /* Variable to store current Time ( To avoid in mutex protection)*/
  uint32 Temp_Time;
  /* Variable to store Pin Status ( To avoid in mutex protection)*/
  uint32 Temp_MotorPinStatus = 0xFFU;
  uint32 Temp_SolenoidPinStatus = 0xFFU;

  /* Get the current time value*/
  Temp_Time = millis();

  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&InputBoost_Mux);

  /* Check wheather support is enabled..*/
  if (P13_InputBoostMotor_Support == STD_ON)
  {

    /* If input request is to ON*/
    if (InputRequest == Operatation_ON)
    {
      /* If previous status is OFF, then Update States changed Time*/
      if (Operatation_OFF == InputBoost_Current_Status)
      {
        /* Reset the Start time*/
        InputBoost_Start_Time = Temp_Time;

        /*Print Debug Info.*/
        Debug_Trace("Requested Booster pump to turn ON...");
      }
      else
      {
        /* Do Nothing...*/
      }

      /* Update the Output pin state*/
      Temp_MotorPinStatus = P15_InputBoostMotor_Relay_ON_State;
      Temp_SolenoidPinStatus = P18_InputBoostSolenoid_Relay_ON_State;
      /* Update current status*/
      InputBoost_Current_Status = Operatation_ON;
    }
    /* If input request is to make it OFF*/
    else if (InputRequest == Operatation_OFF)
    {
      /* If previous status is OFF, then Update States changed Time*/
      if (Operatation_ON == InputBoost_Current_Status)
      {
        /* Reset the Stope time*/
        InputBoost_Start_Time = Temp_Time;

        /*Print Debug Info.*/
        Debug_Trace("Requested Booster pump to turn OFF...");
      }
      else
      {
        /* Do Nothing...*/
      }

      /* Update the Output pin state*/
      Temp_MotorPinStatus = P16_InputBoostMotor_Relay_OFF_State;
      Temp_SolenoidPinStatus = P19_InputBoostSolenoid_Relay_OFF_State;
      /* Update current status*/
      InputBoost_Current_Status = Operatation_OFF;
    }
    else
    {
      /* Do Nothing...*/
    }
  }
  else /* If Booster support is dissabled*/
  {
    /* Input request if its valied, accordingly...*/
    InputBoost_Current_Status = ((InputRequest == Operatation_ON) ? Operatation_ON : Operatation_OFF);
    /* Reset the Stope time*/
    InputRO_Start_Time = millis();
  }

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&InputBoost_Mux);

  /* If port Pin Required to update*/
  if (Temp_MotorPinStatus != 0xFFU)
  {
    /* Switch ON / OFF Port Pin based on the result.*/
    digitalWrite(P14_InputBoostMotor_Relay, Temp_MotorPinStatus);
  }
  /* If port Pin Required to update*/
  if (Temp_SolenoidPinStatus != 0xFFU)
  {
    /* Switch ON / OFF Port Pin based on the result.*/
    digitalWrite(P17_InputBoostSolenoid_Relay, Temp_SolenoidPinStatus);
  }
}

/* ************************************************************************
 * This function is get the status of the Booster pump request
 * *************************************************************************/
Sys_Operatation_Status GetStatus_BoostInput(void)
{
  Sys_Operatation_Status Return_Value;

  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&InputBoost_Mux);

  /* Check the Time is over or not.*/
  if (Get_Time_Elapse(InputBoost_Start_Time) >= P33_InputBoost_Delay_Time_In_ms)
  {
    /* Updare the status based on the current state.*/
    Return_Value = InputBoost_Current_Status;
  }
  else /* Still change is in progress*/
  {
    /* Set status to in progress..*/
    Return_Value = Operatation_InProgres;
  }

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&InputBoost_Mux);

  return (Return_Value);
}

/* ************************************************************************
 * This function is to Control RO pump operatations
 * *************************************************************************/
void Control_ROInput(Sys_Operatation_Status InputRequest)
{

  /* Variable to store current Time ( To avoid in mutex protection)*/
  uint32 Temp_Time;
  /* Variable to store Pin Status ( To avoid in mutex protection)*/
  uint32 Temp_MotorPinStatus = 0xFFU;
  uint32 Temp_SolenoidPinStatus = 0xFFU;

  /* Get the current time value*/
  Temp_Time = millis();

  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&InputRO_Mux);

  /* Check wheather support is enabled..*/
  if (P1A_RO_Motor_Support == STD_ON)
  {
    /* If input request is to ON*/
    if (InputRequest == Operatation_ON)
    {
      /* If previous status is OFF, then Update States changed Time*/
      if (Operatation_OFF == InputRO_Current_Status)
      {
        /* Reset the Start time*/
        InputRO_Start_Time = Temp_Time;

        /*Print Debug Info.*/
        Debug_Trace("Requested RO pump and solenoid valve to turn ON...");
      }
      else
      {
        /* Do Nothing...*/
      }

      /* Update the Output pin state*/
      Temp_MotorPinStatus = P1C_RO_Motor_Relay_ON_State;
      Temp_SolenoidPinStatus = P1F_RO_Solenoid_Relay_ON_State;
      /* Update current status*/
      InputRO_Current_Status = Operatation_ON;
    }
    /* If input request is to make it OFF*/
    else if (InputRequest == Operatation_OFF)
    {
      /* If previous status is OFF, then Update States changed Time*/
      if (Operatation_ON == InputRO_Current_Status)
      {
        /* Reset the Stope time*/
        InputRO_Start_Time = Temp_Time;

        /*Print Debug Info.*/
        Debug_Trace("Requested RO pump and solenoid valve to turn OFF...");
      }
      else
      {
        /* Do Nothing...*/
      }

      /* Update the Output pin state*/
      Temp_MotorPinStatus = P1D_RO_Motor_Relay_OFF_State;
      Temp_SolenoidPinStatus = P20_RO_Solenoid_Relay_OFF_State;
      /* Update current status*/
      InputRO_Current_Status = Operatation_OFF;
    }
    else
    {
      /* Do Nothing...*/
    }
  }
  else /* If RO support is dissabled*/
  {
    /* Input request if its valied, accordingly...*/
    InputRO_Current_Status = ((InputRequest == Operatation_ON) ? Operatation_ON : Operatation_OFF);
    /* Reset the Stope time*/
    InputRO_Start_Time = millis();
  }

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&InputRO_Mux);

  /* If port Pin Required to update*/
  if (Temp_MotorPinStatus != 0xFFU)
  {
    /* Switch ON / OFF Port Pin based on the result.*/
    digitalWrite(P1B_RO_Motor_Relay, Temp_MotorPinStatus);
  }
  /* If port Pin Required to update*/
  if (Temp_SolenoidPinStatus != 0xFFU)
  {
    /* Switch ON / OFF Port Pin based on the result.*/
    digitalWrite(P1E_RO_Solenoid_Relay, Temp_SolenoidPinStatus);
  }
}

/* ************************************************************************
 * This function is get the status of the RO pump request
 * *************************************************************************/
Sys_Operatation_Status GetStatus_ROInput(void)
{
  Sys_Operatation_Status Return_Value;

  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&InputRO_Mux);

  /* Check the Time is over or not. OR if support is enabled, return current status, bypass timmer wait..*/
  if ((Get_Time_Elapse(InputRO_Start_Time) >= P35_RO_Delay_Time_In_ms) || (P1A_RO_Motor_Support != STD_ON))
  {
    /* Updare the status based on the current state.*/
    Return_Value = InputRO_Current_Status;
  }
  else /* Still change is in progress*/
  {
    /* Set status to in progress..*/
    Return_Value = Operatation_InProgres;
  }

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&InputRO_Mux);

  return (Return_Value);
}

/* ************************************************************************
 * This function is get the status of the High Presere Indication
 * Return value meaning
 *    Sensor_ON    ==> Indicate High Presure detected.
 *    Sensor_OFF   ==> Indicate NO High Presure detected.
 * *************************************************************************/
Sensor_InputStatus_Status GetStatus_HighPresere(void)
{
  uint16 HighPressure_ADC_Value;

  /* Variable to store current Time ( To avoid in mutex protection)*/
  uint32 Temp_Time;

  /* Read Current ADC value for High Presure */
  HighPressure_ADC_Value = Sys_Read_Processed_ADC_Value(P21_Analog_HighPresere);

  /* Get the current time value*/
  Temp_Time = millis();

  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&Sensor_HighPressure_Mux);

  /* Check if its detected as ON*/
  if (ADC_Check_Tolerance((uint32)HighPressure_ADC_Value, (uint32)P22_Analog_HighPresere_ON_Volt, P26_Analog_HighPresere_Tolerance) == E_OK)
  {

    /* Set Status to ON*/
    Sensor_HighPressure_Status = Sensor_ON;
    /* Reset the time*/
    Sensor_HighPressure_Start_Time = Temp_Time;
  }
  /* Check wheather its status is OFF*/
  else if (ADC_Check_Tolerance((uint32)HighPressure_ADC_Value, (uint32)P24_Analog_HighPresere_OFF_Volt, P26_Analog_HighPresere_Tolerance) == E_OK)
  {
    /* Check wheather time is elapsed to correct the status, And check time only if previous state is ON or Fault*/
    if ((Get_Time_Elapse(Sensor_HighPressure_Start_Time) >= P37_HighPresere_CollingTime_In_ms) ||
        (Sensor_HighPressure_Status == Sensor_OFF)) /* this check is to by pass timer check if already off, else time overflow cause issue after ~90 days and at start-up.*/
    {
      /* Set Status to ON*/
      Sensor_HighPressure_Status = Sensor_OFF;
    }
    else
    {
      /* Do nothing, share the old status stored in globale variable.*/
    }
  }
  else /* Fault detected.*/
  {
    /*Switching to fault shall be immidate*/
    Sensor_HighPressure_Status = Sensor_Fault;
    /* Reset the time*/
    Sensor_HighPressure_Start_Time = Temp_Time;
  }

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&Sensor_HighPressure_Mux);

  return (Sensor_HighPressure_Status);
}

/* ************************************************************************
 * This function is get the High Presere Sensor Raw Value.
 * *************************************************************************/
uint16 GetStatus_HighPresere_Sensor_Raw_Value(void)
{
  uint16 ADC_Raw_Value;

  /* Read Current ADC value for High Presere */
  ADC_Raw_Value = Sys_Read_Processed_ADC_Value(P21_Analog_HighPresere);

  /*Return Raw Value*/
  return (ADC_Raw_Value);
}

/* ************************************************************************
 * This function is get the status of the OverFlow Indication
 * Return value meaning
 *    Sensor_ON    ==> Indicate Overflow detected.
 *    Sensor_OFF   ==> Indicate Overflow NOT detected.
 * *************************************************************************/
Sensor_InputStatus_Status GetStatus_OverFlow(void)
{
  uint16 OverFlow_ADC_Value;

  /* Variable to store current Time ( To avoid in mutex protection)*/
  uint32 Temp_Time;

  /* Read Current ADC value for overflow */
  OverFlow_ADC_Value = Sys_Read_Processed_ADC_Value(P27_Analog_OverFlow);

  /* Get the current time value*/
  Temp_Time = millis();

  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&Sensor_OverFlow_Mux);

  /* Check if its detected as ON*/
  if (ADC_Check_Tolerance((uint32)OverFlow_ADC_Value, (uint32)P28_Analog_OverFlow_ON_Volt, P2C_Analog_OverFlow_Tolerance) == E_OK)
  {

    /* Set Status to ON*/
    Sensor_OverFlow_Status = Sensor_ON;
    /* Reset the time*/
    Sensor_OverFlow_Start_Time = Temp_Time;
  }
  /* Check wheather its status is OFF*/
  else if (ADC_Check_Tolerance((uint32)OverFlow_ADC_Value, (uint32)P2A_Analog_OverFlow_OFF_Volt, P2C_Analog_OverFlow_Tolerance) == E_OK)
  {
    /* Check wheather time is elapsed to correct the status, And check time only if previous state is ON or Fault*/
    if ((Get_Time_Elapse(Sensor_OverFlow_Start_Time) >= P39_OverFlow_CollingTime_In_ms) ||
        (Sensor_OverFlow_Status == Sensor_OFF)) /* this check is to by pass timer check if already off, else time overflow cause issue after ~90 days and at start-up.*/
    {
      /* Set Status to ON*/
      Sensor_OverFlow_Status = Sensor_OFF;
    }
    else
    {
      /* Do nothing, share the old status stored in globale variable.*/
    }
  }
  else /* Fault detected.*/
  {
    /*Switching to fault shall be immidate*/
    Sensor_OverFlow_Status = Sensor_Fault;
    /* Reset the time*/
    Sensor_OverFlow_Start_Time = Temp_Time;
  }

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&Sensor_OverFlow_Mux);

  return (Sensor_OverFlow_Status);
}

/* ************************************************************************
 * This function is get the OverFlow Sensor Raw Value.
 * *************************************************************************/
uint16 GetStatus_OverFlow_Sensor_Raw_Value(void)
{
  uint16 ADC_Raw_Value;

  /* Read Current ADC value for overflow */
  ADC_Raw_Value = Sys_Read_Processed_ADC_Value(P27_Analog_OverFlow);

  /*Return Raw Value*/
  return (ADC_Raw_Value);
}

/*
===========================================================================
===========================================================================
          Public functions related to System Operatations
===========================================================================
==========================================================================
*/

/* ************************************************************************
 * Function to Process the Control System
 * *************************************************************************/
void Process_ControlSystem(void)
{
  /* Variable to check if Init status is completed.*/
  uint8 Local_Init_status;
  /* Variable to flag wheather fault is detected.*/
  uint8 Fault_State_Check;

  uint32 OverFlow_Tank_Not_Full_Loop_Index;

  /* Get the State of Overflow, If over flow detected then Switch off..*/

  /* State Flow Is as mentioned below

    1. Here Logic is considered in assumption that this task is a Pre-emitable task.
    2. If certain delay is required to read the input then those delay are directely addedinto the task considering its a Pre-emitable task.
    3. All operatation inside this task is Sequential, if any current activity needs to perform the eacute same in another task.


      -Init_State ( Entry Point)
          - Shut down all
          - Check UV Sensor Working
          - Water Flow Working  ? Not considered, because same may be issue if Tank is already full.
      - Normal_Tank_Not_Full
          - Water Flow Keep on going
      - OverFlow_Tank_Not_Full
          - Tank Not full, But More than expected water flowed.
      - Tank_Full
          -Tank Full and Stoped the working.
      - Sensore_Fault
          - Fault in any of the sensor detected.
      - Emergency_Stop
          - If any failtel System error detected, Only exit is power on reset.

   */

  /* Switch to each state based on the state mechine flow.

  */

  switch (Get_Current_Opp_State())
  {

  /*******************************************************************************
   * Init_State:-                                                                *
   *                                                                             *
   * Process State Indicating Initialization sequence is in progress.            *
   * *****************************************************************************/
  case Init_State:
  {
    /*Print State change Message*/
    Log_State_Changed("Water Filer Operatation state changed to \"Init_State\" state.");
    /* Indicate current sate is executed.*/
    State_Change_completed();

    /* Set Init status to false.*/
    Clear_Check_Flag(Local_Init_status);

    /* DO complete Shut down, As a percolation.*/
    ShutDown_All();

    /*Wait to complete the shutdown.*/
    Delay_In_ms(CompleteSystem_ShutDown_Wait_Time);

    /*---------------------------------------------------------------------------------
      *                     Start Float Sensor validatation  checking.
     -----------------------------------------------------------------------------------*/
    /* Check wheather High Pressure detected detected as off, Because Now systen is Down*/
    if (GetStatus_HighPresere() == Sensor_OFF)
    {
      /* Set flag to true.*/
      True_Check_Flag(Local_Init_status);

      Debug_Trace("Correctely detect High presur Sensor is OFF, as expected in init.");
    }
    else if (GetStatus_HighPresere() == Sensor_ON)
    {
      /* Set status to check failed.*/
      False_Check_Flag(Local_Init_status);
      /* Get current raw value and print same ro debug trace.*/
      Debug_Trace("Failed to detect the High presur Sensor As OFF, At present detected as ON. Not expected at init. For reference Sensor RAW value is  %d ", GetStatus_HighPresere_Sensor_Raw_Value());
    }

    /*---------------------------------------------------------------------------------
     *                      Start High Presure Sensor validatation  checking.
    -----------------------------------------------------------------------------------*/
    /* Check wheather fault detected in flot sensor*/
    if (GetStatus_OverFlow() == Sensor_Fault)
    {
      /* Set status to check failed.*/
      False_Check_Flag(Local_Init_status);
      /* Get current raw value and print same ro debug trace.*/
      Debug_Trace("Failed to detect the Over flow Sensor, Could be because same is disconnected. For reference Sensor RAW value is  %d ", GetStatus_OverFlow_Sensor_Raw_Value());
    }
    else /* If sensor is in a valied state*/
    {
      Debug_Trace("Correctely detect Over flow Sensor Sensor is in valied state, as expected in init.");
    }

    /* If local Init status is OK, Then Start checking UV lamp.*/
    if (Is_Check_Flag_True(Local_Init_status))
    {
      /*---------------------------------------------------------------------------------
       *                      Start UV lamp Operatation checking.
      -----------------------------------------------------------------------------------*/

      /* Assumption by this time UV light could be OFF.*/
      /* Wait until UV lamp status changed to ON*/
      while (Get_UV_Lamp_Feedback() == UV_Lamp_Feedback_InProgres)
      {
        /*Wait to Switch the task excitation, each time wait for 100ms, because time to make UV light ON is high*/
        Delay_In_ms(100);
      }
      /* Check if UV Lamp status is in OFF*/
      if (Get_UV_Lamp_Feedback() == UV_Lamp_Feedback_OFF)
      {

        /* On the UV Light*/
        Control_UV_Lamp(UV_Lamp_ON);

        /* Wait until UV lamp status changed to ON*/
        while (Get_UV_Lamp_Feedback() == UV_Lamp_Feedback_InProgres)
        {
          /*Wait to Switch the task excitation, each time wait for 100ms, because time to make UV light ON is high*/
          Delay_In_ms(100);
        }
        /* Check if UV Lamp status is in ON*/
        if (Get_UV_Lamp_Feedback() == UV_Lamp_Feedback_ON)
        {
          Debug_Trace("UV Lamp testing passed with flying colours. And for Reference ON state value %s ", GetStatus_UV_Lamp_Sensor_Raw_Value());

          /* Set Init status to true.*/
          True_Check_Flag(Local_Init_status);
        }
        else /* Failed to detect the UV light*/
        {
          /* Get current raw value and print same ro debug trace.*/
          Debug_Trace("Failed to detect Wheather UV lamp is ON, could be because of faulty LDR or UV Lamp ss damaged, %s ", GetStatus_UV_Lamp_Sensor_Raw_Value());

          /* Indicate check failed.*/
          False_Check_Flag(Local_Init_status);
        }
      }
      else /* Feed back failed to detect wheather Lamp is OFF, So wait until it get ready after logging the error*/
      {
        /* Get current raw value and print same ro debug trace.*/
        Debug_Trace("Failed to detect Wheather UV lamp is OFF, could be because of faulty LDR or if LDR Not possinied properly, %s ", GetStatus_UV_Lamp_Sensor_Raw_Value());

        /* Indicate check failed.*/
        False_Check_Flag(Local_Init_status);
      }

    } /* End of if Is_Check_Flag_True(Local_Init_status) for UV lamp.*/
    /*---------------------------------------------------------------------------------
     *                      Start Next state conclusion.
    -----------------------------------------------------------------------------------*/
    /* If local Init status is OK, Then switch to New state.*/
    if (Is_Check_Flag_True(Local_Init_status))
    {

      /* Re-start Water flow counter*/
      Clean_Water_Flow_Counters();

      /* If tank is full move to Tank_Full state*/
      if (GetStatus_OverFlow() == Sensor_ON)
      {
        Set_Current_Opp_State(Tank_Full);
      }
      /* If tank is Not full move to Normal_Tank_Not_Full state*/
      else if (GetStatus_OverFlow() == Sensor_OFF)
      {
        Set_Current_Opp_State(Normal_Tank_Not_Full);
      }
      else
      {
        /* Do nothing.*/
      }
    } /* End of If (Local_Init_status == true)*/
    else
    {
      /* Do nothing.*/
    }

    break;
  }

    /*******************************************************************************
     * Normal_Tank_Not_Full:-                                                      *
     *                                                                             *
     * Indicate Tank is Not full and needs to On the Water flow.                   *
     * *****************************************************************************/
  case Normal_Tank_Not_Full:
  {
    /* Define New Perodic statement*/
    Define_Perodic_Statement(Filter_Block_Msg);
    Define_Perodic_Statement(UV_Lamp_Ready_Msg);

    /*Print State change Message*/
    Log_State_Changed("Water Filer Operatation state changed to \"Normal_Tank_Not_Full\" state.");

    /* If first time Entering this state from any other state.*/
    if (Is_Opp_State_Changed())
    {
      /* Reset the Perodic statement.*/
      ReStart_Perodic_Statement(Filter_Block_Msg);
      ReStart_Perodic_Statement(UV_Lamp_Ready_Msg);

      /* Enter in to Critical Section*/
      portENTER_CRITICAL(&Waterflow_Mux);

      /* Log the Current Water flow level when switched to this state*/
      Water_Flow_At_Normal_Tank_Not_Full = Get_Current_WaterFlowedInL();

      /* Exit from Critical Section. */
      portEXIT_CRITICAL(&Waterflow_Mux);

      /* Restart flow rate calculation. */
      ReStartFlowRate_Processing();
    }

    /* Indicate current sate is executed.*/
    State_Change_completed();

    /* Check Wheather level is Low, Over flow Nor detected, If low shall process further.*/
    if (GetStatus_OverFlow() == Sensor_OFF)
    {
      /* Check if presure is Normal, else switch to its state. */
      if (GetStatus_HighPresere() == Sensor_OFF)
      {

        /*---------------------------------------------------------------------------------
        *                      Check for UV lamp
        -----------------------------------------------------------------------------------*/
        /* Check if UV Lamp status is Already  ON*/
        if (Get_UV_Lamp_Feedback() != UV_Lamp_Feedback_ON)
        {
          /* Make UV lamp ON*/
          Control_UV_Lamp(UV_Lamp_ON);

          /* Wait until UV lamp status changed to ON*/
          while (Get_UV_Lamp_Feedback() == UV_Lamp_Feedback_InProgres)
          {
            /*Wait to Switch the task excitation, each time wait for 100ms, because time to make UV light ON is high*/
            Delay_In_ms(100);
          }
        } /* End of Initial UV lamp check for != ON*/

        /* Check if UV Lamp status is in ON*/
        if (Get_UV_Lamp_Feedback() == UV_Lamp_Feedback_ON)
        {
          /* Start the Perodic statement section for UV_Lamp_Ready_Msg, for every 12 Hour*/
          Start_Perodic_Statement(UV_Lamp_Ready_Msg, (12 * 60 * 60 * 1000))

              Debug_Trace("UV Lamp is ON and Ready to use. And for Reference Raw value of sensor%s ", GetStatus_UV_Lamp_Sensor_Raw_Value());

          /* Start the Perodic statement section for UV_Lamp_Ready_Msg, for every 12 Hour*/
          End_Perodic_Statement()

              /*---------------------------------------------------------------------------------
                                     Open Inlet.
              -----------------------------------------------------------------------------------*/
              /* If Inlet is Not already open.*/
              if (GetStatus_InLineInput() != Operatation_ON)
          {
            /* Switch On the inlet valve and wait until its get open.*/
            while (GetStatus_InLineInput() != Operatation_ON)
            {
              /* Switch it ON, For same operatation mode Timeout flag shall not re-Init*/
              Control_InLineInput(Operatation_ON);

              /* Add Nominal Delay for 100ms between each check.*/
              Delay_In_ms(100);
            } /* End of While loop */

            /* Print log once open First time*/
            Debug_Trace("Successfully open input solenoid to the water Filter.");

          } /* End of if (GetStatus_InLineInput() != Operatation_ON)*/
          /*---------------------------------------------------------------------------------
                                Open Boaster pump.
          -----------------------------------------------------------------------------------*/
          /* If Boaster pump is Not already open.*/
          if (GetStatus_BoostInput() != Operatation_ON)
          {
            /* Switch On the Boaster pump and wait until its get open.*/
            while (GetStatus_BoostInput() != Operatation_ON)
            {
              /* Switch it ON, For same operatation mode Timeout flag shall not re-Init*/
              Control_BoostInput(Operatation_ON);

              /* Add Nominal Delay for 100ms between each check.*/
              Delay_In_ms(100);
            } /* End of While loop */

            /* Print log once open First time*/
            Debug_Trace("Successfully started Boaster pump of the water Filter. ( If available)");

          } /* End of if (GetStatus_BoostInput() != Operatation_ON)*/

          /*---------------------------------------------------------------------------------
                                 Open RO pump and solenoid.
          -----------------------------------------------------------------------------------*/
          /* If RO pump and solenoid is Not already open.*/
          if (GetStatus_ROInput() != Operatation_ON)
          {
            /* Switch On the RO pump and solenoid, and wait until its get open.*/
            while (GetStatus_ROInput() != Operatation_ON)
            {
              /* Switch it ON, For same operatation mode Timeout flag shall not re-Init*/
              Control_ROInput(Operatation_ON);

              /* Add Nominal Delay for 100ms between each check.*/
              Delay_In_ms(100);
            } /* End of While loop */

            /* Print log once open First time*/
            Debug_Trace("Successfully started RO pump and solenoid of the water Filter. ( If available)");

          } /* End of if (GetStatus_ROInput() != Operatation_ON)*/

          /*---------------------------------------------------------------------------------
                                Check Wafer Potential Overflow.
           -----------------------------------------------------------------------------------*/
          /* Check wheather water flowed Above the mentioned limit.*/
          if (((uint32)(floor(Get_Current_SectionWaterFlowedInL() * 1000))) >= Nvm_Read_Each(NVM_ID_Calibration_WaterTankOverflowCapacity))
          {
            Debug_Trace("More water than expected transfer, Higher than tank capacity, But still Overflow is not detected by the sensore.");

            /* Switch to its respective state.*/
            Set_Current_Opp_State(OverFlow_Tank_Not_Full);

            /* switchoff the Inlet relay and both motor to avoid any damage*/
            Control_ROInput(Operatation_OFF);
            Control_BoostInput(Operatation_OFF);
            Control_InLineInput(Operatation_OFF);
            /* UV is not turning OFF as water may flow through filer to reduce the presure build up.*/
          }

          /* Check if water flow rate is above the mentioned Limit..*/
          /*---------------------------------------------------------------------------------
           *                   Check Wafer Potential Pile Burst, Higher flow rate.
           *---------------------------------------------------------------------------------*/

          /* If higher water flow detected.*/
          if (((uint32)(floor(Get_Instantinous_FlowRate_InLpM() * 1000))) > (Nvm_Read_Each(NVM_ID_Calibration_HighFlowRate)))
          {
            /* switchoff the Inlet relay and both motor to avoid any damage*/
            ShutDown_All();
            Debug_Trace("A high flow of water is detected By the system based on the configuration, So Switching Off. Current flow rate is %f, And Max Limit is %f ", Get_Instantinous_FlowRate_InLpM(), (double)(Nvm_Read_Each(NVM_ID_Calibration_HighFlowRate) / 1000));

            /* Set Global variable for High Presure Detection.*/
            HighWater_Flow_Detected = true;

            /* Take Action for High water flow rate */
            if ((Setting_Recovery_Actions)Nvm_Read_Each(NVM_ID_Seting_HighFlowRateWarningAction) == Recovery_Time_Bound)
            {
              Debug_Trace("Waitting for High flow rate to recover..");
              /* Wait for configured time and then switch back to same state, Come out only once Water flow go below required level.*/
              do
              {

                Delay_In_ms(Nvm_Read_Each(NVM_ID_Calibration_FlowRateWarningCollingTime));

                /* Wait until flow rate is reduced.*/
              } while (((uint32)(floor(Get_Instantinous_FlowRate_InLpM() * 1000))) > Nvm_Read_Each(NVM_ID_Calibration_HighFlowRate));
            }
            /* If recover is after Next power on, Then switch to Tank_Emergency_Stop state.*/
            else if ((Setting_Recovery_Actions)Nvm_Read_Each(NVM_ID_Seting_HighFlowRateWarningAction) == Recovery_On_PowerOn)
            {
              Debug_Trace("Switch state to \"Tank_Emergency_Stop\" because of Higher flow rate, And shall remain Down until Next Power ON.");
              /* Switch to the state representing overflow detected.*/
              Set_Current_Opp_State(Tank_Emergency_Stop);
            }
          }
          else /* High water flow did not detected.*/
          {
            /* Set Global variable for High Presure Detection.*/
            HighWater_Flow_Detected = false;
          }

          /* Check if water flow rate is above the mentioned Limit..*/
          /*---------------------------------------------------------------------------------
           *                   Check Wafer Potential Filter Block, Low flow rate.
           *---------------------------------------------------------------------------------*/

          /* If Lower water flow detected.*/
          if ((uint32)(floor(Get_Instantinous_FlowRate_InLpM() * 1000)) < Nvm_Read_Each(NVM_ID_Calibration_LowFlowRate))
          {

            /* Add perodic statement to show Once in every 2 Hour*/
            Start_Perodic_Statement(Filter_Block_Msg, (2 * 60 * 60 * 1000))

                /* Just show the warning for the Low flow Rate*/
                Debug_Trace("Potential Filer Jam. A Low flow of water is detected By the system based on the configuration. Current flow rate is %f, And Max Limit is %f ", Get_Instantinous_FlowRate_InLpM(), (double)(Nvm_Read_Each(NVM_ID_Calibration_LowFlowRate) / 1000));

            /* End above perodic statement */
            End_Perodic_Statement()

                /* Set Global variable for High Presure Detection.*/
                LowWater_Flow_Detected = true;

            /* No Action logic for Low flow rate is considered, As same did not make any sense. */
          }
          else /* Low water flow did not detected.*/
          {
            /* Set Global variable for Low Presure Detection.*/
            LowWater_Flow_Detected = false;
          }

        }    /* End of if (Get_UV_Lamp_Feedback() == UV_Lamp_Feedback_ON)*/
        else /* Failed to detect the UV light*/
        {
          /* switchoff the Inlet relay and both motor to avoid any damage*/
          Control_ROInput(Operatation_OFF);
          Control_BoostInput(Operatation_OFF);
          Control_InLineInput(Operatation_OFF);

          /* Get current raw value and print same ro debug trace.*/
          Debug_Trace("Failed to detect Wheather UV lamp as ON, could be because of faulty LDR or UV Lamp is damaged, %s ", GetStatus_UV_Lamp_Sensor_Raw_Value());

          /* Switch to the state representing UV lamp fault is detected.*/
          Set_Current_Opp_State(Tank_UV_Lamp_Fault);
        }

      } /* End of If for High presure Not detected*/
      /* High presure is detected.*/
      else if (GetStatus_HighPresere() == Sensor_ON)
      {
        Debug_Trace("High Water presure is detected, So Switching off the system, to avoid further damage");
        /* Switch to the state representing High presure is detected.*/
        Set_Current_Opp_State(Tank_High_Presure);

        /* switchoff the Inlet relay and both motor to avoid any damage*/
        Control_ROInput(Operatation_OFF);
        Control_BoostInput(Operatation_OFF);
        Control_InLineInput(Operatation_OFF);
        /* UV is not turning OFF as water may flow through filer to reduce the presure build up.*/
      } /* End of If for High presure Detected*/

    } /* End of if (GetStatus_OverFlow() == Sensor_OFF)*/
    /* If Over flow detected.*/
    else if (GetStatus_OverFlow() == Sensor_ON)
    {
      /* Switch to the state representing overflow detected.*/
      Set_Current_Opp_State(Tank_Full);

      /* Power down shall be performed in Next state.*/
    }

    break;
  }

    /*******************************************************************************
     * OverFlow_Tank_Not_Full:-                                                    *
     *                                                                             *
     * Indicate Indicate Tank full indicator not responding after considerable     *
     *            amound of water flows.                                           *
     * *****************************************************************************/
  case OverFlow_Tank_Not_Full:
  {
    Define_Perodic_Statement(OverFlow_Wait);
    /*Print State change Message*/
    Log_State_Changed("Water Filer Operatation state changed to \"OverFlow_Tank_Not_Full\" state.");

    /* If first time Entering this state from any other state.*/
    if (Is_Opp_State_Changed())
    {
      ReStart_Perodic_Statement(OverFlow_Wait);
    }

    /* Indicate current sate is executed.*/
    State_Change_completed();

    /* Shut Down Every think. */
    ShutDown_All();

    /* Check if the Action configured is Recovery_On_PowerOn.*/
    if ((Setting_Recovery_Actions)Nvm_Read_Each(NVM_ID_Seting_WaterTankOverflowAction) == Recovery_On_PowerOn)
    {
      Debug_Trace("Switch State to \"Tank_Emergency_Stop\" because Overflow sensor did not detect, But consumed More water that configured. For recover Please do Power OFF and then ON.");
      Debug_Trace("For Reference, Current water Filtered = %f, And configured level is %f", Get_Current_SectionWaterFlowedInL(), (double)(Nvm_Read_Each(NVM_ID_Calibration_WaterTankOverflowCapacity) / 1000));
      /* Switch to the state representing overflow detected.*/
      Set_Current_Opp_State(Tank_Emergency_Stop);
    }
    else /* Waite until the filter Overflow sensor detect its state OFF continuesly for moe than 5 Second.*/
    {
      Start_Perodic_Statement(OverFlow_Wait, 30000)

          Debug_Trace("Wait until Overflow sensor Detect as OFF for 5 Sec continually.");
      Debug_Trace("For Reference, Current water Filtered = %f, And configured level is %f", Get_Current_SectionWaterFlowedInL(), (double)(Nvm_Read_Each(NVM_ID_Calibration_WaterTankOverflowCapacity) / 1000));

      End_Perodic_Statement()

          OverFlow_Tank_Not_Full_Loop_Index = 0;

      do
      {
        /* Check if Tank Full is Not detected. If so clear the counter.*/
        if (GetStatus_OverFlow() == Sensor_OFF)
        {
          /* Reset the counter*/
          OverFlow_Tank_Not_Full_Loop_Index = 0;
        }
        else if (GetStatus_OverFlow() == Sensor_ON)
        {
          /* Increment the counter.*/
          OverFlow_Tank_Not_Full_Loop_Index++;
        }
        else /* Could be a fault So switch the State.*/
        {
          /* Switch to the state to Tank_Sensor_Fault.*/
          Set_Current_Opp_State(Tank_Sensor_Fault);

          /* Update condonation to exit the loop.*/
          OverFlow_Tank_Not_Full_Loop_Index = OverFlow_Tank_Not_Full_Wait_Time;
        }

        /* Give 100ms Delay*/
        Delay_In_ms(100);
        /* Waite until time out reached, Considering the delay of 100ms */
      } while (OverFlow_Tank_Not_Full_Loop_Index <= (uint32)(OverFlow_Tank_Not_Full_Wait_Time / 100));

      /* If No fault detected and Overflow detected, Then Switch to Tank full state.*/
      if ((GetStatus_OverFlow() == Sensor_ON) && (OverFlow_Tank_Not_Full_Loop_Index != OverFlow_Tank_Not_Full_Wait_Time))
      {
        Debug_Trace("System Recovered form Potential Overflow case.");
        /* Switch to the state to Tank_Sensor_Fault.*/
        Set_Current_Opp_State(Tank_Full);
      }
      else
      {
        /* Do nothing Loop back this state again.*/
      }

    } /* End of Recovery Mode check If statement.*/

    break;
  }

  /*******************************************************************************
   * Tank_Full:-                                                                 *
   *                                                                             *
   * Indicate Tank is full and Stop the flow.                                    *
   * *****************************************************************************/
  case Tank_Full:
  {
    /*Print State change Message*/
    Log_State_Changed("Water Filer Operatation state changed to \"Tank_Full\" state.");

    /* Wait for overflow colling time based on the paramayer P39_OverFlow_CollingTime_In_ms*/
    /* If first time Entering this state from any other state.*/
    if (Is_Opp_State_Changed())
    {
      /* Shut Down Every think. */
      ShutDown_All();

      Debug_Trace(" Waitting for %d ms Based on configuration after Overflow detected.", P39_OverFlow_CollingTime_In_ms);
      Delay_In_ms(P39_OverFlow_CollingTime_In_ms);
    }
    /* Indicate current sate is executed.*/
    State_Change_completed();

    /* Shut Down Every think. */
    ShutDown_All();

    /* switch the state based om the Over flow sensor state.*/
    if (GetStatus_OverFlow() == Sensor_OFF)
    {
      Set_Current_Opp_State(Normal_Tank_Not_Full);
    }
    else
    {
      /* Do Nothing.*/
    }

    break;
  }

    /*******************************************************************************
     * Tank_High_Presure:-                                                         *
     *                                                                             *
     * Indicate aHigh presure is detected at its input.                            *
     * *****************************************************************************/

  case Tank_High_Presure:
  {
    /*Print State change Message*/
    Log_State_Changed("Water Filer Operatation state changed to \"Tank_High_Presure\" state.");

    /* Wait for overflow colling time based on the paramayer P39_OverFlow_CollingTime_In_ms*/
    /* If first time Entering this state from any other state.*/
    if (Is_Opp_State_Changed())
    {
      Debug_Trace(" Waitting for %d ms Based on configuration after High pressure is detected.", P37_HighPresere_CollingTime_In_ms);
      Delay_In_ms(P37_HighPresere_CollingTime_In_ms);
    }

    /* Indicate current sate is executed.*/
    State_Change_completed();

    /* switchoff the Inlet relay and both motor to avoid any damage*/
    Control_InLineInput(Operatation_OFF);
    Control_BoostInput(Operatation_OFF);
    Control_ROInput(Operatation_OFF);

    /* Turn off the UV lamp once flow Rate is reached to Zero.*/
    if (Get_Instantinous_FlowRate_InLpM == 0)
    {
      /* Switch off the UV lamp, Because there was No Water flow.*/
      Control_UV_Lamp(UV_Lamp_OFF);
    }

    /* If presure is recovered, Then switch back to respective State.*/
    if (GetStatus_HighPresere() == Sensor_OFF)
    {
      Debug_Trace("Recovered from High presure detected.");
      /* switch the state based om the Over flow sensor state.*/
      if (GetStatus_OverFlow() == Sensor_OFF)
      {
        Set_Current_Opp_State(Normal_Tank_Not_Full);
      }
      /* If tank is full*/
      else if (GetStatus_OverFlow() == Sensor_ON)
      {
        Set_Current_Opp_State(Tank_Full);
      }
      else /* Some fault present*/
      {
        Set_Current_Opp_State(Tank_Sensor_Fault);
      }

    } /* End of GetStatus_HighPresere == Sensor_OFF If statement. */

    break;
  }

    /*******************************************************************************
     * Tank_Sensor_Fault:-                                                         *
     *                                                                             *
     * Indicate Some of the Sensor detected the Fault.                             *
     * *****************************************************************************/
  case Tank_Sensor_Fault:
  {
    /*Print State change Message*/
    Log_State_Changed("Water Filer Operatation state changed to \"Tank_Sensor_Fault\" state.");
    /* Indicate current sate is executed.*/
    State_Change_completed();

    /* Clear Check flag.*/
    Clear_Check_Flag(Fault_State_Check);

    /* DO complete Shut down, As a Pre-condation.*/
    ShutDown_All();

    /* Check wheather UV lamp processing completed.*/
    while (Get_UV_Lamp_Feedback() == UV_Lamp_Feedback_InProgres)
    {
      /*Wait to Switch the task excitation, each time wait for 100ms, because time to make UV light ON is high*/
      Delay_In_ms(100);
    }

    /* Check if UV lamp had fault*/
    if (Get_UV_Lamp_Feedback() == UV_Lamp_Feedback_Fault)
    {
      /* Set flag indicate fault detected*/
      False_Check_Flag(Fault_State_Check);
      Debug_Trace("Fault detected on UV lamp feedback, Could be because UV lamp failed. For reference, %s ", GetStatus_UV_Lamp_Sensor_Raw_Value());
    }
    else /* No fault*/
    {
      /* Set flag to true that fault not detected*/
      True_Check_Flag(Fault_State_Check);
    }

    /*---------------------------------------------------------------------------------
     *                      Start Float Sensor validatation  checking.
    -----------------------------------------------------------------------------------*/
    /* Check wheather fault detected in flot sensor*/
    if (GetStatus_HighPresere() == Sensor_Fault)
    {
      /* Set flag indicate fault detected*/
      False_Check_Flag(Fault_State_Check);
      /* Get current raw value and print same ro debug trace.*/
      Debug_Trace("Failed to detect the High presur Sensor, Could be because same is disconnected. For reference Sensor RAW value is  %d ", GetStatus_HighPresere_Sensor_Raw_Value());
    }
    else /* No fault.*/
    {
      /* Set flag to true that fault not detected*/
      True_Check_Flag(Fault_State_Check);
    }

    /*---------------------------------------------------------------------------------
    *                       Start High Presure Sensor validatation  checking.
    -----------------------------------------------------------------------------------*/
    /* Check wheather fault detected in flot sensor*/
    if (GetStatus_OverFlow() == Sensor_Fault)
    {
      /* Set flag indicate fault detected*/
      False_Check_Flag(Fault_State_Check);
      /* Get current raw value and print same ro debug trace.*/
      Debug_Trace("Failed to detect the Over flow Sensor, Could be because same is disconnected. For reference Sensor RAW value is  %d ", GetStatus_OverFlow_Sensor_Raw_Value());
    }
    else /* No fault.*/
    {
      /* Set flag to true that fault not detected*/
      True_Check_Flag(Fault_State_Check);
    }

    /*---------------------------------------------------------------------------------
    *              Take consultation for state switching based on the fault status.
    -----------------------------------------------------------------------------------*/
    /* Check if No fault is detected.*/
    if (Is_Check_Flag_True(Fault_State_Check))
    {
      /* Check global count is increased after the desired limit.*/
      Debug_Trace("All Fault are recovered, So now Re initiating System operatation.");

      /* Switch to Init state after fault is recovered.*/
      Set_Current_Opp_State(Init_State);
    }
    /* If fault is detected. */
    else if (Is_Check_Flag_False(Fault_State_Check))
    {
      Debug_Trace("Still fault not recovered, Shall wait for %f Sec and retry again...", (float)(Fault_Recheck_Wait_Time / 1000));

      /* Waite for configured time..*/
      Delay_In_ms(Fault_Recheck_Wait_Time);
    }

    break;
  }

  /*******************************************************************************
   * Tank_UV_Lamp_Fault:-                                                        *
   *                                                                             *
   * Detect fault in UV lamp, so recover after fault is recovered.               *
   * *****************************************************************************/
  case Tank_UV_Lamp_Fault:
  {
    /*Print State change Message*/
    Log_State_Changed("Water Filer Operatation state changed to \"Tank_UV_Lamp_Fault\" state.");
    /* Indicate current sate is executed.*/
    State_Change_completed();

    /* switchoff the Inlet relay and both motor to avoid any damage*/
    Control_ROInput(Operatation_OFF);
    Control_BoostInput(Operatation_OFF);
    Control_InLineInput(Operatation_OFF);
    Control_UV_Lamp(UV_Lamp_ON);

    /* Wait until UV lamp status changed to ON*/
    while (Get_UV_Lamp_Feedback() == UV_Lamp_Feedback_InProgres)
    {
      /*Wait to Switch the task excitation, each time wait for 100ms, because time to make UV light ON is high*/
      Delay_In_ms(100);
    }
    /* Check if UV Lamp status is in OFF*/
    if (Get_UV_Lamp_Feedback() == UV_Lamp_Feedback_ON)
    {

      /* OFF the UV Light*/
      Control_UV_Lamp(UV_Lamp_OFF);

      /* Wait until UV lamp status changed to OFF*/
      while (Get_UV_Lamp_Feedback() == UV_Lamp_Feedback_InProgres)
      {
        /*Wait to Switch the task excitation, each time wait for 100ms, because time to make UV light ON is high*/
        Delay_In_ms(100);
      }
      /* Check if UV Lamp status is in OFF*/
      if (Get_UV_Lamp_Feedback() == UV_Lamp_Feedback_OFF)
      {
        Debug_Trace("UV Lamp testing passed with flying colours. And for Reference OFF state value = %s ", GetStatus_UV_Lamp_Sensor_Raw_Value());

        /* Sensor is detected as OK, So switch to state "Tank_Full", from there switch to required state.*/
        Set_Current_Opp_State(Tank_Full);
      }
      else /* If Lamp Failed to switch to OFF*/
      {
        /* Failed Keep On Looping.*/
      }
    }
    else /* If Lamp Failed to switch to ON*/
    {
      /* Failed Keep On Looping.*/
    }

    break;
  }

  /*******************************************************************************
   * Tank_Emergency_Stop:-                                                       *
   *                                                                             *
   * Performe Emergency stop, Once inter in to this state It cannot come out.    *
   * Needs power cycle to Recover.                                               *
   * *****************************************************************************/
  case Tank_Emergency_Stop:
  {
    /*Print State change Message*/
    Log_State_Changed("Water Filer Operatation state changed to \"Tank_Emergency_Stop\" state.");
    /* Indicate current sate is executed.*/
    State_Change_completed();

    /* Initate Shut down*/
    ShutDown_All();

    /* And keep on this state until Next power On reset.*/

    break;
  }

  } /* End of Switch statement*/

  /* Generic State mechine / General monitering*/
  /*
     1. Check if any fault detected in UV
     2. Check if any fault detected in Over flow Sensor
     3. Check if any fault detected in Over High presure sensor.
  */
  /* Make sure currect state is not in Tank_Sensor_Fault detected */
  if ((Get_Current_Opp_State() != Tank_Sensor_Fault) && (Get_Current_Opp_State() != Tank_Emergency_Stop))
  {
    /* Check if fault detected in any of the sensor.*/
    if ((Get_UV_Lamp_Feedback() == UV_Lamp_Feedback_Fault) ||
        (GetStatus_HighPresere() == Sensor_Fault) ||
        (GetStatus_OverFlow() == Sensor_Fault))
    {
      /* Forfully Set next state to Sensor fault*/
      Set_Current_Opp_State(Tank_Sensor_Fault);

      /* Force shutdown to prevent any malfunction.*/
      ShutDown_All();

      /* Print debug info*/
      Debug_Trace("Sensor fault detected in Normal Execution, SO Switching to state \"Tank_Sensor_Fault\" and Excute force shutdown.");
    }
  }

  /* Logic for Perodic reset to make sure every think work properly.
   * This is mainely to avoid misinterpretation of the values stored for different time related record.
   */
  if (millis() >= System_Periodic_Reset_Time_in_ms)
  {

    /* Force shutdown to prevent any malfunction.*/
    ShutDown_All();

    /*Wait to complete the shutdown.*/
    Delay_In_ms(CompleteSystem_ShutDown_Wait_Time);

    /* Request for SW reset.*/
    Perform_Reset();

    /* Add infinit loop such that same shall not recover after this point.*/
    while (1)
    {
      /* Do nothing.*/
    }
  } /* End of if (millis() >= System_Periodic_Reset_Time_in_ms)*/
}


/* ************************************************************************
 * Function to Initialise all System related functions.
 * *************************************************************************/
void Init_MCU(void)
{
  /* WDG is already enabled.. So no change required.*/

  /* Initializes all port settings.*/
  pinMode(P01_UV_Lamp_Relay, OUTPUT);
  digitalWrite(P01_UV_Lamp_Relay, P03_UV_Lamp_Relay_OFF_State);

  pinMode(P10_InLineInputSolenoid_Relay, OUTPUT);
  digitalWrite(P10_InLineInputSolenoid_Relay, P12_InLineInputSolenoid_Relay_OFF_State);

  pinMode(P14_InputBoostMotor_Relay, OUTPUT);
  digitalWrite(P14_InputBoostMotor_Relay, P16_InputBoostMotor_Relay_OFF_State);

  pinMode(P17_InputBoostSolenoid_Relay, OUTPUT);
  digitalWrite(P17_InputBoostSolenoid_Relay, P19_InputBoostSolenoid_Relay_OFF_State);

  pinMode(P1B_RO_Motor_Relay, OUTPUT);
  digitalWrite(P1B_RO_Motor_Relay, P1D_RO_Motor_Relay_OFF_State);

  pinMode(P1E_RO_Solenoid_Relay, OUTPUT);
  digitalWrite(P1E_RO_Solenoid_Relay, P20_RO_Solenoid_Relay_OFF_State);
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

/* ************************************************************************
 * Function to initialise all required variables.
 * *************************************************************************/
void Init_System_Utilityes_Variables(void)
{
  /* Variable to store the current UV lamp state set by SW.*/
  UV_Lamp_Current_Status = UV_Lamp_OFF;
  /* Variable to store the Time at which UV light Started / Stopped.*/
  UV_Lamp_Start_Time = Int_Zero;

  /* Variable to store the current IN-Line request set by SW.*/
  InLineInput_Current_Status = Operatation_OFF;
  /* Variable to store the Time at which In-Line Input Started / stoped.*/
  InLineInput_Start_Time = Int_Zero;

  /* Variable to store the current Input Boost request set by SW.*/
  InputBoost_Current_Status = Operatation_OFF;
  /* Variable to store the Time at which InputBoost Input Started / stoped.*/
  InputBoost_Start_Time = Int_Zero;

  /* Variable to store the current Input RO request set by SW.*/
  InputRO_Current_Status = Operatation_OFF;
  /* Variable to store the Time at which Input RO Input Started / stoped.*/
  InputRO_Start_Time = Int_Zero;

  /* Variable to store the current High presure sensor input.*/
  Sensor_HighPressure_Status = Sensor_OFF;
  /* Variable to store the Time at which High presure sensor input Started / stoped.*/
  Sensor_HighPressure_Start_Time = Int_Zero;

  /* Variable to store the current OverFlow sensor input.*/
  Sensor_OverFlow_Status = Sensor_OFF;
  /* Variable to store the Time at which OverFlow sensor input Started / stoped.*/
  Sensor_OverFlow_Start_Time = Int_Zero;

  /* Variable to store the init status of the Operatation.*/
  Current_Operatation_Status = Init_State;

  /* Variable to store the water flow detected when state changed to "Normal_Tank_Not_Full" */
  Water_Flow_At_Normal_Tank_Not_Full = 0;

  /* Use to store the Next Index to be filed.*/
  Water_FlowRate_Log_Current_Index = 0;

  /* Use to store Instantinous Index, Once reached 60, shall hold there.*/
  Water_FlowRate_Log_Instantaneous_Index = 0;

  /* Store Previous Logged Value. Shall help to detect first case and avoid travising buffer*/
  Previous_Section_Value = Invalue_Flow_Value_InL;

  /*Store final processed Instantaneous flow value.*/
  Final_Instantinous_Flow_In_LpM = Invalue_Flow_Value_InL;

  /* Global Variable to store the High flow rate detected.*/
  HighWater_Flow_Detected = false;

  /* Global Variable to store the High flow rate detected.*/
  LowWater_Flow_Detected = false;
}

/*
===========================================================================
===========================================================================
          Functions for water flow meter....
===========================================================================
==========================================================================
*/

/* *********************************************************************************
 * ISR Function to trigen when ever over flow is detected.......
 *************************************************************************************/
void IRAM_ATTR CounterOverflow_ISR(void *arg)
{

  /* Increment Over flow counter */
  CounterOverflow = CounterOverflow + 1;

  /* Clear counter*/
  PCNT.int_clr.val = BIT(PCNT_UNIT_Used);
  pcnt_counter_clear(PCNT_UNIT_Used);
}

/* *********************************************************************************
 * Function to init PCNT based on HW configuration..
 *************************************************************************************/

void Init_PulseCounter(void)
{
  pcnt_config_t pcntFreqConfig = {};                    // Declear variable for cinfig
  pcntFreqConfig.pulse_gpio_num = PCNT_INPUT_SIG_IO;    // Set the port ping using for counting
  pcntFreqConfig.pos_mode = PCNT_COUNT_INC;             // set Counter mode: Increase counter value
  pcntFreqConfig.counter_h_lim = PCNT_Overflow_LIM_VAL; // Set Over flow Interupt / event value
  pcntFreqConfig.unit = PCNT_UNIT_Used;                 //  Set Pulsos unit to ne used
  pcntFreqConfig.channel = PCNT_CHANNEL_0;              //  select PCNT channel 0
  pcnt_unit_config(&pcntFreqConfig);                    // Configure PCNT.

  pcnt_counter_pause(PCNT_UNIT_Used); // Pause PCNT counter such that we can set event.
  pcnt_counter_clear(PCNT_UNIT_Used); // Clear PCNT counter to avoid ant mis counting.

  pcnt_event_enable(PCNT_UNIT_Used, PCNT_EVT_H_LIM);                 // Enable event for when PCNT watch point event: Maximum counter value
  pcnt_isr_register(CounterOverflow_ISR, NULL, 0, &user_isr_handle); // Set call back function for the Event.
  pcnt_intr_enable(PCNT_UNIT_Used);                                  // Enable PCNT

  pcnt_counter_resume(PCNT_UNIT_Used); // Re-started PCNT.

  Debug_Trace("PCNT Init Completed....");
}

/* *********************************************************************************
   Function to clean the Counter and its variables......
*************************************************************************************/
void Clean_Water_Flow_Counters(void)
{

  pcnt_counter_pause(PCNT_UNIT_Used); // Pause PCNT counter such that we can set event.

  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&Waterflow_Mux);

  CounterOverflow = 0; // Clear global Over flow counter.

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&Waterflow_Mux);

  pcnt_counter_clear(PCNT_UNIT_Used);  // Clean Pulse Counter...
  pcnt_counter_resume(PCNT_UNIT_Used); // Re-started PCNT.
}

/* *********************************************************************************
   Function to get total water flowed from last clear / restart in Liters......
*************************************************************************************/
double Get_Current_WaterFlowedInL(void)
{
  double Return_Water_Flowed_InL;
  int16_t Current_Counter_Value;
  uint32 Calib_Value;

  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&Waterflow_Mux);

  /* Consider Over-flowed values*/
  Return_Water_Flowed_InL = CounterOverflow * PCNT_Overflow_LIM_VAL;

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&Waterflow_Mux);

  /*Read the counter Value */
  pcnt_get_counter_value(PCNT_UNIT_Used, &Current_Counter_Value);

  /* Add Current Counter Value*/
  Return_Water_Flowed_InL += Current_Counter_Value;

  /* Get NVM Calib Value*/
  Calib_Value = Nvm_Read_Each(NVM_ID_Calibration_FlowMeaterFactor);

  /* Check is value is Zero, If So applay safe default value.*/
  Calib_Value = ((Calib_Value == 0) ? WaterFlow_Default_Calib_VAL : Calib_Value);

  /* Convert In to Liters*/
  /* Consider the Value in NVM paramater NVM_ID_Calibration_FlowMeaterFactor = Number of counter tick for 1 Letter of water.*/
  Return_Water_Flowed_InL = Return_Water_Flowed_InL / Calib_Value;

  return (Return_Water_Flowed_InL);
}

/* *********************************************************************************
   Function to get total water flowed after started last time or Now ongoing section......
*************************************************************************************/
double Get_Current_SectionWaterFlowedInL(void)
{
  double Current_SectionWaterFlowedInL;
  double TotalWaterFlowed;

  /* Get total water flowed till this time*/
  TotalWaterFlowed = Get_Current_WaterFlowedInL();

  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&Waterflow_Mux);

  /* If stored water is less than current one, The ignore and return Zero*/
  if (Water_Flow_At_Normal_Tank_Not_Full <= TotalWaterFlowed)
  {
    Current_SectionWaterFlowedInL = (TotalWaterFlowed - Water_Flow_At_Normal_Tank_Not_Full);
  }
  else /* If difference is Negative.*/
  {
    /* Set it to Zero.*/
    Current_SectionWaterFlowedInL = 0;
  }

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&Waterflow_Mux);

  return (Current_SectionWaterFlowedInL);
}

/* *********************************************************************************
    Cyclic runnable to process the water glow rate based on the previous water flow value
    Predacity expected in 1000ms ( Not configurable.)
*************************************************************************************/
void ProcessWaterFlowRate(void)
{
  double Temp_Local_Current_Value;
  uint8 LoopIndex;

  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&Waterflow_Mux);

  /* Check if its NOT the first loop*/
  if (Previous_Section_Value != Invalue_Flow_Value_InL)
  {

    /* Get current total value */
    Temp_Local_Current_Value = Get_Current_WaterFlowedInL();
    /* Check for Negative value possibility*/
    if (Previous_Section_Value <= Temp_Local_Current_Value)
    {
      /* Load delta into the Per Second buffer*/
      Water_FlowRate_PerSec[Water_FlowRate_Log_Current_Index] = (Temp_Local_Current_Value - Previous_Section_Value);
    }
    else /* If Diff is Negative Store 0*/
    {
      /* store Zero*/
      Water_FlowRate_PerSec[Water_FlowRate_Log_Current_Index] = 0;
    }

    /*Update previous value*/
    Previous_Section_Value = Temp_Local_Current_Value;

    /* Increment buffer Index*/
    Water_FlowRate_Log_Current_Index++;

    /* Check if buffer index overflowed*/
    if (Water_FlowRate_Log_Current_Index >= 60)
    {
      /* Reset Index to zero.*/
      Water_FlowRate_Log_Current_Index = 0;
    }

    /* Loop for get the sum.*/
    for (LoopIndex = 0, Temp_Local_Current_Value = 0; LoopIndex < 60; LoopIndex++)
    {
      /* Clear buffer*/
      Temp_Local_Current_Value += Water_FlowRate_PerSec[LoopIndex];
    }

    /* Increment buffer Instantaneous Index*/
    Water_FlowRate_Log_Instantaneous_Index++;

    /* Check if buffer Instantaneous index overflowed*/
    if (Water_FlowRate_Log_Instantaneous_Index >= 60)
    {
      /* Reset Instantaneous Index to zero.*/
      Water_FlowRate_Log_Instantaneous_Index = 60;

      /* Update final value, No additional calculation required after first 60 Iteration*/
      Final_Instantinous_Flow_In_LpM = Temp_Local_Current_Value;
    }
    else /* For First 60 Iteration*/
    {

      /* Update final value*/
      Final_Instantinous_Flow_In_LpM = (double)(Temp_Local_Current_Value * (60 / Water_FlowRate_Log_Instantaneous_Index));
    }
  }
  /* Its the first loop*/
  else
  {
    /* Get the current value*/
    Previous_Section_Value = Get_Current_WaterFlowedInL();

    /* Clear Variables */
    Water_FlowRate_Log_Current_Index = 0;
    Water_FlowRate_Log_Instantaneous_Index = 0;

    Final_Instantinous_Flow_In_LpM = Invalue_Flow_Value_InL;

    /* Clear all buffer element*/
    for (LoopIndex = 0; LoopIndex < 60; LoopIndex++)
    {
      /* Clear buffer*/
      Water_FlowRate_PerSec[LoopIndex] = 0;
    }
  }

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&Waterflow_Mux);
}

/* *********************************************************************************
    This function is to Re-Start the flow Rate processing.
*************************************************************************************/
void ReStartFlowRate_Processing(void)
{
  uint8 LoopIndex;
  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&Waterflow_Mux);

  /* Clear the current value*/
  Previous_Section_Value = Invalue_Flow_Value_InL;

  /* Clear Variables */
  Water_FlowRate_Log_Current_Index = 0;
  Water_FlowRate_Log_Instantaneous_Index = 0;

  Final_Instantinous_Flow_In_LpM = Invalue_Flow_Value_InL;

  /* Clear all buffer element*/
  for (LoopIndex = 0; LoopIndex < 60; LoopIndex++)
  {
    /* Clear buffer*/
    Water_FlowRate_PerSec[LoopIndex] = 0;
  }

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&Waterflow_Mux);
}

/* *********************************************************************************
   Function to get Instantinous FlowRate In LpM
*************************************************************************************/
double Get_Instantinous_FlowRate_InLpM(void)
{

  double Temp_Local_Current_Value;

  /* Enter in to Critical Section*/
  portENTER_CRITICAL(&Waterflow_Mux);

  Temp_Local_Current_Value = Final_Instantinous_Flow_In_LpM;

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&Waterflow_Mux);

  /* Check is Its Invalid, If so return Zero*/
  if (Temp_Local_Current_Value == Invalue_Flow_Value_InL)
  {
    /* Set Return to Zero.*/
    Temp_Local_Current_Value = 0;
  }

  /* Return the value.*/
  return (Temp_Local_Current_Value);
}

/* *********************************************************************************
   Function to return wheather any High flow rate is detected.
*************************************************************************************/
int Is_HighWaterFlowRateDetected(void)
{

  /* Return true if detected*/
  return (HighWater_Flow_Detected == true);
}

/* *********************************************************************************
   Function to return wheather any Low flow rate is detected.
*************************************************************************************/
int Is_LowWaterFlowRateDetected(void)
{

  /* Return true if detected*/
  return (LowWater_Flow_Detected == true);
}






