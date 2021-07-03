/*******************************************************************************
 *  External Includes
*******************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include "Automatic_Water_Purifier.h"


/*******************************************************************************
 *  Variables and Constense
*******************************************************************************/
char buffer[Max_Debug_Buffer];
char Timming_Buffer[Max_Debug_Time_Buffer];

/*******************************************************************************
 *  Functions Extern deceleration
*******************************************************************************/

/* Function to get time difference with respect to current time*/
unsigned long Get_Time_Elapse(unsigned long Reference_Time);
/* For print debug trace.*/
extern void Debug_Trace(const char *fmt, ...);


/*******************************************************************************
 *  Startup Functions
*******************************************************************************/
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}












/*
===========================================================================
===========================================================================
                      Custom Functions
===========================================================================
==========================================================================
*/



/* ************************************************************************
 * Function to print output for debug purpose.
 * ************************************************************************
 * */
void Debug_Trace(const char *fmt, ...)
{

  /* Do operation only if debug support is ON*/
#if (Enable_Debug_Support == STD_ON)
    int Ret_Var;
    va_list args;
    va_start(args, fmt);
    Ret_Var = vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    /* Print Timing related inform*/
    sprintf(Timming_Buffer,"%011ld: ", millis());
    Serial.write(Timming_Buffer);

    if (Ret_Var > 0)
    {
        /* Print the  out to Uart Serial.*/
        (void) Serial.write(buffer);
    }
    else
    {
        (void) Serial.write("Error in Generating the debug Trace.");
    }

    Serial.write("\n");

#endif

}



/* ************************************************************************
 * Function to get time difference with respect to current time
 * ************************************************************************
 * */
unsigned long Get_Time_Elapse(unsigned long Reference_Time)
{
    /* Variable to store the difference in time.*/
    unsigned long Delta_Time = 0;
    unsigned long Current_Time = 0;

    /*Get current time*/
    Current_Time = millis();

    /* Check if overflow is happened. In case of overflow current value shall be smaller than the Reference time*/
    if( Current_Time < Reference_Time)
    {
         Delta_Time = Current_Time + ( 0xFFFFFFFF - Reference_Time);
    }
    else /* No over flow detected*/
    {
        Delta_Time = Current_Time - Reference_Time;
    }


    /* Return the difference*/
    return(Delta_Time);
}


