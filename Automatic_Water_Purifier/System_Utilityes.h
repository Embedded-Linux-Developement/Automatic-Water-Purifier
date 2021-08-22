
#ifndef System_Utilityes_H
#define System_Utilityes_H

#include "MyStdTypes.h"
#include "driver/pcnt.h" 

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
 *  Program Specific data types.
*******************************************************************************/
/*Following Enumerators are to represent the UV lamp status*/
enum  Sys_UV_Lamp_Status{
  UV_Lamp_ON     = 0x5A, /* Indicate Lamp is ON. */
  UV_Lamp_OFF    = 0x0F, /* Indicate Lamp is OFF.*/
  UV_Lamp_UnInit = 0xA9  /* Indicate Lamp is Uninit.*/
};

/*Following Enumerators are to represent the UV lamp status*/
enum  Sys_UV_Lamp_Feedback_Status{
  UV_Lamp_Feedback_ON        = 0x98,  /* Indicate Lamp is ON Via feedback. */
  UV_Lamp_Feedback_OFF       = 0x89,  /* Indicate Lamp is OFF Via feedback.*/
  UV_Lamp_Feedback_InProgres = 0x5A,  /* Indicate Lamp is Starting is in progress.*/
  UV_Lamp_Feedback_Fault     = 0xE0   /* Indicate Lamp Fault detected Via feedback.*/
};


/* Enum to define Operatation Status*/
enum  Sys_Operatation_Status{
  Operatation_ON        = 0x5A, /* Indicate request is to ON. */
  Operatation_OFF       = 0x0F, /* Indicate request is to OFF.*/
  Operatation_InProgres = 0xA9  /* Indicate request is to In-Progres.*/
};

/* Enum to define Operatation Status*/
enum  Sensor_InputStatus_Status{
  Sensor_ON     = 0x44, /* Indicate Sensor is ON. */
  Sensor_OFF    = 0x48, /* Indicate Sensor is OFF.*/
  Sensor_Fault  = 0x94  /* Indicate Sensor is Fault.*/
};


/*******************************************************************************
 *  Macro Functions
*******************************************************************************/

#define PCNT_UNIT_Used             PCNT_UNIT_0                  /* Select the Pulse Count 0  as the unit..*/
#define PCNT_Overflow_LIM_VAL       10000                       /* Set the max limit to trigger the interrupt*/
#define WaterFlow_Default_Calib_VAL 1000                        /* Paramater represent the default Calib value to be used if configured value is wrong.*/
#define PCNT_INPUT_SIG_IO          P2D_WaterFlowSensor_Input                           /* Pulse Input selected as GPIO 4 */


/*******************************************************************************
 *  Public Function Definations Functions
*******************************************************************************/

extern void Init_MCU(void);
extern void Init_GPT_ICU(void);
extern void Perform_Reset(void);
extern void Monitor_ControlSystem(void);
extern void Init_PulseCounter (void);
extern void Clean_Water_Flow_Counters(void);
extern double Get_Current_WaterFlowedInL(void);


#endif /* End of  System_Utilityes_H */
