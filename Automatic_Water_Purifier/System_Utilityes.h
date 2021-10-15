
#ifndef System_Utilityes_H
#define System_Utilityes_H

#include "MyStdTypes.h"
#include "driver/pcnt.h"

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

/* MAcro defining the wait Time to complete System shutdown from start.*/
#define CompleteSystem_ShutDown_Wait_Time 6000 /* Configured as 6 Sec*/

/* Macro to defining the wait Time to Restart the fault checking in ms*/
#define Fault_Recheck_Wait_Time 10000 /* Configured as 2 Sec*/

/* Macro to defining the wait Time after Overflow detected without sensor in ms*/
#define OverFlow_Tank_Not_Full_Wait_Time 5000 /* Configured as 5 Sec*/

/* Macro to represent the Time at which Reset needs to be triggered after system is powered on
   Here configured for 45 Days = 3888000000ms. So reset after every 45days.
*/
#define System_Periodic_Reset_Time_in_ms 3888000000U

/* MAcro to specify wheather system specific Configuration needs to be get from NVM or NOT*/
#define System_Config_From_NVM_Support STD_OFF

/* MAcro to define ADC Max value, Same shall use to calculate the tolerance value for the ADC sensor values.*/
#define System_ADC_Max_Value 4095

 /* MAcro to store the debounce time to registor Fault state, And register fault only after debouncing time is elapsed.
      This is because ADC shall not change its level like GPIO, 
      And we did not want to register fault on transition from ON to OFF and vis versa, To avoid False positive fault can trigger.
    1. Unit shall be in ms 
    2. Please make sure Debounce time shall be double that of Filter window configured for ADC, else False positive fault can trigger.*/
#define ADC_Sensor_FaultDebouncing_Time_ms 700


/*-----------------------------------------------------------------------------
 *  System Utility related Configuration END
-------------------------------------------------------------------------------*/

/*******************************************************************************
 *  Program Specific data types.
 *******************************************************************************/
/*Following Enumerators are to represent the UV lamp status*/
enum Sys_UV_Lamp_Status
{
  UV_Lamp_ON = 0x5A,    /* Indicate Lamp is ON. */
  UV_Lamp_OFF = 0x0F,   /* Indicate Lamp is OFF.*/
  UV_Lamp_UnInit = 0xA9 /* Indicate Lamp is Uninit.*/
};

/*Following Enumerators are to represent the UV lamp status*/
enum Sys_UV_Lamp_Feedback_Status
{
  UV_Lamp_Feedback_ON = 0x98,        /* Indicate Lamp is ON Via feedback. */
  UV_Lamp_Feedback_OFF = 0x89,       /* Indicate Lamp is OFF Via feedback.*/
  UV_Lamp_Feedback_InProgres = 0x5A, /* Indicate Lamp is Starting is in progress.*/
  UV_Lamp_Feedback_Fault = 0xE0      /* Indicate Lamp Fault detected Via feedback.*/
};

/* Enum to define Operatation Status*/
enum Sys_Operatation_Status
{
  Operatation_ON = 0x5A,       /* Indicate request is to ON. */
  Operatation_OFF = 0x0F,      /* Indicate request is to OFF.*/
  Operatation_InProgres = 0xA9 /* Indicate request is to In-Progres.*/
};

/* Enum to define Operatation Status*/
enum Sensor_InputStatus_Status
{
  Sensor_ON = 0x44,   /* Indicate Sensor is ON. */
  Sensor_OFF = 0x48,  /* Indicate Sensor is OFF.*/
  Sensor_Fault = 0x94 /* Indicate Sensor is Fault.*/
};

/* Enum to define the state mechine of the Operatations*/
enum System_Operatation_Status
{
  Init_State = 0x45,             /* Indicate Initialization sequence is in progress.*/
  Normal_Tank_Not_Full = 0x65,   /* Indicate Tank is Not full and needs to On the Water flow*/
  OverFlow_Tank_Not_Full = 0x75, /* Indicate Tank full indicator not responding after considerable amound of water flows.*/
  Tank_Full = 0x85,              /* Indicate Tank is full and Stop the flow..*/
  Tank_High_Presure = 0x99,      /* Indicate Some of the High Presure is detected at the input.*/
  Tank_Sensor_Fault = 0x95,      /* Indicate Some of the Sensor detected the Fault.*/
  Tank_UV_Lamp_Fault = 0x59,     /* Indicate Some of the UV lamp Sensor detected the Fault or Wrong reading based on lamp state..*/
  Tank_Emergency_Stop = 0xA5     /* Performe Emergency stop, Once inter in to this state It cannot come out. Needs power cycle.*/
};

/*******************************************************************************
 *  Macros
 *******************************************************************************/

#define PCNT_UNIT_Used PCNT_UNIT_0                  /* Select the Pulse Count 0  as the unit..*/
#define PCNT_Overflow_LIM_VAL 10000                 /* Set the max limit to trigger the interrupt*/
#define WaterFlow_Default_Calib_VAL 1000            /* Paramater represent the default Calib value to be used if configured value is wrong.*/
#define PCNT_INPUT_SIG_IO P2D_WaterFlowSensor_Input /* Pulse Input selected as GPIO 4 */

/*******************************************************************************
 *  Macro Functios
 *******************************************************************************/



/*******************************************************************************
 *  Public Function Definations Functions
 *******************************************************************************/

extern void Init_MCU(void);
extern void Init_System_Utilityes_Variables(void);
extern void Init_GPT_ICU(void);
extern void Perform_Reset(void);

extern void Init_PulseCounter(void);
extern void Clean_Water_Flow_Counters(void);
extern double Get_Current_WaterFlowedInL(void);
extern double Get_Current_SectionWaterFlowedInL(void);
extern void ProcessWaterFlowRate(void);
extern void ReStartFlowRate_Processing(void);
extern double Get_Instantinous_FlowRate_InLpM(void);
extern int Is_HighWaterFlowRateDetected(void);
extern int Is_LowWaterFlowRateDetected(void);



#endif /* End of  System_Utilityes_H */
