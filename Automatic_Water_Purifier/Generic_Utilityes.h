
#ifndef Generic_Utilityes_H
#define Generic_Utilityes_H

#include "MyStdTypes.h"


/*******************************************************************************
 *  Generic Utility Configuration Start
*******************************************************************************/
/* Set required Serial broad-rate.*/
#define Serial_BR_Rate 115200 /*serial communication at 9600 bits per second*/

/* Macro to enable or disable debug support,
     STD_ON   => Will print debug info over serial terminal.
     STD_OFF  => Shall Not print debug info over serial terminal.
  */
#define Enable_Debug_Support STD_ON

/* Macro to enable or disable tracing of the function calls,
     STD_ON   => Will print debug info over serial terminal.
     STD_OFF  => Shall Not print debug info over serial terminal.
  */
#define Enable_Debug_Trace_Function_Calls STD_OFF


/*Reserve Max debug variable sizes as 1KB.*/
#define Max_Debug_Buffer 1024
#define Max_Debug_Time_Buffer 128


/*-----------------------------------------------------------------------------
 *  Generic Utility Configuration END
-------------------------------------------------------------------------------*/

/*******************************************************************************
 *  Program Specific Macros.
*******************************************************************************/


/*******************************************************************************
 *  Macro Functions
*******************************************************************************/

/* If function call tracing is enabled,*/
#if (Enable_Debug_Trace_Function_Calls == STD_ON)
/* Print debug informatations*/
//#define Trace_Function_Call() Debug_Trace("Call Sequence:- In Function %-40s  , @ Line Number %04d , in file %s .", __func__,__LINE__,__FILE__)
/* One without file name*/
#define Trace_Function_Call() Debug_Trace("Call Sequence:- In Function %-40s  , @ Line Number %04d", __func__,__LINE__)

#else /* if (Enable_Debug_Trace_Function_Calls == STD_OFF)*/
/* Do nothing, as same is dissabled.*/
#define Trace_Function_Call() 

#endif /* End of (Enable_Debug_Trace_Function_Calls == STD_ON)*/


/*******************************************************************************
 *  Public Function Definations Functions
*******************************************************************************/

/* Function to get time difference with respect to current time*/
extern unsigned long Get_Time_Elapse(unsigned long Reference_Time);
/* For print debug trace.*/
extern void Debug_Trace(const char *fmt, ...);
/*unction to Init output serial for debug purpose. */
extern void Init_Trace(void);
/* Function to get time difference with respect to current time, Shall consider over flow case also.*/
extern unsigned long Get_Time_Elapse(unsigned long Reference_Time);
/* Function to get Random string. */
extern void Get_Randam_String(uint16 String_Length, uint8 *OutPutStringBuffer);
extern uint8 Check_Tolerance(uint32 InputValue, uint32 TargetedValue, uint8 ToleranceAllowed);





#endif /* End of  Generic_Utilityes_H */
