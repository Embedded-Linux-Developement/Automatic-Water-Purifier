
#ifndef Automatic_Water_Purifier_H
#define Automatic_Water_Purifier_H

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



/*-----------------------------------------------------------------------------
 *  Configuration END
-------------------------------------------------------------------------------*/

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
  NVM_ID_Seting_HighFlowRateWarningAction        /* This NVM paramater is storing Action to me considered once High Flow rate is detected.*/
  
};

/* Structure to Configuration paramaters for NVM Paramaters.*/
typedef struct NVM_Param_Config_Table_Tag {
   NVMParam_ID_Enum NVMParam_ID;     /* Variable to st*/


}NVM_Param_Config_Table_Type;





#endif /* End of  Automatic_Water_Purifier_H */
