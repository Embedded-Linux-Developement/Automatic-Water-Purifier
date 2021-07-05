
#ifndef Automatic_Water_Purifier_H
#define Automatic_Water_Purifier_H

#include "MyStdTypes.h"


/*******************************************************************************
 *  Configuration Start
*******************************************************************************/
/* Set required Serial broad-rate.*/
#define Serial_BR_Rate 115200 /*serial communication at 9600 bits per second*/

/* Macro to enable or disable debug support,
     STD_ON   => Will print debug info over serial terminal.
     STD_OFF  => Shall Not print debug info over serial terminal.
  */
#define Enable_Debug_Support STD_ON

/*Reserve Max debug variable sizes as 1KB.*/
#define Max_Debug_Buffer 1024
#define Max_Debug_Time_Buffer 128

/* Following are the Configurations related to the Networking.*/
/* Default name for recovery Access Point.*/ 
/* If configured WiFi are not available then shall Automaticaly switch to below mentioned AP. 
   And after login into this access point you can configure new WiFi Pasword if needed.
   User name and pasword of AP is not configuriable because its a recovery mechanism.
   */
#define AP_Name "Automatic_Water_Purifier"
#define AP_Pasword "IamPayyampallil"



/*******************************************************************************
 *  Following are the MACROS for each Used Port Pins
*******************************************************************************/

#define DO_Buzzer 13
#define R_Speed_2 10 /* Represent the Relay @ Bottom Left, Relay for Speed 2 (Med)  White Wire*/
#define R_Speed_3 11 /* Represent the Relay @ Bottom Right, Relay for Speed 3 (High) Black Wire*/
#define R_Bulb 3     /* Represent the Relay @ Top Left,  Relay for Bulb*/
#define R_Speed_1 4  /* Represent the Relay @ Top Right, Relay for Speed 1 (Low)  Red Wire*/

#define But_Stop 9    /* Button connected to black wire. For Stop Fan*/
#define But_Speed_1 5 /* Button connected to Yellow wire. For Speed 1 Fan*/
#define But_Speed_2 6 /* Button connected to Orange wire. For Speed 2 Fan*/
#define But_Speed_3 7 /* Button connected to Red wire. For Speed 3 Fan*/

#define But_Bukb 8 /* Button connected to Brown wire. For ON /OFF bulb*/




/*******************************************************************************
 *  Following are the configuration for EEPROM
*******************************************************************************/
/* This Macro represent the maximum available, For ESP32, Its 512Bytes */
#define Max_Available_EEPROM 512
#define Total_NVM_Paramaters 14   /* Represent Max NVM paramater, Please make sure shall same as NVM_ID_Max*/

const NVM_Param_Config_Table_Type NVM_Param_Config_Table[Total_NVM_Paramaters] = {

   /*
     How to Update:- 
       1. Each Paramater shall have a 2 byte CRC attached for error detection.
       2. Address shall be calculated by itself at the time of Readingand Writting, Its to avoid the possible mistack.
       3. Please make sure total sizes shall ot exceed "Max_Available_EEPROM" value, if so shall give error and stop operatations.
   
   */

/* NVMParam_ID                                 , NVMParam_Length ,  NVMParam_Type   ,  &NVMParam_Default     */
{NVM_ID_Value_WiFiSSIDName                     ,        75U       ,  NVM_StringType  ,     CharNULLPtr                },   
{NVM_ID_Value_WiFiSSIDPasword                  ,        75U       ,  NVM_StringType  ,     CharNULLPtr                },   
{NVM_ID_Value_WiFiStsticIP                     ,        04U       ,  NVM_VoidType    ,     CharNULLPtr                },   
{NVM_ID_Value_WiFiServerName                   ,        75U       ,  NVM_StringType  ,     CharNULLPtr                },   

/* For Calibratation */
{NVM_ID_Calibration_FlowMeaterFactor           ,        04U       ,  NVM_VoidType    ,     CharNULLPtr                },  
{NVM_ID_Calibration_LowFlowRate                ,        04U       ,  NVM_VoidType    ,     CharNULLPtr                },  
{NVM_ID_Calibration_HighFlowRate               ,        04U       ,  NVM_VoidType    ,     CharNULLPtr                },  
{NVM_ID_Calibration_HighPresureCollingTime     ,        04U       ,  NVM_VoidType    ,     CharNULLPtr                },  
{NVM_ID_Calibration_WaterTankOverflowCapacity  ,        04U       ,  NVM_VoidType    ,     CharNULLPtr                },  

/*For settings*/
{NVM_ID_Seting_WaterTankOverflowAction         ,        01U       ,  NVM_VoidType    ,     CharNULLPtr                },  
{NVM_ID_Seting_HighPresureAction               ,        01U       ,  NVM_VoidType    ,     CharNULLPtr                },  
{NVM_ID_Seting_OperatationMode                 ,        01U       ,  NVM_VoidType    ,     CharNULLPtr                },  
{NVM_ID_Seting_LowFlowRateWarningAction        ,        01U       ,  NVM_VoidType    ,     CharNULLPtr                },  
{NVM_ID_Seting_HighFlowRateWarningAction       ,        01U       ,  NVM_VoidType    ,     CharNULLPtr                },  

};

/*-----------------------------------------------------------------------------
 *  Configuration END
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





#endif /* End of  Automatic_Water_Purifier_H */
