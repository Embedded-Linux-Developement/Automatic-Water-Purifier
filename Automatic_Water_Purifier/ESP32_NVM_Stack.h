
#ifndef ESP32_NVM_Stack_H
#define ESP32_NVM_Stack_H

#include "MyStdTypes.h"


/*******************************************************************************
 *  NVM Configuration Start
*******************************************************************************/
/* This Macro represent the maximum available, For ESP32, Its 512Bytes */
#define Max_Available_EEPROM 512
#define Total_NVM_Paramaters 18   /* Represent Max NVM paramater, Please make sure shall same as NVM_ID_Max*/
#define NVM_CRC_NoOfBytes    2    /* Number of bytes required to store CRC of each paramater.*/
#define NVM_CRC_Polynomial   0x2869 /* Polynomial for calculate the CRC*/

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
#define NVM_Start_Signature_DefaultData   "NOK"  /*Default String to be stored in Start Signature.*/
const uint8 NVM_Default_Start_Signature_Data[NVM_Start_Signature_Sizes] = NVM_Start_Signature_DefaultData;  /*String to hold the default value for the NVM_Start_Signature NVM paramater.*/

#define NVM_End_Signature_Sizes  4U /* Define the sizes of End Signature.*/
#define NVM_End_Signature_Data   0x5655AAFFU /*String to be stored in End Signature.*/
#define NVM_End_Signature_DefaultData   0x00000000U  /*Default String to be stored in Start Signature.*/
const uint8 NVM_Default_End_Signature_Data[NVM_End_Signature_Sizes] = {0x00,0x00,0x00,0x00};  /*String to hold the default value for the NVM_End_Signature NVM paramater.*/

/*******************************************************************************
 *  Data Type definitions
*******************************************************************************/

/*Following is the Enum for represent Different NVM paramater Type .*/
enum  NVMParam_Type_Enum{
  NVM_StringType,     /* Tis type is use to store content in string format., Will read or write until '\0' detected or Max Length reached. the paramater shall have minimum length of 2 Byte, Because one byte is reserved for null charactor '\0'.*/
  NVM_VoidType        /*This type used to read any type of data, but read will read entire data, till max length.*/
};

/*Following is the Enum for NVM Paramater ID.*/
enum  NVMParam_ID_Enum{
  NVM_Start_Signature,                           /* This NVM paramater is storing the Signature to Identify the start and validate NVM, Please keep it at the begining.*/

/* ================================ Please add new Paramater below this point.=============================*/

  NVM_ID_Value_WiFiSSIDName,                     /* This NVM paramater is storing the WiFi SSID Name set by the user.*/
  NVM_ID_Value_WiFiSSIDPasword,                  /* This NVM paramater is storing the WiFi SSID Pasword set by the user. Pasword shall Not store Securely*/
  NVM_ID_Value_WiFiStsticIP,                     /* This NVM paramater is storing the Server IP, If user specify then only same shall be considered, Else shall ignore.*/
  NVM_ID_Value_WiFiServerName,                   /* This NVM paramater is storing the Server Custom Server Name, If user want to, Else Shall use default Server Name.*/
  NVM_ID_Value_AdminPasword,                     /* This NVM paramater is storing the Admin pasword User has been set. Default password shall be "Admin"*/

  NVM_ID_Calibration_FlowMeaterFactor,             /* This NVM paramater is storing the convertion factor for the flow meter.*/
  NVM_ID_Calibration_LowFlowRate,                  /* This NVM paramater is storing the Lowest Flow rate allowed without any warning.*/
  NVM_ID_Calibration_HighFlowRate,                 /* This NVM paramater is storing the Higest Flow rate allowed without any warning.*/
  NVM_ID_Calibration_HighPresureCollingTime,       /* This NVM paramater is storing the Cool off time in Second after High presure is being detected.*/
  NVM_ID_Calibration_FlowRateWarningCollingTime,   /* This NVM paramater is storing the Cool off time in Second after High / Low flow rate detected.*/
  NVM_ID_Calibration_WaterTankOverflowCapacity,    /* This NVM paramater is storing the Maximum Tank Capacity. After reaching this level if float sensor is not detected, Then will take action*/
      
  NVM_ID_Seting_WaterTankOverflowAction,          /* This NVM paramater is storing Action to me considered once Potential Overflow is detected.*/
  NVM_ID_Seting_HighPresureAction,                /* This NVM paramater is storing Action to me considered once High presure is detected detected.*/
  NVM_ID_Seting_OperatationMode,                  /* This NVM paramater is storing Operatation mode of the filter.*/
  NVM_ID_Seting_LowFlowRateWarningAction,         /* This NVM paramater is storing Action to me considered once low Flow rate is detected.*/
  NVM_ID_Seting_HighFlowRateWarningAction,        /* This NVM paramater is storing Action to me considered once High Flow rate is detected.*/
  

/* ================================ Do Not add any new Paramater below this point.=============================*/

  NVM_END_Signature,                              /* This NVM paramater is storing the Signature to Identify the start and validate NVM, Please keep it at the begining.*/
  NVM_ID_Max                                      /* To represent the maximum ID possible.*/
};



/* Structure to Configuration paramaters for NVM Paramaters.*/
typedef struct NVM_Param_Config_Table_Tag {
   NVMParam_ID_Enum    NVMParam_ID;             /* Variable to store the NVM paramater ID.*/
   uint16              NVMParam_Length;         /* Variable to store the length of NVM paramater. Address shall calculate at run time, when ever there is a NVM read operatation*/
   NVMParam_Type_Enum  NVMParam_Type;           /* Variable to store the type of NVM paramater.*/
   const uint8       * NVMParam_Default;        /* Variable store the pointer of default value, If configured as NULL then shall be set as 0x00 as default value.*/

}NVM_Param_Config_Table_Type;



/*******************************************************************************
 *  NVM paramater Configuration
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


/*-----------------------------------------------------------------------------
 *  Configuration END
-------------------------------------------------------------------------------*/

/*******************************************************************************
 *  Special Typedefs.
*******************************************************************************/
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

/*******************************************************************************
 *  Macro Functions
*******************************************************************************/

/* 
* This paramater is just to dissable the writting operatation. 
*   1. This option is to protect NVM from unwanted write during development.
*   1. Its always Recomented to STD_ON, In final prodect, else NVM write will not happen.
*   2. IN Development phase you can keep is as STD_OFF, IN this case Will not write to EEPROM, 
*       Only NVM mirror data shall be updated.
*/
#define NVM_Stack_Dissable_NVM_Write STD_OFF

/*******************************************************************************
 *  Public Function Definations Functions
*******************************************************************************/


/*
===========================================================================
          Public functions related to NVM data Processing.
===========================================================================
*/

extern void Nvm_Read_All(void);
extern uint32  Nvm_Read_Each(NVMParam_ID_Enum Input_Requested_NVMParam);
extern void    Nvm_Read_Each(NVMParam_ID_Enum Input_Requested_NVMParam, uint8 * Return_Nvm_Value);
extern void   Nvm_Write_Each(NVMParam_ID_Enum Input_Requested_NVMParam, uint32 NVM_Intger_Value);
extern void Nvm_Write_Each(NVMParam_ID_Enum Input_Requested_NVMParam, uint8 *Nvm_Array_Value);
extern void Nvm_Validate_CRC_And_Recover(NVMParam_ID_Enum Input_Requested_NVMParam);
extern void NVM_READ_Write_Test(void);


#endif /* End of  ESP32_NVM_Stack_H */
