
#ifndef Generic_Utilityes_H
#define Generic_Utilityes_H

#include "MyStdTypes.h"


/*******************************************************************************
 *  Generic Utility Configuration Start
*******************************************************************************/


/*-----------------------------------------------------------------------------
 *  Generic Utility Configuration END
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

/* Function to get time difference with respect to current time, Shall consider over flow case also.*/
extern unsigned long Get_Time_Elapse(unsigned long Reference_Time);
/* Function to get Random string. */
extern void Get_Randam_String(uint16 String_Length, uint8 *OutPutStringBuffer);
extern uint8 ADC_Check_Tolerance(uint32 InputValue, uint32 TargetedValue, uint8 ToleranceAllowed);




#endif /* End of  Generic_Utilityes_H */
