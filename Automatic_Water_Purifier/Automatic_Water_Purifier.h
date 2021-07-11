
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
#define Total_NVM_Paramaters 18   /* Represent Max NVM paramater, Please make sure shall same as NVM_ID_Max*/
#define NVM_CRC_NoOfBytes    2    /* Number of bytes required to store CRC of each paramater.*/
#define NVM_CRC_Polynomial   0x2867 /* Polynomial for calculate the CRC*/

/* 
 * This paramater is to indicate wheather all NVM mirror values to be printed. 
 *  Recommenced to be STD_OFF on production, As it can compermise the Security Informatations in NVM.
*/
#define Debug_Print_All_NVM_Read_All_Value STD_ON   
/* 
 * This paramater is to perform the destractive Test, Will write New Data and read it back to verify.
 *   Its always Recomented to STD_OFF, Because will corrept the NVM data on every restart, Only meant for testing NVM stack.. 
 *   Prolonged use can reduce the longed cycle of the NVM.
*/
#define NVM_Stack_Distractive_Test STD_ON   

/* 
* This paramater is to perform the check for Default value.
*     1. Its always Recomented to STD_OFF, Because Once configured default value Check shall be always fails.
*     2. Its just considered to validate default value update after any code update, As validatation.
*/
#define NVM_Stack_Default_Test STD_ON   

/* 
 * This paramater is to Validate the Signature, 
 *   1. By writting and reading a specific data at start and end Address of the NVM memort block.
 *   2. For the same Will have 2 Reserved NVM paramater one at start and one at End.
 *   3. It shall use Update interface, which will not write to EEPROM Address data is same. 
 *   4. And we will keep same data, else will affect the endurance of the Prodect.
 *   4. Highely recommend to keep ot as STD_ON, because will help to find fault in NVM.
*/
#define NVM_Stack_Signature_Test STD_ON   


/* Following are the default Value for each NVM paramaters.*/
const uint8 NVM_Default_Value_WiFiSSIDName[75]    = "Test";                       /*String to hold the default value for the NVM_ID_Value_WiFiSSIDName NVM paramater.*/
const uint8 NVM_Default_Value_WiFiSSIDPasword[75] = "Test";                       /*String to hold the default value for the NVM_ID_Value_WiFiSSIDPasword NVM paramater.*/
const uint8 NVM_Default_Value_WiFiStsticIP[4]     = {198,168,1,10};               /*Array to hold the default value for the NVM_ID_Value_WiFiStsticIP NVM paramater.*/
const uint8 NVM_Default_Value_WiFiServerName[75]  = "Automatic Water Purifier";   /*String to hold the default value for the NVM_ID_Value_WiFiServerName NVM paramater.*/
const uint8 NVM_Default_Value_AdminPasword[30]    = "Admin";                      /*String to hold the default value for the NVM_ID_Value_AdminPasword NVM paramater.*/


const uint8 NVM_Default_Calibration_FlowMeaterFactor[4]          = {0x76,0x54,0x32,0x10};  /*Array to hold the default value for the NVM_ID_Calibration_FlowMeaterFactor NVM paramater.*/
const uint8 NVM_Default_Calibration_LowFlowRate[4]               = {0x00,0x00,0x00,0x00};  /*Array to hold the default value for the NVM_ID_Calibration_LowFlowRate NVM paramater.*/
const uint8 NVM_Default_Calibration_HighFlowRate[4]              = {0x00,0x00,0x00,0x00};  /*Array to hold the default value for the NVM_ID_Calibration_HighFlowRate NVM paramater.*/
const uint8 NVM_Default_Calibration_HighPresureCollingTime[4]    = {0x00,0x00,0x00,0x00};  /*Array to hold the default value for the NVM_ID_Calibration_HighPresureCollingTime NVM paramater.*/
const uint8 NVM_Default_Calibration_FlowRateWarningCollingTime[4]= {0x00,0x00,0x00,0x00};  /*Array to hold the default value for the NVM_ID_Calibration_FlowRateWarningCollingTime NVM paramater.*/
const uint8 NVM_Default_Calibration_WaterTankOverflowCapacity[4] = {0x00,0x00,0x00,0x00};  /*Array to hold the default value for the NVM_ID_Calibration_WaterTankOverflowCapacity NVM paramater.*/

const uint8 NVM_Default_Seting_WaterTankOverflowAction    = Recovery_On_PowerOn;       /*Variable to hold the default value for the NVM_ID_Seting_WaterTankOverflowAction NVM paramater.*/
const uint8 NVM_Default_Seting_HighPresureAction          = Recovery_Time_Bound;       /*Variable to hold the default value for the NVM_ID_Seting_HighPresureAction NVM paramater.*/
const uint8 NVM_Default_Seting_LowFlowRateWarningAction   = Recovery_Time_Bound;       /*Variable to hold the default value for the NVM_ID_Seting_LowFlowRateWarningAction NVM paramater.*/
const uint8 NVM_Default_Seting_HighFlowRateWarningAction  = Recovery_On_PowerOn;       /*Variable to hold the default value for the NVM_ID_Seting_HighFlowRateWarningAction NVM paramater.*/
const uint8 NVM_Default_Seting_OperatationMode            = WF_Mode_Inline;            /*Variable to hold the default value for the NVM_ID_Seting_OperatationMode NVM paramater.*/

/* Below Variables and Macros are for setting the NVM Signature Value*/
#define NVM_Start_Signature_Sizes  4U /* Define the sizes of Start Signature.*/
#define NVM_Start_Signature_Data   "SSV"  /*String to be stored in Start Signature.*/
const uint8 NVM_Default_Start_Signature_Data[NVM_Start_Signature_Sizes] = NVM_Start_Signature_Data;  /*String to hold the default value for the NVM_Start_Signature NVM paramater.*/

#define NVM_End_Signature_Sizes  4U /* Define the sizes of End Signature.*/
#define NVM_End_Signature_Data   {0x56U, 0x55U, 0xAAU, 0xFFU} /*String to be stored in End Signature.*/
const uint8 NVM_Default_End_Signature_Data[NVM_End_Signature_Sizes] = NVM_End_Signature_Data;  /*String to hold the default value for the NVM_End_Signature NVM paramater.*/


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

{NVM_ID_Value_WiFiSSIDName                     ,        75U       ,  NVM_StringType  ,     NVM_Default_Value_WiFiSSIDName                          },   
{NVM_ID_Value_WiFiSSIDPasword                  ,        75U       ,  NVM_StringType  ,     NVM_Default_Value_WiFiSSIDPasword                       },   
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
                             
/*For settings*/                             
{NVM_ID_Seting_WaterTankOverflowAction         ,        01U       ,  NVM_VoidType    ,     &NVM_Default_Seting_WaterTankOverflowAction             },  
{NVM_ID_Seting_HighPresureAction               ,        01U       ,  NVM_VoidType    ,     &NVM_Default_Seting_HighPresureAction                   },  
{NVM_ID_Seting_OperatationMode                 ,        01U       ,  NVM_VoidType    ,     &NVM_Default_Seting_OperatationMode                     },  
{NVM_ID_Seting_LowFlowRateWarningAction        ,        01U       ,  NVM_VoidType    ,     &NVM_Default_Seting_LowFlowRateWarningAction            },  
{NVM_ID_Seting_HighFlowRateWarningAction       ,        01U       ,  NVM_VoidType    ,     &NVM_Default_Seting_HighFlowRateWarningAction           },  


/*========================================== Please DO NOT add any New NVM paramater below this Point.=============================================*/
{NVM_END_Signature , NVM_End_Signature_Sizes ,  NVM_VoidType    ,  NVM_Default_End_Signature_Data  }

};

/* Type to define the CRC Value*/
typedef 
#if NVM_CRC_NoOfBytes == 2
    uint16 
#elif  NVM_CRC_NoOfBytes == 4/* If Number of Byte is 4*/
    uint32 
#else
  #error "Its Only support 16bit and 32 bit CRC calculation." 
#endif
 NVM_CRC_DataType;

/* Following is the union for splitting the checksum */
typedef union CRC_Split_Tag
{
    NVM_CRC_DataType CRC_Value;
    uint8  CRC_String[NVM_CRC_NoOfBytes];

}CRC_Split_t;



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

extern void Init_MCU(void);
extern void Perform_Reset(void);

/* NVM related Public functions*/

extern void Nvm_Read_All(void);
extern uint32 Convert_CRC(uint8 * InputBuffer);
extern uint32  Nvm_Read_Each(NVMParam_ID_Enum Input_Requested_NVMParam);
extern void    Nvm_Read_Each(NVMParam_ID_Enum Input_Requested_NVMParam, uint8 * Return_Nvm_Value);
extern void Nvm_Validate_CRC_And_Recover(NVMParam_ID_Enum Input_Requested_NVMParam);
#endif /* End of  Automatic_Water_Purifier_H */
