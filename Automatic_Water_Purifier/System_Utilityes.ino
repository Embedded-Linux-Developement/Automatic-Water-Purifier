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



static uint32 CounterOverflow;                        /* Variable to store the over flow count */
pcnt_isr_handle_t user_isr_handle = NULL;      /* User ISR handler for Interrupt */




/*******************************************************************************
 *  Functions Forward decleratations deceleration
*******************************************************************************/


/*This function is to Control UV Lamp operatations*/
 static void Control_UV_Lamp(Sys_UV_Lamp_Status InputRequest);
 static Sys_UV_Lamp_Feedback_Status Get_UV_Lamp_Feedback( void );
 static void Control_InLineInput(Sys_Operatation_Status InputRequest);
 static Sys_Operatation_Status GetStatus_InLineInput(void);
 static uint16 Sys_Read_Processed_ADC_Value(int GPIO_Port_pin);
 static Sensor_InputStatus_Status GetStatus_HighPresere(void);
 static Sensor_InputStatus_Status GetStatus_OverFlow(void);



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
Sys_UV_Lamp_Feedback_Status Get_UV_Lamp_Feedback( void )
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
   if(Get_Time_Elapse(UV_Lamp_Start_Time) >= P2F_UV_On_Delay_Time_In_ms)
   {

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

  /* Exit from Critical Section. */
  portEXIT_CRITICAL(&UV_Lamp_Mux);


  /* Return final status*/
  return (ReturnStatus);
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
      InLineInput_Start_Time =Temp_Time;
    }
    else
    {
      /* Do Nothing...*/
    }

    /* Update the Output pin state*/
    Temp_PinStatus =  P12_InLineInputSolenoid_Relay_OFF_State;
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



  /* If input request is to ON*/
  if (InputRequest == Operatation_ON)
  {
    /* If previous status is OFF, then Update States changed Time*/
    if (Operatation_OFF == InputBoost_Current_Status)
    {
      /* Reset the Start time*/
      InputBoost_Start_Time = Temp_Time;
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
  if (Check_Tolerance((uint32)HighPressure_ADC_Value, (uint32)P22_Analog_HighPresere_ON_Volt, P26_Analog_HighPresere_Tolerance) == E_OK)
  {

     /* Set Status to ON*/
     Sensor_HighPressure_Status = Sensor_ON;
    /* Reset the time*/
    Sensor_HighPressure_Start_Time = Temp_Time;
  }
  /* Check wheather its status is OFF*/
  else if (Check_Tolerance((uint32)HighPressure_ADC_Value, (uint32)P24_Analog_HighPresere_OFF_Volt, P26_Analog_HighPresere_Tolerance) == E_OK)
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

   return(Sensor_HighPressure_Status);

}


/* ************************************************************************
 * This function is get the status of the OverFlow Indication
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
  if (Check_Tolerance((uint32)OverFlow_ADC_Value, (uint32)P28_Analog_OverFlow_ON_Volt, P2C_Analog_OverFlow_Tolerance) == E_OK)
  {

     /* Set Status to ON*/
     Sensor_OverFlow_Status = Sensor_ON;
    /* Reset the time*/
    Sensor_OverFlow_Start_Time = Temp_Time;
  }
  /* Check wheather its status is OFF*/
  else if (Check_Tolerance((uint32)OverFlow_ADC_Value, (uint32)P2A_Analog_OverFlow_OFF_Volt, P2C_Analog_OverFlow_Tolerance) == E_OK)
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

   return(Sensor_OverFlow_Status);

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
 * Function to log latest status or to Monitor the provess..
 * *************************************************************************/
void Monitor_ControlSystem(void)
{
  /* Variable to store the current water flow*/
  static double Previous_Water_flow_Reading = 0;
  double Current_Water_flow_Reading;


/* Read water flow reading and print..*/
   Current_Water_flow_Reading = Get_Current_WaterFlowedInL();
 /* Check if both are Not same, then Log new reading*/
  if(Previous_Water_flow_Reading != Current_Water_flow_Reading)
  {
      Debug_Trace("Total Water Flowed = %f",Current_Water_flow_Reading);
      /* Update Previous Data*/
      Previous_Water_flow_Reading = Current_Water_flow_Reading;
  }
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

void Init_PulseCounter (void)
{
  pcnt_config_t pcntFreqConfig = { };                        // Declear variable for cinfig
  pcntFreqConfig.pulse_gpio_num = PCNT_INPUT_SIG_IO;         // Set the port ping using for counting
  pcntFreqConfig.pos_mode = PCNT_COUNT_INC;                  // set Counter mode: Increase counter value
  pcntFreqConfig.counter_h_lim = PCNT_Overflow_LIM_VAL;      // Set Over flow Interupt / event value
  pcntFreqConfig.unit = PCNT_UNIT_Used;                      //  Set Pulsos unit to ne used
  pcntFreqConfig.channel = PCNT_CHANNEL_0;                   //  select PCNT channel 0
  pcnt_unit_config(&pcntFreqConfig);                         // Configure PCNT.

  pcnt_counter_pause(PCNT_UNIT_Used);                        // Pause PCNT counter such that we can set event.
  pcnt_counter_clear(PCNT_UNIT_Used);                        // Clear PCNT counter to avoid ant mis counting.

  pcnt_event_enable(PCNT_UNIT_Used, PCNT_EVT_H_LIM);         // Enable event for when PCNT watch point event: Maximum counter value
  pcnt_isr_register(CounterOverflow_ISR, NULL, 0, &user_isr_handle);  // Set call back function for the Event.
  pcnt_intr_enable(PCNT_UNIT_Used);                          // Enable PCNT

  pcnt_counter_resume(PCNT_UNIT_Used);                       // Re-started PCNT.

 Serial.println("PCNT Init Completed....");
}


/* *********************************************************************************
   Function to clean the Counter and its variables......
*************************************************************************************/
void Clean_Water_Flow_Counters(void)                                       
{

  pcnt_counter_pause(PCNT_UNIT_Used);                      // Pause PCNT counter such that we can set event.
  CounterOverflow = 0;                                     // Clear global Over flow counter.
  pcnt_counter_clear(PCNT_UNIT_Used);                      // Clean Pulse Counter...
  pcnt_counter_resume(PCNT_UNIT_Used);                     // Re-started PCNT.

}



/* *********************************************************************************
   Function to get total water flowed from last clear / restart in Liters......
*************************************************************************************/
double Get_Current_WaterFlowedInL(void)                                       
{
   double Return_Water_Flowed_InL;
   int16_t Current_Counter_Value;
   uint32 Calib_Value;

   /* Consider Over-flowed values*/
   Return_Water_Flowed_InL = CounterOverflow * PCNT_Overflow_LIM_VAL;

   /*Read the counter Value */
   pcnt_get_counter_value(PCNT_UNIT_Used, &Current_Counter_Value);

  /* Add Current Counter Value*/
  Return_Water_Flowed_InL += Current_Counter_Value;

   /* Get NVM Calib Value*/
   Calib_Value = Nvm_Read_Each(NVM_ID_Calibration_FlowMeaterFactor);

   /* Check is value is Zero, If So applay safe default value.*/
   Calib_Value  = ((Calib_Value == 0)?WaterFlow_Default_Calib_VAL:Calib_Value);

  /* Convert In to Liters*/
  /* Consider the Value in NVM paramater NVM_ID_Calibration_FlowMeaterFactor = Number of counter tick for 1 Letter of water.*/
  Return_Water_Flowed_InL = Return_Water_Flowed_InL / Calib_Value;

  return (Return_Water_Flowed_InL);
}

