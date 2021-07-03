
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

#define Button_Feed_Back_Enabled STD_ON

/*Reserve Max debug variable sizes as 1KB.*/
#define Max_Debug_Buffer 128
#define Max_Debug_Time_Buffer 30


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

#endif /* End of  Automatic_Water_Purifier_H */
