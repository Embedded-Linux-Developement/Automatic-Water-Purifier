
#ifndef Automatic_Water_Purifier_H
#define Automatic_Water_Purifier_H

#include "MyStdTypes.h"


/*******************************************************************************
 *  System Utility related Configuration Start
*******************************************************************************/

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



#endif /* End of  Automatic_Water_Purifier_H */
