
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

/*-------------------------------------------------------------------------------------
              Support for Check_Flag
--------------------------------------------------------------------------------------*/

/* Define Sys_Flag_True*/
#ifndef Sys_Flag_True
#define Sys_Flag_True 0X01
#endif

/* Define SSys_Flag_False*/
#ifndef Sys_Flag_False
#define Sys_Flag_False 0X00
#endif

/* Define SSys_Flag_Init*/
#ifndef Sys_Flag_Init
#define Sys_Flag_Init 0X11
#endif

/* Macro to clear Check flag, Shall use before using the flag*/
#define Clear_Check_Flag(Flag_Name) (Flag_Name = Sys_Flag_Init)

/* Macro to make flag True, Once flag is False after clearing same shall not convert to true again, shall preserve False state*/
#define True_Check_Flag(Flag_Name) (Flag_Name &= Sys_Flag_True)

/* Macro to make flag False, Once flag is False after clearing same shall preserve False state, till next clear.*/
#define False_Check_Flag(Flag_Name) (Flag_Name &= Sys_Flag_False)

/* Macro to check if flag is set to True atleast once and never set to false,
     After Init if true is not set atleast once then also return false.*/
#define Is_Check_Flag_True(Flag_Name) (Flag_Name == Sys_Flag_True)

/* Macro to check if flag is set to False atleast once after last clean,
     After Init if false is not set atleast once then also return false.*/
#define Is_Check_Flag_False(Flag_Name) (Flag_Name == Sys_Flag_False)

/*-------------------------------------------------------------------------------------
              Support for Perodic statement
--------------------------------------------------------------------------------------*/

/* Following are the Macro required for the below Perodic statement MACRO functions*/
#define Perodic_Statement_Invalid_Time 0xFFFFFFFFU

/* Below are the Macro functions which allows the execution of statement between
   them only once in every providded time, We have following MACROS
   1. Define_Perodic_Statement( Statement_Name )                  ==> Define the perodic statement Should be at the start of the Scope.
   2. Start_Perodic_Statement(Statement_Name, ProviddedTime_ms)   ==> Shall help to start the Perodic statements.
   3. End_Perodic_Statement()                                     ==> Shall help to End / Stop the previous Perodic statement.
   4. ReStart_Perodic_Statement(Statement_Name)                   ==> Shall Re-Start the Perodic statement.

   Input Arguments
     Statement_Name    => Please give a simple Name for the Perodic statement section.
     ProviddedTime_ms  => Time in ms to define the periodicity of the Perodic statement section.

   It can use in Nested passion also.
*/

/* Macro function for Define Perodic Statement,
  Please use this in the start of scope where you want to use Perodic Statement.
  */
#define Define_Perodic_Statement(Statement_Name) static uint32 P_S##Statement_Name##Timeout = Perodic_Statement_Invalid_Time;

/* Macro function to Start the Perodic statement section.*/
#define Start_Perodic_Statement(Statement_Name, ProviddedTime_ms)                                           \
    {                                                                                                       \
        uint8 P_S##Statement_Name##CheckerFlag;                                                             \
        Clear_Check_Flag(P_S##Statement_Name##CheckerFlag);                                                 \
        if (P_S##Statement_Name##Timeout == Perodic_Statement_Invalid_Time)                                 \
        {                                                                                                   \
            True_Check_Flag(P_S##Statement_Name##CheckerFlag);                                              \
            P_S##Statement_Name##Timeout = millis();                                                        \
        }                                                                                                   \
        else if (Get_Time_Elapse(P_S##Statement_Name##Timeout) >= ProviddedTime_ms) /* if time is elapsed*/ \
        {                                                                                                   \
            True_Check_Flag(P_S##Statement_Name##CheckerFlag);                                              \
            P_S##Statement_Name##Timeout = millis();                                                        \
        }                                                                                                   \
        else                                                                                                \
        {                                                                                                   \
            False_Check_Flag(P_S##Statement_Name##CheckerFlag);                                             \
        }                                                                                                   \
        if (Is_Check_Flag_True(P_S##Statement_Name##CheckerFlag))                                           \
        {                                                                                                   \
        /* Add what ever Statement you needs to Run in a perodic phase based on the Providded time.*/       \
        /*When Next time its excused and time experted then shall Run*/

/* Macro function to End the Perodic statement section.*/
#define End_Perodic_Statement() \
    }                           \
    }

/* MAcro to Restart the Timming of the perodic statement.*/
#define ReStart_Perodic_Statement(Statement_Name) P_S##Statement_Name##Timeout = Perodic_Statement_Invalid_Time;

/*******************************************************************************
 *  Public Function Definations Functions
 *******************************************************************************/

/* Function to get time difference with respect to current time, Shall consider over flow case also.*/
extern unsigned long Get_Time_Elapse(unsigned long Reference_Time);
/* Function to get Random string. */
extern void Get_Randam_String(uint16 String_Length, uint8 *OutPutStringBuffer);
extern uint8 ADC_Check_Tolerance(uint32 InputValue, uint32 TargetedValue, uint8 ToleranceAllowed);

#endif /* End of  Generic_Utilityes_H */
