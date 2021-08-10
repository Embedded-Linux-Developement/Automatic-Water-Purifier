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

/* Variable to store the current UV lamp state set by SW.*/
static Sys_UV_Lamp_Status UV_Lamp_Current_Status = UV_Lamp_OFF;
/* Variable to store the Time at which UV light Started / Stopped.*/
static uint32 UV_Lamp_Start_Time = Int_Zero;

/* Variable to store the current IN-Line request set by SW.*/
static Sys_Operatation_Status InLineInput_Current_Status = Operatation_OFF;
/* Variable to store the Time at which In-Line Input Started / stoped.*/
static uint32 InLineInput_Start_Time = Int_Zero;


/* Variable to store the current Input Boost request set by SW.*/
static Sys_Operatation_Status InputBoost_Current_Status = Operatation_OFF;
/* Variable to store the Time at which InputBoost Input Started / stoped.*/
static uint32 InputBoost_Start_Time = Int_Zero;

/* Variable to store the current Input RO request set by SW.*/
static Sys_Operatation_Status InputRO_Current_Status = Operatation_OFF;
/* Variable to store the Time at which Input RO Input Started / stoped.*/
static uint32 InputRO_Start_Time = Int_Zero;


/*******************************************************************************
 *  Functions Forward decleratations deceleration
*******************************************************************************/


/*This function is to Control UV Lamp operatations*/
 static void Control_UV_Lamp(Sys_UV_Lamp_Status InputRequest);
 static Sys_UV_Lamp_Status Get_UV_Lamp_Feedback( void );
 static void Control_InLineInput(Sys_Operatation_Status InputRequest);
 static Sys_Operatation_Status GetStatus_InLineInput(void);
 static uint16 Sys_Read_Processed_ADC_Value(int GPIO_Port_pin);

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
 * This Function to read the processed ADC value based Filter designed.
 * *************************************************************************/
 uint16 Sys_Read_Processed_ADC_Value(int GPIO_Port_pin)
 {
   uint16 Return_Value;
   /* At present ADC filtering logic are not implemented so reading directely from the ADC.*/
   Return_Value = analogRead(GPIO_Port_pin);
 }

/* ************************************************************************
 * Function to master ShutDown the filtering.
 * *************************************************************************/
void ShutDown_All(void)
{

  /* Power off RO motor if same is configured.*/
  if (P1A_RO_Motor_Support == STD_ON)
  {
    /* Switch off the Motor*/
    digitalWrite(P1B_RO_Motor_Relay, P1D_RO_Motor_Relay_OFF_State);
    /* Switch off Solenoid associated with same. */
    digitalWrite(P1E_RO_Solenoid_Relay, P20_RO_Solenoid_Relay_OFF_State);

  }

  /* Power off Booster pump if same is configured.*/
  if (P13_InputBoostMotor_Support == STD_ON)
  {
    /* Switch off the Motor*/
    digitalWrite(P14_InputBoostMotor_Relay, P16_InputBoostMotor_Relay_OFF_State);
    /* Switch off Solenoid associated with same. */
    digitalWrite(P17_InputBoostSolenoid_Relay, P19_InputBoostSolenoid_Relay_OFF_State);

  }

  /* Disconnect the Inlet Solenoids*/
  digitalWrite(P10_InLineInputSolenoid_Relay, P12_InLineInputSolenoid_Relay_OFF_State);

  /* Switch off the UV light.*/
  Control_UV_Lamp(UV_Lamp_OFF);

}


/* ************************************************************************
 * This function is to Control UV Lamp operatations
 * *************************************************************************/
void Control_UV_Lamp(Sys_UV_Lamp_Status InputRequest)
{

  /* Power ON the Lamp is requested.*/
  if (InputRequest == UV_Lamp_ON)
  {
    /* Update Current time, if previous state is OFF*/
    if (UV_Lamp_Current_Status == UV_Lamp_OFF)
    {
      /* Reset the Start time*/
      UV_Lamp_Start_Time = millis();
    }

    /* Switch ON the UV light.*/
    digitalWrite(P01_UV_Lamp_Relay, P02_UV_Lamp_Relay_ON_State);
    /* Up date the status.*/
    UV_Lamp_Current_Status = UV_Lamp_ON;
  }
  else if (InputRequest == UV_Lamp_OFF)
  {

    /* Update Current time, if previous state is ON*/
    if (UV_Lamp_Current_Status == UV_Lamp_ON)
    {
      /* Reset the Start time*/
      UV_Lamp_Start_Time = millis();
    }

    /* Switch off the UV light.*/
    digitalWrite(P01_UV_Lamp_Relay, P03_UV_Lamp_Relay_OFF_State);
    /* Up date the status.*/
    UV_Lamp_Current_Status = UV_Lamp_OFF;
  }
  else
  {
    /* Do nothing because, request is not valied.*/
  }
}

/* ************************************************************************
 * This function is to Get Feedback status of UV Lamp operatations.
 * *************************************************************************/
Sys_UV_Lamp_Status Get_UV_Lamp_Feedback( void )
{
  /* Return variable..*/
  Sys_UV_Lamp_Status ReturnStatus = UV_Lamp_Feedback_Fault;
  Sys_UV_Lamp_Status LDR_1_Status = UV_Lamp_Feedback_Fault;
  Sys_UV_Lamp_Status LDR_2_Status = UV_Lamp_Feedback_Fault;
  uint16 UV_LDR_1_ADC_Value;
  uint16 UV_LDR_2_ADC_Value;

  /* Check if configuration of feedback is enabled*/
  if (UV_Feedback_None != P2E_UV_Feedback_Support)
  {

    /* Check if enough time elapsed after UV Lamp is turned ON*/
   if(Get_Time_Elapse(UV_Lamp_Start_Time) >= P2F_UV_On_Delay_Time_In_ms)
   {
    /* Read ADC value of both LDR. Filtering of ADC is not considered for now... */
    UV_LDR_1_ADC_Value = Sys_Read_Processed_ADC_Value(P04_UV_Lamp_Analog_LDR_1);
    UV_LDR_2_ADC_Value = Sys_Read_Processed_ADC_Value(P0A_UV_Lamp_Analog_LDR_2);

    /* Check if LDR 1 detected as UV light ON*/
    if ( Check_Tolerance((uint32)UV_LDR_1_ADC_Value,(uint32)P05_UV_Lamp_Analog_LDR_1_ON_Volt, P09_UV_Lamp_Analog_LDR_1_Tolerance) == E_OK)
      {
      /* Check if Current UV lamp state is also ON, Else decleared as fault*/
      LDR_1_Status = (UV_Lamp_Current_Status == UV_Lamp_ON) ? UV_Lamp_Feedback_ON : UV_Lamp_Feedback_Fault;
    }
    /* Check wheather status is OFF.*/
    else if (Check_Tolerance((uint32)UV_LDR_1_ADC_Value, (uint32)P07_UV_Lamp_Analog_LDR_1_OFF_Volt, P09_UV_Lamp_Analog_LDR_1_Tolerance) == E_OK)
    {
      /* Check if Current UV lamp state is also OFF, Else decleared as fault*/
      LDR_1_Status = (UV_Lamp_Current_Status == UV_Lamp_OFF) ? UV_Lamp_Feedback_OFF : UV_Lamp_Feedback_Fault;
    }
    else /* Unknown State detected, So setting as fault.*/
    {
      LDR_1_Status = UV_Lamp_Feedback_Fault;
    }

    /* Check if LDR 2 detected as UV light ON*/
    if (Check_Tolerance((uint32)UV_LDR_2_ADC_Value,(uint32)P0B_UV_Lamp_Analog_LDR_2_ON_Volt, P0F_UV_Lamp_Analog_LDR_2_Tolerance) == E_OK)
    {
      /* Check if Current UV lamp state is also ON, Else decleared as fault*/
      LDR_2_Status = (UV_Lamp_Current_Status == UV_Lamp_ON) ? UV_Lamp_Feedback_ON : UV_Lamp_Feedback_Fault;
    }
    /* Check wheather status is OFF.*/
    else if (Check_Tolerance((uint32)UV_LDR_2_ADC_Value, (uint32)P0D_UV_Lamp_Analog_LDR_2_OFF_Volt, P0F_UV_Lamp_Analog_LDR_2_Tolerance) == E_OK)
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
   else  /* If time is Not Elapsed yet to read the feedback status.*/
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

  /* Return final status*/
  return (ReturnStatus);
}


/* ************************************************************************
 * This function is to Control InLine waterInput operatations
 * *************************************************************************/
void Control_InLineInput(Sys_Operatation_Status InputRequest)
{
  /* If input request is to ON*/
  if (InputRequest == Operatation_ON)
  {
    /* If previous status is OFF, then Update States changed Time*/
    if (Operatation_OFF == InLineInput_Current_Status)
    {
      /* Reset the Start time*/
      InLineInput_Start_Time = millis();
    }
    else
    {
      /* Do Nothing...*/
    }

    /* Update the Output pin state*/
    digitalWrite(P10_InLineInputSolenoid_Relay, P11_InLineInputSolenoid_Relay_ON_State);
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
      InLineInput_Start_Time = millis();
    }
    else
    {
      /* Do Nothing...*/
    }

    /* Update the Output pin state*/
    digitalWrite(P10_InLineInputSolenoid_Relay, P12_InLineInputSolenoid_Relay_OFF_State);
    /* Update current status*/
    InLineInput_Current_Status = Operatation_OFF;
  }
  else
  {
    /* Do Nothing...*/
  }
}


/* ************************************************************************
 * This function is get the status of the InLineInput request
 * *************************************************************************/
Sys_Operatation_Status GetStatus_InLineInput(void)
{
  Sys_Operatation_Status Return_Value;

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

  return (Return_Value);
}


/* ************************************************************************
 * This function is get the status of the High Presere Indication
 * *************************************************************************/
Sensor_InputStatus_Status GetStatus_HighPresere(void)
{
  Sensor_InputStatus_Status Return_Value = Sensor_Fault;
  uint16 HighPressure_ADC_Value;

  /* Read Current ADC value for High Presure */
  HighPressure_ADC_Value = Sys_Read_Processed_ADC_Value(P21_Analog_HighPresere);

  /* Check if its detected as ON*/
  if (Check_Tolerance((uint32)HighPressure_ADC_Value, (uint32)P22_Analog_HighPresere_ON_Volt, P26_Analog_HighPresere_Tolerance) == E_OK)
  {
     /* Set Status to ON*/
     Return_Value = Sensor_ON;
     /* Set Timer Value if previous state if OFF */
  }
}

/* ************************************************************************
 * This function is to Control Booster pump operatations
 * *************************************************************************/
void Control_BoostInput(Sys_Operatation_Status InputRequest)
{
  /* If input request is to ON*/
  if (InputRequest == Operatation_ON)
  {
    /* If previous status is OFF, then Update States changed Time*/
    if (Operatation_OFF == InputBoost_Current_Status)
    {
      /* Reset the Start time*/
      InputBoost_Start_Time = millis();
    }
    else
    {
      /* Do Nothing...*/
    }

    /* Update the Output pin state*/
    digitalWrite(P14_InputBoostMotor_Relay, P15_InputBoostMotor_Relay_ON_State);
    digitalWrite(P17_InputBoostSolenoid_Relay, P18_InputBoostSolenoid_Relay_ON_State);
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
      InputBoost_Start_Time = millis();
    }
    else
    {
      /* Do Nothing...*/
    }

    /* Update the Output pin state*/
    digitalWrite(P14_InputBoostMotor_Relay, P16_InputBoostMotor_Relay_OFF_State);
    digitalWrite(P17_InputBoostSolenoid_Relay, P19_InputBoostSolenoid_Relay_OFF_State);
    /* Update current status*/
    InputBoost_Current_Status = Operatation_OFF;
  }
  else
  {
    /* Do Nothing...*/
  }
}


/* ************************************************************************
 * This function is get the status of the Booster pump request
 * *************************************************************************/
Sys_Operatation_Status GetStatus_BoostInput(void)
{
  Sys_Operatation_Status Return_Value;

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

  return (Return_Value);
}



/* ************************************************************************
 * This function is to Control RO pump operatations
 * *************************************************************************/
void Control_ROInput(Sys_Operatation_Status InputRequest)
{

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
        InputRO_Start_Time = millis();
      }
      else
      {
        /* Do Nothing...*/
      }

      /* Update the Output pin state*/
      digitalWrite(P1B_RO_Motor_Relay, P1C_RO_Motor_Relay_ON_State);
      digitalWrite(P1E_RO_Solenoid_Relay, P1F_RO_Solenoid_Relay_ON_State);
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
        InputRO_Start_Time = millis();
      }
      else
      {
        /* Do Nothing...*/
      }

      /* Update the Output pin state*/
      digitalWrite(P1B_RO_Motor_Relay, P1D_RO_Motor_Relay_OFF_State);
      digitalWrite(P1E_RO_Solenoid_Relay, P20_RO_Solenoid_Relay_OFF_State);
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
}

/* ************************************************************************
 * This function is get the status of the RO pump request
 * *************************************************************************/
Sys_Operatation_Status GetStatus_ROInput(void)
{
  Sys_Operatation_Status Return_Value;

  /* Check the Time is over or not. OR if support is enabled, return current status, bypass timmer wait..*/
  if ((Get_Time_Elapse(InputRO_Current_Status) >= P35_RO_Delay_Time_In_ms) || (P1A_RO_Motor_Support != STD_ON))
  {
    /* Updare the status based on the current state.*/
    Return_Value = InputRO_Current_Status;
  }
  else /* Still change is in progress*/
  {
    /* Set status to in progress..*/
    Return_Value = Operatation_InProgres;
  }

  return (Return_Value);
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
 
/* Get the State of Overflow, If over flow detected then Switch off..*/



}






/* ************************************************************************
 * Function to Initialise all System related functions.
 * *************************************************************************/
void Init_MCU(void)
{
  /* WDG is already enabled.. So no change required.*/


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
