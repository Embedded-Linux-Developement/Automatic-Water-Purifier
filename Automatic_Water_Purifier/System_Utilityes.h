
#ifndef System_Utilityes_H
#define System_Utilityes_H

#include "MyStdTypes.h"


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
uint8 Pxx_UV_Lamp_Relay = 16;              /*  GPIO 16 @Port Pin 21 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint8 Pxx_UV_Lamp_Relay_ON_State = LOW;    /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
uint8 Pxx_UV_Lamp_Relay_OFF_State = HIGH;  /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/* Paramater for LDR 1 , to detect UV light operatation*/
uint8  Pxx_UV_Lamp_Analog_LDR_1 = 35;                /*  Mapped to ADC 1_7, GPIO 35 @Port Pin 11 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint16 Pxx_UV_Lamp_Analog_LDR_1_ON_Volt = 1024;      /*  Represent the Voltage level representing the Active State / When UV is ON for LDR 1.*/
uint16 Pxx_UV_Lamp_Analog_LDR_1_OFF_Volt = 4024;     /*  Represent the Voltage level representing the Active State / When UV is OFF for LDR 1.*/
uint8  Pxx_UV_Lamp_Analog_LDR_1_Tolerance = 10;      /*  Persentage (%) of acceptable tolerance which can be considered.*/

/* Paramater for LDR 2 , to detect UV light operatation*/
uint8  Pxx_UV_Lamp_Analog_LDR_2 = 34;                /*  Mapped to ADC 1_6, GPIO 34 @Port Pin 12 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint16 Pxx_UV_Lamp_Analog_LDR_2_ON_Volt = 1024;      /*  Represent the Voltage level representing the Active State / When UV is ON for LDR 2.*/
uint16 Pxx_UV_Lamp_Analog_LDR_2_OFF_Volt = 4024;     /*  Represent the Voltage level representing the Active State / When UV is OFF for LDR 2.*/
uint8  Pxx_UV_Lamp_Analog_LDR_2_Tolerance = 10;      /*  Persentage (%) of acceptable tolerance which can be considered.*/

/*===========================================================================================*/
/*      Paramaters Related to Input flow                                                     */
/*===========================================================================================*/

/*Port Paramaters related in InLine Input Solinode Relay control */
uint8 Pxx_InLineInputSolenoid_Relay = 17;              /*  GPIO 16 @Port Pin 22 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint8 Pxx_InLineInputSolenoid_Relay_ON_State = LOW;    /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
uint8 Pxx_InLineInputSolenoid_Relay_OFF_State = HIGH;  /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/*===========================================================================================*/
/*      Paramaters Related to Booster Pump                                                   */
/*===========================================================================================*/
/* Paramater to Specify Wheather Booster motor required to support.*/
uint8 Pxx_InputBoostMotor_Support = STD_ON;             /*  STD_ON ==> Support Booster motor, STD_OFF ==> Shall not Support Booster motor. */

/*Port Paramaters related to Input Booster Motor Relay control */
uint8 Pxx_InputBoostMotor_Relay = 18;              /*  GPIO 18 @Port Pin 24 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint8 Pxx_InputBoostMotor_Relay_ON_State = LOW;    /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
uint8 Pxx_InputBoostMotor_Relay_OFF_State = HIGH;  /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/*Port Paramaters related in input Solinode to control flow of Booster Motor */
uint8 Pxx_InputBoostSolenoid_Relay = 19;              /*  GPIO 19 @Port Pin 25 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint8 Pxx_InputBoostSolenoid_Relay_ON_State = LOW;    /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
uint8 Pxx_InputBoostSolenoid_Relay_OFF_State = HIGH;  /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/*===========================================================================================*/
/*      Paramaters Related to RO motor Pump                                                  */
/*===========================================================================================*/

/* Paramater to Specify Wheather RO Pump required to support.*/
uint8 Pxx_InputBoostMotor_Support = STD_ON;             /*  STD_ON ==> Support RO pump, STD_OFF ==> Shall not Support RO Pump. */

/*Port Paramaters related to RO Motor Relay control */
uint8 Pxx_RO_Motor_Relay = 5;               /*  GPIO 5 @Port Pin 23 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint8 Pxx_RO_Motor_Relay_ON_State = LOW;    /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
uint8 Pxx_RO_Motor_Relay_OFF_State = HIGH;  /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */

/*Port Paramaters related to the Solinode to control flow of RO Motor */
uint8 Pxx_RO_Solenoid_Relay = 5;               /*  GPIO 5 @Port Pin 23 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint8 Pxx_RO_Solenoid_Relay_ON_State = LOW;    /*  Indicate on which Port pin State UV lamp relay make Lamp ON */
uint8 Pxx_RO_Solenoid_Relay_OFF_State = HIGH;  /*  Indicate on which Port pin State UV lamp relay make Lamp OFF  */


/*===========================================================================================*/
/*      Other Analog Input Port  paramaters                                                  */
/*===========================================================================================*/

/* Paramater for High Presere Detection, to Avoid malfunctioning*/
uint8  Pxx_Analog_HighPresere = 32;                /*  Mapped to ADC 1_4, GPIO 32 @Port Pin 10 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint16 Pxx_Analog_HighPresere_ON_Volt = 1024;      /*  Represent the Voltage level representing the Active State / When UV is ON for LDR 1.*/
uint16 Pxx_Analog_HighPresere_OFF_Volt = 4024;     /*  Represent the Voltage level representing the Active State / When UV is OFF for LDR 1.*/
uint8  Pxx_Analog_HighPresere_Tolerance = 10;      /*  Persentage (%) of acceptable tolerance which can be considered.*/

/* Paramater for OverFlow Detection and to stop the filtering. */
uint8  Pxx_Analog_LDR_2 = 34;                /*  Mapped to ADC 1_6, GPIO 34 @Port Pin 12 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */
uint16 Pxx_Analog_LDR_2_ON_Volt = 1024;      /*  Represent the Voltage level representing the Active State / When UV is ON for LDR 2.*/
uint16 Pxx_Analog_LDR_2_OFF_Volt = 4024;     /*  Represent the Voltage level representing the Active State / When UV is OFF for LDR 2.*/
uint8  Pxx_Analog_LDR_2_Tolerance = 10;      /*  Persentage (%) of acceptable tolerance which can be considered.*/


/*===========================================================================================*/
/*      Water flow meter Input Port  paramaters                                              */
/*===========================================================================================*/
uint8  Pxx_WaterFlowSensor_Input = 4;         /* GPIO 4 @Port Pin 20 ( Based on the Pin layout in ESP32_Used_Pin_Layout.jpg) */

/*-----------------------------------------------------------------------------
 *  System Utility related Configuration END
-------------------------------------------------------------------------------*/

/*******************************************************************************
 *  Program Specific Macros.
*******************************************************************************/


/*******************************************************************************
 *  Macro Functions
*******************************************************************************/



/*******************************************************************************
 *  Public Function Definations Functions
*******************************************************************************/

extern void Init_MCU(void);
extern void Init_GPT_ICU(void);
extern void Perform_Reset(void);



#endif /* End of  System_Utilityes_H */
