
#ifndef MyStdTypes_h
#define MyStdTypes_h


/*******************************************************************************
 *  Enums and typedefs
*******************************************************************************/

/*following are the Standard type */
typedef  signed char        sint8;     /* Slandered Data type for signed 8 bit   / 1 byte variable.*/
typedef  signed short       sint16;    /* Slandered Data type for signed 16 bit  / 2 byte variable.*/
typedef  signed long        sint32;    /* Slandered Data type for signed 32 bit  / 4 byte variable.*/
typedef  signed long long   sint64;    /* Slandered Data type for signed 64 bit  / 8 byte variable.*/

typedef  unsigned char      uint8;     /* Slandered Data type for unsigned 8 bit   / 1 byte variable.*/  
typedef  unsigned short     uint16;    /* Slandered Data type for unsigned 16 bit  / 2 byte variable.*/
typedef  unsigned long      uint32;     /* Slandered Data type for unsigned 32 bit  / 4 byte variable.*/
typedef  unsigned long long uint64;    /* Slandered Data type for unsigned 64 bit  / 8 byte variable.*/


/*Following is the Enum for NVM Paramater ID.*/
enum  NVMParam_ID_Enum{
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
   uint16              NVMParam_Length;         /* Variable to store the length of NVM paramater. Address shall calculate at run time, when ever there is a NVM read operatation*/
   NVMParam_Type_Enum  NVMParam_Type;           /* Variable to store the type of NVM paramater.*/
   const uint8       * NVMParam_Default;        /* Variable store the pointer of default value, If configured as NULL then shall be set as 0x00 as default value.*/

}NVM_Param_Config_Table_Type;


/*Following Enumerators are to Set the recovery Actions.*/
enum  Setting_Recovery_Actions{
  Recovery_None       = 0x55,  /* Represent No recovery is configured, Or Bo nothing*/
  Recovery_Time_Bound = 0x89, /* Recover after certain configured time */
  Recovery_On_PowerOn = 0xAA  /* Recover only after a power on cycle.*/
};

/*Following Enumerators are to Set Different Functional Mode.*/
enum  WP_Operatation_Mode{
  WF_Mode_Auto     = 0x5A, /* Indicate Select the different Mode automaticaly. */
  WF_Mode_Inline   = 0x47, /* Indicate the mode in which Only Inline water shall be used.*/
  WF_Mode_Via_Pump = 0xA9  /* Indicate the mode in which Only Pump shall be used to deef water supplay.*/
};





/*******************************************************************************
 *  Program Specific Macros.
*******************************************************************************/

/* Macro to represent the config ON/OFF status*/
#define STD_ON 0x22
#define STD_OFF 0x55

/* Macro to represent the error flags*/
#define E_OK      0x25   /* Represent starte is OK*/
#define E_NOT_OK  0x5A   /* Represent starte is NOT OK*/

/* Macro to represent On OFF Relay status*/
#define Relay_ON LOW
#define Relay_OFF HIGH

/* Macro to represent Button ON /OFF status*/
#define Button_ON LOW
#define Button_OFF HIGH

/* Limit Switch ON/ OFF ranges*/
#define Button_ON LOW
#define Button_OFF HIGH



#define CharNULLPtr (uint8 *)0x00  /* MAcro to represent the Null pointer within this program. */

/*******************************************************************************
 *  Macro Functions
*******************************************************************************/




#endif /* End of  MyStdTypes_h */
