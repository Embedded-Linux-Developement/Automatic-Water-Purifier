
#ifndef MyStdTypes_h
#define MyStdTypes_h


/*******************************************************************************
 *  Program Specific Macros.
*******************************************************************************/

/* Macro to represent the config ON/OFF status*/
#define STD_ON 0x22
#define STD_OFF 0x55

/* Macro to represent On OFF Relay status*/
#define Relay_ON LOW
#define Relay_OFF HIGH

/* Macro to represent Button ON /OFF status*/
#define Button_ON LOW
#define Button_OFF HIGH

/* Limit Switch ON/ OFF ranges*/
#define Button_ON LOW
#define Button_OFF HIGH



#define CharNULLPtr (char *)0x00  /* MAcro to represent the Null pointer within this program. */

/*******************************************************************************
 *  Macro Functions
*******************************************************************************/



/*******************************************************************************
 *  Enums and typedefs
*******************************************************************************/

/*Following is the Enum for NVM Paramater ID.*/
enum  NVMParam_ID_Enum{
  NVM_ID_Value_WiFiSSIDName,                     /* This NVM paramater is storing the WiFi SSID Name set by the user.*/
  NVM_ID_Value_WiFiSSIDPasword,                  /* This NVM paramater is storing the WiFi SSID Pasword set by the user. Pasword shall Not store Securely*/
  NVM_ID_Value_WiFiStsticIP,                     /* This NVM paramater is storing the Server IP, If user specify then only same shall be considered, Else shall ignore.*/
  NVM_ID_Value_WiFiServerName,                   /* This NVM paramater is storing the Server Custom Server Name, If user want to, Else Shall use default Server Name.*/

  NVM_ID_Calibration_FlowMeaterFactor,             /* This NVM paramater is storing the convertion factor for the flow meter.*/
  NVM_ID_Calibration_LowFlowRate,                  /* This NVM paramater is storing the Lowest Flow rate allowed without any warning.*/
  NVM_ID_Calibration_HighFlowRate,                 /* This NVM paramater is storing the Higest Flow rate allowed without any warning.*/
  NVM_ID_Calibration_HighPresureCollingTime,       /* This NVM paramater is storing the Cool off time in Second after High presure is being detected.*/
  NVM_ID_Calibration_WaterTankOverflowCapacity,    /* This NVM paramater is storing the Maximum Tank Capacity. After reaching this level if float sensor is not detected, Then will take action*/
      
  NVM_ID_Seting_WaterTankOverflowAction,          /* This NVM paramater is storing Action to me considered once Potential Overflow is detected.*/
  NVM_ID_Seting_HighPresureAction,                /* This NVM paramater is storing Action to me considered once High presure is detected detected.*/
  NVM_ID_Seting_OperatationMode,                  /* This NVM paramater is storing Operatation mode of the filter.*/
  NVM_ID_Seting_LowFlowRateWarningAction,         /* This NVM paramater is storing Action to me considered once low Flow rate is detected.*/
  NVM_ID_Seting_HighFlowRateWarningAction,        /* This NVM paramater is storing Action to me considered once High Flow rate is detected.*/
  
  NVM_ID_Max                                      /* To represent the maximum ID possible.*/
};

/*Following is the Enum for represent Different NVM paramater Type .*/
enum  NVMParam_Type_Enum{
  NVM_StringType,     /* Tis type is use to store content in string format., Will read / write until '\0' detected or Max Length reached.*/
  NVM_VoidType        /*This type used to read any type of data, but read will read entire data, till max length.*/
};

/* Structure to Configuration paramaters for NVM Paramaters.*/
typedef struct NVM_Param_Config_Table_Tag {
   NVMParam_ID_Enum    NVMParam_ID;             /* Variable to store the NVM paramater ID.*/
   unsigned short      NVMParam_Length;         /* Variable to store the length of NVM paramater. Address shall calculate at run time, when ever there is a NVM read operatation*/
   NVMParam_Type_Enum  NVMParam_Type;           /* Variable to store the type of NVM paramater.*/
   char              * NVMParam_Default;        /* Variable store the pointer of default value, If configured as NULL then shall be set as 0x00 as default value.*/

}NVM_Param_Config_Table_Type;



#endif /* End of  MyStdTypes_h */
