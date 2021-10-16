
#ifndef ESP32_NVM_Stack_H
#define ESP32_NVM_Stack_H

#include "MyStdTypes.h"

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
 *  NVM ID configuration Configuration Start
*******************************************************************************/

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

  NVM_ID_Calibration_FlowMeaterFactor,             /* This NVM paramater is storing the convertion factor for the flow meter, Number of ticks for 1 Liter.*/
  NVM_ID_Calibration_LowFlowRate,                  /* This NVM paramater is storing the Lowest Flow rate in milli Litter per Min allowed without any warning.*/
  NVM_ID_Calibration_HighFlowRate,                 /* This NVM paramater is storing the Higest Flow rate in milli Litter per Min allowed without any warning.*/
  NVM_ID_Calibration_HighPresureCollingTime,       /* This NVM paramater is storing the Cool off time in milli Second after High presure is being detected.*/
  NVM_ID_Calibration_FlowRateWarningCollingTime,   /* This NVM paramater is storing the Cool off time in milli Second after High / Low flow rate detected.*/
  NVM_ID_Calibration_WaterTankOverflowCapacity,    /* This NVM paramater is storing the Maximum Tank Capacity in milli Litter. After reaching this level if float sensor is not detected, Then will take action*/
  NVM_ID_Calibration_AutoModeBoosterStartTime,     /* This NVM paramater is storing time to wait after water flow is detected as zero if NVM_ID_Seting_OperatationMode = WF_Mode_Auto, unit is in milli Seconds.*/
  NVM_ID_Calibration_MaxDryRunTimeTime,            /* This NVM paramater is storing time for Maximum allowed Drt run time, unit is in milli Seconds, Once dry run detected shall swich to Emergency shut down mode.*/
  
      
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

#define NVM_CRC_NoOfBytes    2    /* Number of bytes required to store CRC of each paramater.*/

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
