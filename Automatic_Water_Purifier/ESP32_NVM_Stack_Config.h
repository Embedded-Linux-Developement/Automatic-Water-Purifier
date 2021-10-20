
#ifndef ESP32_NVM_Stack_Config_H
#define ESP32_NVM_Stack_Config_H

#include "MyStdTypes.h"
#include "ESP32_NVM_Stack.h"

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
 *  NVM Configuration Start
*******************************************************************************/
/* This Macro represent the maximum available, For ESP32, Its 512Bytes */
#define Max_Available_EEPROM 512
#define Total_NVM_Paramaters 22   /* Represent Max NVM paramater, Please make sure shall same as NVM_ID_Max*/
#define NVM_CRC_Polynomial   0x2869 /* Polynomial for calculate the CRC*/

/* 
 * This paramater is to indicate wheather all NVM mirror values to be printed. 
 *  Recommenced to be STD_OFF on production, As it can compermise the Security Informatations in NVM.
*/
#define Debug_Print_All_NVM_Read_All_Value STD_OFF  
/* 
 * This paramater is to perform the destractive Test, Will write New Data and read it back to verify.
 *   Its always Recomented to STD_OFF, Because will corrept the NVM data on every restart, Only meant for testing NVM stack.. 
 *   Prolonged use can reduce the longed cycle of the NVM.
*/
#define NVM_Stack_Distractive_Test STD_OFF

/* 
* This paramater is to perform the check for Default value.
*     1. Its always Recomented to STD_OFF, Because Once configured default value Check shall be always fails.
*     2. Its just considered to validate default value update after any code update, As validatation.
*/
#define NVM_Stack_Default_Test STD_OFF   

/* 
 * This paramater is to Validate the Signature, 
 *   1. By writting and reading a specific data at start and end Address of the NVM memort block.
 *   2. For the same Will have 2 Reserved NVM paramater one at start and one at End.
 *   3. It shall use Update interface, which will not write to EEPROM Address data is same. 
 *   4. And we will keep same data, else will affect the endurance of the Prodect.
 *   4. Highely recommend to keep ot as STD_ON, because will help to find fault in NVM.
*/
#define NVM_Stack_Signature_Test STD_ON   

/*
 * This test is to just read the Variable and prient same to show its value.
 * 1. This Test shall just read the NVM paramater using the interface and Print to show the value.
 * 2. Recommenced to be STD_OFF on production, As it can compermise the Security Informatations in NVM.
 */
#define NVM_Stack_Read_And_Display_Test STD_OFF


/* 
* This paramater is just to dissable the writting operatation. 
*   1. This option is to protect NVM from unwanted write during development.
*   1. Its always Recomented to STD_ON, In final prodect, else NVM write will not happen.
*   2. IN Development phase you can keep is as STD_OFF, IN this case Will not write to EEPROM, 
*       Only NVM mirror data shall be updated.
*/
#define NVM_Stack_Dissable_NVM_Write STD_OFF



/*******************************************************************************
 *  Default Data for each NVM paramater
*******************************************************************************/

/* Following are the default Value for each NVM paramaters.*/
const uint8 NVM_Default_Value_WiFiSSIDName[50]     = "Test";                      /*String to hold the default value for the NVM_ID_Value_WiFiSSIDName NVM paramater.*/
const uint8 NVM_Default_Value_WiFiSSIDPasword[25]  = "Test";                       /*String to hold the default value for the NVM_ID_Value_WiFiSSIDPasword NVM paramater.*/

const uint8 NVM_Default_Value_Soft_AP_SSIDName[50] = "WaterPurifier";         /*String to hold the default value for the NVM_ID_Value_Soft_AP_SSIDName NVM paramater.*/
const uint8 NVM_Default_Value_Soft_AP_Pasword[25]  = "686517PWF2021";                       /*String to hold the default value for the NVM_ID_Value_Soft_AP_Pasword NVM paramater.*/

const uint8 NVM_Default_Value_WiFiStsticIP[4]      = {198,168,0,180};               /*Array to hold the default value for the NVM_ID_Value_WiFiStsticIP NVM paramater.*/
const uint8 NVM_Default_Value_WiFiServerName[75]   = "Automatic Water Purifier";   /*String to hold the default value for the NVM_ID_Value_WiFiServerName NVM paramater.*/
const uint8 NVM_Default_Value_AdminPasword[30]     = "Admin";                      /*String to hold the default value for the NVM_ID_Value_AdminPasword NVM paramater.*/

      /* Byte arrangement after converting to uint32 Byte 0 - 3    {LSB0,LSB1,LSB2,MSB3}             */
const uint8 NVM_Default_Calibration_FlowMeaterFactor[4]          = {0x69,0x00,0x00,0x00};  /*  105Tick = 1L    = 0x0069 Array to hold the default value for the NVM_ID_Calibration_FlowMeaterFactor NVM paramater.*/
const uint8 NVM_Default_Calibration_LowFlowRate[4]               = {0xF4,0x01,0x00,0x00};  /*  500mLpM = 0.5LpM= 0x01F4 Array to hold the default value for the NVM_ID_Calibration_LowFlowRate NVM paramater.*/
const uint8 NVM_Default_Calibration_HighFlowRate[4]              = {0xA0,0x0F,0x00,0x00};  /* 4000mLpM = 4LpM  = 0x0FA0 Array to hold the default value for the NVM_ID_Calibration_HighFlowRate NVM paramater.*/
const uint8 NVM_Default_Calibration_HighPresureCollingTime[4]    = {0x10,0x27,0x00,0x00};  /* 10000ms  = 10S   = 0x2710 Array to hold the default value for the NVM_ID_Calibration_HighPresureCollingTime NVM paramater.*/
const uint8 NVM_Default_Calibration_FlowRateWarningCollingTime[4]= {0x88,0x13,0x00,0x00};  /*  5000ms  =  5S   = 0x1388 Array to hold the default value for the NVM_ID_Calibration_FlowRateWarningCollingTime NVM paramater.*/
const uint8 NVM_Default_Calibration_WaterTankOverflowCapacity[4] = {0x20,0x4E,0x00,0x00};  /* 20000mL  = 20L   = 0x4E20 Array to hold the default value for the NVM_ID_Calibration_WaterTankOverflowCapacity NVM paramater.*/
const uint8 NVM_Default_Calibration_AutoModeBoosterStartTime[4]  = {0x20,0x4E,0x00,0x00};  /* 20000ms  = 20S   = 0x4E20 Array to hold the default value for the NVM_ID_Calibration_AutoModeBoosterStartTime NVM paramater.*/
const uint8 NVM_Default_Calibration_MaxDryRunTimeTime[4]         = {0x60,0xEA,0x00,0x00};  /* 60000ms  = 60S   = 0xEA60 Array to hold the default value for the NVM_ID_Calibration_MaxDryRunTimeTime NVM paramater.*/


const uint8 NVM_Default_Seting_WaterTankOverflowAction    = Recovery_On_PowerOn;       /*Variable to hold the default value for the NVM_ID_Seting_WaterTankOverflowAction NVM paramater.*/
const uint8 NVM_Default_Seting_HighPresureAction          = Recovery_Time_Bound;       /*Variable to hold the default value for the NVM_ID_Seting_HighPresureAction NVM paramater.*/
const uint8 NVM_Default_Seting_LowFlowRateWarningAction   = Recovery_Time_Bound;       /*Variable to hold the default value for the NVM_ID_Seting_LowFlowRateWarningAction NVM paramater.*/
const uint8 NVM_Default_Seting_HighFlowRateWarningAction  = Recovery_Time_Bound;       /*Variable to hold the default value for the NVM_ID_Seting_HighFlowRateWarningAction NVM paramater.*/
const uint8 NVM_Default_Seting_OperatationMode            = WF_Mode_Auto;              /*Variable to hold the default value for the NVM_ID_Seting_OperatationMode NVM paramater.*/

/* Below Variables and Macros are for setting the NVM Signature Value*/
#define NVM_Start_Signature_Sizes  4U /* Define the sizes of Start Signature.*/
#define NVM_Start_Signature_Data   "SSV"  /*String to be stored in Start Signature.*/
#define NVM_Start_Signature_DefaultData   "NOK"  /*Default String to be stored in Start Signature.*/
const uint8 NVM_Default_Start_Signature_Data[NVM_Start_Signature_Sizes] = NVM_Start_Signature_DefaultData;  /*String to hold the default value for the NVM_Start_Signature NVM paramater.*/

#define NVM_End_Signature_Sizes  4U /* Define the sizes of End Signature.*/
#define NVM_End_Signature_Data   0x5655AAFFU /*String to be stored in End Signature.*/
#define NVM_End_Signature_DefaultData   0x00000000U  /*Default String to be stored in Start Signature.*/
const uint8 NVM_Default_End_Signature_Data[NVM_End_Signature_Sizes] = {0x00,0x00,0x00,0x00};  /*String to hold the default value for the NVM_End_Signature NVM paramater.*/




/*******************************************************************************
 *  NVM paramater Configuration, 
 *  Please add new NVM ID on "NVMParam_ID_Enum" in ESP32_NVM_Stack.h file
*******************************************************************************/

const NVM_Param_Config_Table_Type NVM_Param_Config_Table[Total_NVM_Paramaters] = {

   /*
     How to Update:- 
       1. Each Paramater shall have a 2 (Based on the configuration) byte CRC attached for error detection.
       2. Address shall be calculated by itself at the time of Readingand Writting, Its to avoid the possible mistack.
       3. Please make sure total sizes shall ot exceed "Max_Available_EEPROM" value, if so shall give error and stop operatations.
   
   */

{NVM_Start_Signature , NVM_Start_Signature_Sizes,  NVM_StringType  ,  NVM_Default_Start_Signature_Data },  
/*========================================== Please add New NVM paramater below this Point Only.===================================================*/
/* NVMParam_ID                                 , NVMParam_Length  ,  NVMParam_Type   ,            &NVMParam_Default         */

{NVM_ID_Value_WiFiSSIDName                     ,        50U       ,  NVM_StringType  ,     NVM_Default_Value_WiFiSSIDName                          },   
{NVM_ID_Value_WiFiSSIDPasword                  ,        25U       ,  NVM_StringType  ,     NVM_Default_Value_WiFiSSIDPasword                       },  

{NVM_ID_Value_Soft_AP_SSIDName                 ,        50U       ,  NVM_StringType  ,     NVM_Default_Value_Soft_AP_SSIDName                      },   
{NVM_ID_Value_Soft_AP_Pasword                  ,        25U       ,  NVM_StringType  ,     NVM_Default_Value_Soft_AP_Pasword                       },   

{NVM_ID_Value_WiFiStsticIP                     ,        04U       ,  NVM_VoidType    ,     NVM_Default_Value_WiFiStsticIP                          },   
{NVM_ID_Value_WiFiServerName                   ,        75U       ,  NVM_StringType  ,     NVM_Default_Value_WiFiServerName                        },   
{NVM_ID_Value_AdminPasword                     ,        30U       ,  NVM_StringType  ,     NVM_Default_Value_AdminPasword                          },   
                             
/* For Calibratation */                             
{NVM_ID_Calibration_FlowMeaterFactor           ,        04U       ,  NVM_VoidType    ,     NVM_Default_Calibration_FlowMeaterFactor                },  
{NVM_ID_Calibration_LowFlowRate                ,        04U       ,  NVM_VoidType    ,     NVM_Default_Calibration_LowFlowRate                     },  
{NVM_ID_Calibration_HighFlowRate               ,        04U       ,  NVM_VoidType    ,     NVM_Default_Calibration_HighFlowRate                    },  
{NVM_ID_Calibration_HighPresureCollingTime     ,        04U       ,  NVM_VoidType    ,     NVM_Default_Calibration_HighPresureCollingTime          },  
{NVM_ID_Calibration_FlowRateWarningCollingTime ,        04U       ,  NVM_VoidType    ,     NVM_Default_Calibration_FlowRateWarningCollingTime      },  
{NVM_ID_Calibration_WaterTankOverflowCapacity  ,        04U       ,  NVM_VoidType    ,     NVM_Default_Calibration_WaterTankOverflowCapacity       },  
{NVM_ID_Calibration_AutoModeBoosterStartTime   ,        04U       ,  NVM_VoidType    ,     NVM_Default_Calibration_AutoModeBoosterStartTime        },  
{NVM_ID_Calibration_MaxDryRunTimeTime          ,        04U       ,  NVM_VoidType    ,     NVM_Default_Calibration_MaxDryRunTimeTime               },  
                             
/*For settings*/                             
{NVM_ID_Seting_WaterTankOverflowAction         ,        01U       ,  NVM_VoidType    ,     &NVM_Default_Seting_WaterTankOverflowAction             },  
{NVM_ID_Seting_HighPresureAction               ,        01U       ,  NVM_VoidType    ,     &NVM_Default_Seting_HighPresureAction                   },  
{NVM_ID_Seting_OperatationMode                 ,        01U       ,  NVM_VoidType    ,     &NVM_Default_Seting_OperatationMode                     },  
{NVM_ID_Seting_LowFlowRateWarningAction        ,        01U       ,  NVM_VoidType    ,     &NVM_Default_Seting_LowFlowRateWarningAction            },  
{NVM_ID_Seting_HighFlowRateWarningAction       ,        01U       ,  NVM_VoidType    ,     &NVM_Default_Seting_HighFlowRateWarningAction           },  


/*========================================== Please DO NOT add any New NVM paramater below this Point.=============================================*/
{NVM_END_Signature , NVM_End_Signature_Sizes ,  NVM_VoidType    ,  NVM_Default_End_Signature_Data  }

};


/*-----------------------------------------------------------------------------
 *  Configuration END
-------------------------------------------------------------------------------*/





#endif /* End of  ESP32_NVM_Stack_Config_H */
