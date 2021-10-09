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

// Load Wi-Fi library
#include <WiFi.h>



/* Include required Html template header files*/
#include "Html_Templates_Debug_Trace_Page.h"


/*Define timeout time in milliseconds (example: 2000ms = 2s)*/
#define html_TimeOut_Clint 2000

/* Macro to allocate Bufferstream memory.*/
#define BufferStream_Max_Size  3000
/* Golbal bariable to store the Buffer stream data.*/
char BufferStream_ForDebugHTMLTrace[BufferStream_Max_Size + 10];

/*Set web server port number to 80 */
WiFiServer server(80);



/*******************************************************************************
 *  System Utility related Configuration Start
*******************************************************************************/

/*******************************************************************************
 *  Following are the Global variables for each Used Port Pins
 *  Global variables are used because later same can be updated via Configuration.
*******************************************************************************/

/*===========================================================================================*/
/*      Paramaters for UV Lamp Related                                                       */
/*===========================================================================================*/
/*Port Paramaters for UV Lamp control Repay. */
uint8 P01_UV_Lamp_Relay = 16;              /*  GPIO 16 @Port Pin 21 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint8 P02_UV_Lamp_Relay_ON_State = LOW;    /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
uint8 P03_UV_Lamp_Relay_OFF_State = HIGH;  /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/* Paramater to configure UV lamp Support*/
uint8 P2E_UV_Feedback_Support = UV_Feedback_Both;             /*  Indicate the configuration for the UV lamp feedback.. */

/* Paramater for LDR 1 , to detect UV light operatation*/
uint8  P04_UV_Lamp_Analog_LDR_1 = 35;                /*  Mapped to ADC 1_7, GPIO 35 @Port Pin 11 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint16 P05_UV_Lamp_Analog_LDR_1_ON_Volt = 1024;      /*  Represent the Voltage level representing the Active State / When UV is ON for LDR 1.*/
uint16 P07_UV_Lamp_Analog_LDR_1_OFF_Volt = 4024;     /*  Represent the Voltage level representing the Active State / When UV is OFF for LDR 1.*/
uint8  P09_UV_Lamp_Analog_LDR_1_Tolerance = 10;      /*  Persentage (%) of acceptable tolerance which can be considered.*/

/* Paramater for LDR 2 , to detect UV light operatation*/
uint8  P0A_UV_Lamp_Analog_LDR_2 = 34;                /*  Mapped to ADC 1_6, GPIO 34 @Port Pin 12 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint16 P0B_UV_Lamp_Analog_LDR_2_ON_Volt = 1024;      /*  Represent the Voltage level representing the Active State / When UV is ON for LDR 2.*/
uint16 P0D_UV_Lamp_Analog_LDR_2_OFF_Volt = 4024;     /*  Represent the Voltage level representing the Active State / When UV is OFF for LDR 2.*/
uint8  P0F_UV_Lamp_Analog_LDR_2_Tolerance = 10;      /*  Persentage (%) of acceptable tolerance which can be considered.*/

/* Paramater to Set UV lamp turn ON Delay.*/
uint16 P2F_UV_On_Delay_Time_In_ms = 5000;             /*  Indicate the configuration for the UV lamp turned ON time.. */


/*===========================================================================================*/
/*      Paramaters Related to Input flow                                                     */
/*===========================================================================================*/

/*Port Paramaters related in InLine Input Solinode Relay control */
uint8 P10_InLineInputSolenoid_Relay = 17;              /*  GPIO 16 @Port Pin 22 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint8 P11_InLineInputSolenoid_Relay_ON_State = LOW;    /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
uint8 P12_InLineInputSolenoid_Relay_OFF_State = HIGH;  /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/* Paramater represent time to Solenoid to take action / water start flow.*/
uint16 P31_InLineInput_Delay_Time_In_ms = 1000;        /*  Indicate the configuration for the time to Solenoid action get effective.. */


/*===========================================================================================*/
/*      Paramaters Related to Booster Pump                                                   */
/*===========================================================================================*/
/* Paramater to Specify Wheather Booster motor required to support.*/
uint8 P13_InputBoostMotor_Support = STD_ON;             /*  STD_ON ==> Support Booster motor, STD_OFF ==> Shall not Support Booster motor. */

/*Port Paramaters related to Input Booster Motor Relay control */
uint8 P14_InputBoostMotor_Relay = 18;              /*  GPIO 18 @Port Pin 24 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint8 P15_InputBoostMotor_Relay_ON_State = LOW;    /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
uint8 P16_InputBoostMotor_Relay_OFF_State = HIGH;  /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/*Port Paramaters related in input Solinode to control flow of Booster Motor */
uint8 P17_InputBoostSolenoid_Relay = 19;              /*  GPIO 19 @Port Pin 25 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint8 P18_InputBoostSolenoid_Relay_ON_State = LOW;    /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
uint8 P19_InputBoostSolenoid_Relay_OFF_State = HIGH;  /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */


/* Paramater represent time to Booster Motor & Solinode to take action / water start flow.*/
uint16 P33_InputBoost_Delay_Time_In_ms = 1000;        /*  Indicate the configuration for the time to Booster Motor & Solinode action get effective.. */




/*===========================================================================================*/
/*      Paramaters Related to RO motor Pump                                                  */
/*===========================================================================================*/

/* Paramater to Specify Wheather RO Pump required to support.*/
uint8 P1A_RO_Motor_Support = STD_ON;             /*  STD_ON ==> Support RO pump, STD_OFF ==> Shall not Support RO Pump. */

/*Port Paramaters related to RO Motor Relay control */
uint8 P1B_RO_Motor_Relay = 5;               /*  GPIO 5 @Port Pin 23 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint8 P1C_RO_Motor_Relay_ON_State = LOW;    /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
uint8 P1D_RO_Motor_Relay_OFF_State = HIGH;  /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/*Port Paramaters related to the Solinode to control flow of RO Motor */
uint8 P1E_RO_Solenoid_Relay = 5;               /*  GPIO 5 @Port Pin 23 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint8 P1F_RO_Solenoid_Relay_ON_State = LOW;    /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
uint8 P20_RO_Solenoid_Relay_OFF_State = HIGH;  /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/* Paramater represent time to RO Motor & Solinode to take action / water start flow.*/
uint16 P35_RO_Delay_Time_In_ms = 1000;         /*  Indicate the configuration for the time to RO Motor & Solinode action get effective.. */


/*===========================================================================================*/
/*      Other Analog Input Port  paramaters                                                  */
/*===========================================================================================*/

/* Paramater for High Presere Detection, to Avoid malfunctioning*/
uint8  P21_Analog_HighPresere = 32;                /*  Mapped to ADC 1_4, GPIO 32 @Port Pin 10 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint16 P22_Analog_HighPresere_ON_Volt = 1024;      /*  Represent the Voltage level representing the Active State / When UV is ON for LDR 1.*/
uint16 P24_Analog_HighPresere_OFF_Volt = 4024;     /*  Represent the Voltage level representing the Active State / When UV is OFF for LDR 1.*/
uint8  P26_Analog_HighPresere_Tolerance = 10;      /*  Persentage (%) of acceptable tolerance which can be considered.*/

/* Paramater represent High Pressure colling Time .
  ==> Once High pressure is detected SHall waite for colling time to leaps..*/
uint16 P37_HighPresere_CollingTime_In_ms = 5000;    /*  Indicate the High Pressure colling Time... */


/* Paramater for OverFlow Detection and to stop the filtering. */
uint8  P27_Analog_OverFlow = 33;                /*  Mapped to ADC 1_5, GPIO 33 @Port Pin 9 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint16 P28_Analog_OverFlow_ON_Volt = 1024;      /*  Represent the Voltage level representing the Active State / When UV is ON for LDR 2.*/
uint16 P2A_Analog_OverFlow_OFF_Volt = 4024;     /*  Represent the Voltage level representing the Active State / When UV is OFF for LDR 2.*/
uint8  P2C_Analog_OverFlow_Tolerance = 10;      /*  Persentage (%) of acceptable tolerance which can be considered.*/


/* Paramater represent OverFlow colling Time .
  ==> Once OverFlow is detected SHall waite for colling time to leaps..*/
uint16 P39_OverFlow_CollingTime_In_ms = 5000;    /*  Indicate the OverFlow colling Time... */


/*===========================================================================================*/
/*      Water flow meter Input Port  paramaters                                              */
/*===========================================================================================*/
uint8  P2D_WaterFlowSensor_Input = 4;         /* GPIO 4 @Port Pin 20 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */

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



static uint32 CounterOverflow;                 /* Variable to store the over flow count */
pcnt_isr_handle_t user_isr_handle = NULL;      /* User ISR handler for Interrupt */

/* Variable to store the init status of the Operatation.*/
Sensor_InputStatus_Status Current_Operatation_Status = Init_State;
Sensor_InputStatus_Status Previous_Operatation_Status = Init_State;

/*Macro function to get current state*/
#define Get_Current_Opp_State() Current_Operatation_Status

/* Macro function to update the state*/
#define Set_Current_Opp_State(Req_State) {Previous_Operatation_Status = Current_Operatation_Status; Current_Operatation_Status = Req_State;}

/* Macro to check wheather any state is changes.*/
#define Is_Opp_State_Changed() (Previous_Operatation_Status != Current_Operatation_Status)

/* Macro to Print the state Change.*/
#define Log_State_Changed(Change_Commend) {if(Is_Opp_State_Changed()){Debug_Trace(Change_Commend);}}

/* Macro indicating processing of current state completed at-lest once*/
#define State_Change_completed() (Previous_Operatation_Status = Current_Operatation_Status)


/*******************************************************************************
 *  Functions Forward decleratations deceleration
*******************************************************************************/


/*This function is to Control UV Lamp operatations*/
 static uint16 Sys_Read_Processed_ADC_Value(int GPIO_Port_pin);

 static void Control_UV_Lamp(Sys_UV_Lamp_Status InputRequest);
 static Sys_UV_Lamp_Feedback_Status Get_UV_Lamp_Feedback( void );
 static char * GetStatus_UV_Lamp_Sensor_Raw_Value(void);

 static void Control_InLineInput(Sys_Operatation_Status InputRequest);
 static Sys_Operatation_Status GetStatus_InLineInput(void);

 static void Control_BoostInput(Sys_Operatation_Status InputRequest);
 static Sys_Operatation_Status GetStatus_BoostInput(void);

 static void Control_ROInput(Sys_Operatation_Status InputRequest);
 static Sys_Operatation_Status GetStatus_ROInput(void);


 static Sensor_InputStatus_Status GetStatus_HighPresere(void);
 static uint16 GetStatus_HighPresere_Sensor_Raw_Value(void)

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
 * This function is get the High Presere Sensor Raw Value.
 * Value shall be process and converted in to string 
 * This interface shall provide its global variable, But its Not Mutely exclusive.
 * *************************************************************************/
char * GetStatus_UV_Lamp_Sensor_Raw_Value(void)
{
  static char Return_Buffer[70];
  uint16 UV_LDR_1_ADC_Value;
  uint16 UV_LDR_2_ADC_Value;

  /* Read ADC value of both LDR. Filtering of ADC is not considered for now... */
  UV_LDR_1_ADC_Value = Sys_Read_Processed_ADC_Value(P04_UV_Lamp_Analog_LDR_1);
  UV_LDR_2_ADC_Value = Sys_Read_Processed_ADC_Value(P0A_UV_Lamp_Analog_LDR_2);

  sprintf(Return_Buffer, "UV Sensor 1 = %d, UV Sensor 2 = %d ", UV_LDR_1_ADC_Value, UV_LDR_2_ADC_Value);

  return((char *)&Return_Buffer[0]);
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
 * This function is get the High Presere Sensor Raw Value.
 * *************************************************************************/
uint16 GetStatus_HighPresere_Sensor_Raw_Value(void)
{
  uint16 ADC_Raw_Value;


  /* Read Current ADC value for High Presere */
  ADC_Raw_Value = Sys_Read_Processed_ADC_Value(P21_Analog_HighPresere);

  /*Return Raw Value*/
   return(ADC_Raw_Value);

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


/* ************************************************************************
 * This function is get the OverFlow Sensor Raw Value.
 * *************************************************************************/
uint16 GetStatus_OverFlow_Sensor_Raw_Value(void)
{
  uint16 ADC_Raw_Value;


  /* Read Current ADC value for overflow */
  ADC_Raw_Value = Sys_Read_Processed_ADC_Value(P27_Analog_OverFlow);

  /*Return Raw Value*/
   return(ADC_Raw_Value);

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
  unsigned char Local_Init_status = false;
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

  /* Process State Indicating Initialization sequence is in progress. */
  case Init_State:
  {
     /*Print State change Message*/
     Log_State_Changed("Water Filer Operatation state changed to \"Init_State\" state.");
     
     /* Set Init status to false.*/
     Local_Init_status = false;

    /* DO complete Shut down, As a percolation.*/
    ShutDown_All();

    /*Wait to complete the shutdown.*/
    Delay_In_ms(CompleteSystem_ShutDown_Wait_Time);

/*---------------------------------------------------------------------------------
                       Start UV lamp Operatation checking.
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
        Debug_Trace("UV Lamp testing passed with flying colours. And for Reference %s ", GetStatus_UV_Lamp_Sensor_Raw_Value());
        
        /* Set Init status to true.*/
         Local_Init_status = true;
      }
      else /* Failed to detect the UV light*/
      {
        /* Get current raw value and print same ro debug trace.*/
        Debug_Trace("Failed to detect Wheather UV lamp is ON, could be because of faulty LDR or UV Lamp ss damaged, %s ", GetStatus_UV_Lamp_Sensor_Raw_Value());
        
        /* Indicate check failed.*/
         Local_Init_status = false;
      }
    }
    else /* Feed back failed to detect wheather Lamp is OFF, So wait until it get ready after logging the error*/
    {
      /* Get current raw value and print same ro debug trace.*/
     Debug_Trace("Failed to detect Wheather UV lamp is OFF, could be because of faulty LDR or if LDR Not possinied properly, %s ",GetStatus_UV_Lamp_Sensor_Raw_Value());

     /* Indicate check failed.*/
      Local_Init_status = false;
    }


/*---------------------------------------------------------------------------------
                       Start Float Sensor validatation  checking.
-----------------------------------------------------------------------------------*/
  /* Check wheather fault detected in flot sensor*/
  if(GetStatus_HighPresere() == Sensor_Fault)
  {
    /* Set status to check failed.*/
    Local_Init_status = false;
    /* Get current raw value and print same ro debug trace.*/
    Debug_Trace("Failed to detect the High presur Sensor, Could be because same is disconnected. For reference Sensor RAW value is  %d ",GetStatus_HighPresere_Sensor_Raw_Value());

  }


/*---------------------------------------------------------------------------------
                       Start High Presure Sensor validatation  checking.
-----------------------------------------------------------------------------------*/
  /* Check wheather fault detected in flot sensor*/
  if(GetStatus_OverFlow() == Sensor_Fault)
  {
    /* Set status to check failed.*/
    Local_Init_status = false;
    /* Get current raw value and print same ro debug trace.*/
    Debug_Trace("Failed to detect the Over flow Sensor, Could be because same is disconnected. For reference Sensor RAW value is  %d ",GetStatus_OverFlow_Sensor_Raw_Value());

  }

/*---------------------------------------------------------------------------------
                       Start Next state conclusion.
-----------------------------------------------------------------------------------*/
     /* If local Init status is OK, Then switch to New state.*/
     if(Local_Init_status == true)
     {



     }


    /* Indicate current sate is executed.*/
    State_Change_completed();
    break;
  }

  /* Indicate Tank is Not full and needs to On the Water flow.*/
  case Normal_Tank_Not_Full:
  {
    /*Print State change Message*/
    Log_State_Changed("Water Filer Operatation state changed to \"Normal_Tank_Not_Full\" state.");


    /* Indicate current sate is executed.*/
    State_Change_completed();
    break;
  }

  /* Indicate Indicate Tank full indicator not responding after considerable amound of water flows.*/
  case OverFlow_Tank_Not_Full:
  {
    /*Print State change Message*/
    Log_State_Changed("Water Filer Operatation state changed to \"OverFlow_Tank_Not_Full\" state.");


    /* Indicate current sate is executed.*/
    State_Change_completed();
    break;
  }

  /* Indicate Tank is full and Stop the flow.*/
  case Tank_Full:
  {
    /*Print State change Message*/
    Log_State_Changed("Water Filer Operatation state changed to \"Tank_Full\" state.");



    /* Indicate current sate is executed.*/
    State_Change_completed();
    break;
  }

  /* Indicate Some of the Sensor detected the Fault.*/
  case Tank_Sensor_Fault:
  {
    /*Print State change Message*/
    Log_State_Changed("Water Filer Operatation state changed to \"Tank_Sensor_Fault\" state.");



    /* Indicate current sate is executed.*/
    State_Change_completed();
    break;
  }

  /* Performe Emergency stop, Once inter in to this state It cannot come out. Needs power cycle.*/
  case Tank_Emergency_Stop:
  {
    /*Print State change Message*/
    Log_State_Changed("Water Filer Operatation state changed to \"Tank_Emergency_Stop\" state.");


    /* Indicate current sate is executed.*/
    State_Change_completed();
    break;
  }
  }



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
      Debug_Trace("Sensor fault detected in Normal Execution, SO Switching to state " Tank_Sensor_Fault " and Excute force shutdown.");
    }
  }
}

/* ************************************************************************
 * Function to log latest status or to Monitor the provess..
 * *************************************************************************/
void Web_Server_Processing(void)
{

  /* Variable to store the HTTP request*/
   String Client_Header_Request;
   String currentLine;

   /* Previous time for time out purpose.*/
   unsigned long previousTime = 0;

   char ClientCurrent_Char;

   /* Check if any  client has connected*/
   WiFiClient client = server.available();

   if (client)
   { /* If a new client connects,*/

      /* Read current time.*/
      previousTime = millis();

      //Debug_Trace("New Clint has been connected...");

      /* Clean the string to make a String to hold incoming data from the client*/
      currentLine = "";

      /*loop while the client's connected and No time out detected.*/
      while ((client.connected() ) &&  (Get_Time_Elapse(previousTime) <= html_TimeOut_Clint))
      {

         /* if there's bytes to read from the client, */
         if (client.available())
         {
            /* Read each available Byte form client*/
            ClientCurrent_Char = client.read();

            /* Stor into a string variable.*/
            Client_Header_Request += ClientCurrent_Char;

            /* if the byte is a newline character */
            if (ClientCurrent_Char == '\n')
            {
               /* if the current line is blank, you got two newline characters in a row.
             that's the end of the client HTTP request, so send a response:
          */
               if (currentLine.length() == 0)
               {
                  /* HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK) */
                  /* and a content-type so the client knows what's coming, then a blank line:*/
                  client.println("HTTP/1.1 200 OK");
                  client.println("Content-type:text/html");
                  client.println();

                  // Display the HTML web Header part
                  client.print(Html_Templates_Debug_Trace_Page_Header);

                  /* Get Queue string*/
                  Populate_BufferStream_FromQueue(BufferStream_ForDebugHTMLTrace, BufferStream_Max_Size);
                  /* Print HTML processed Page*/
                  client.print(BufferStream_ForDebugHTMLTrace);
 
                  /* Print Html Footer for the Debug trace*/
                  client.print(Html_Templates_Debug_Trace_Page_Footer);

                  // The HTTP response ends with another blank line
                  client.println();
                  // Break out of the while loop
                  break;
               }
               else
               { // if you got a newline, then clear currentLine
                  currentLine = "";
               }
            }
            else if (ClientCurrent_Char != '\r')
            {                                     // if you got anything else but a carriage return character,
               currentLine += ClientCurrent_Char; // add it to the end of the currentLine
            }
         }
      }
      // Clear the header variable
      Client_Header_Request = "";
      // Close the connection
      client.stop();
   }


}


/* ************************************************************************
 * Function to Init the Web server Required 
 * *************************************************************************/
void Web_Server_Init(void)
{
  /* change these values to match your network*/
char Current_ssid[100];
char Current_password[100];

  /*Read SSID from NVM.*/
  Nvm_Read_Each(NVM_ID_Value_WiFiSSIDName, (uint8*) Current_ssid );
  Nvm_Read_Each(NVM_ID_Value_WiFiSSIDPasword, (uint8*) Current_password );

   /* Try to connect to Wifi Access point based on the configuration.*/
   WiFi.begin(Current_ssid, Current_password);

  /* Waite until it get connect*/
   while (WiFi.status() != WL_CONNECTED)
   {
     /* Waite for 100ns befor reading status again.*/
     delay(100 / portTICK_PERIOD_MS);
   }

   /* If connected began the server.*/
   if (WiFi.status() == WL_CONNECTED)
   {
     /* Start the server.*/
     server.begin();

     Debug_Trace("WiFi get connected and IP address is %s", WiFi.localIP().toString().c_str());
   }
   /* If not able to connect to the Web server.*/
   else
   {
     Debug_Trace("Failed to connect to the configured WiFi %s", NVM_ID_Value_WiFiSSIDName);

   }

   /* Add additional logic for Time out and automatic switching between AP and WiFi station based on the availability.
    Reffer the Approach mentioned in https://techtutorialsx.com/2021/01/04/esp32-soft-ap-and-station-modes/
   */




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

 Debug_Trace("PCNT Init Completed....");
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





