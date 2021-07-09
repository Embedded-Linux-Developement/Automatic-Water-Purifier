/*******************************************************************************
 *  External Includes
*******************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "Automatic_Water_Purifier.h"

#include <EEPROM.h>
#include "CRC16.h"
#include "CRC.h"


/*******************************************************************************
 *  Variables and Constense
*******************************************************************************/
char buffer[Max_Debug_Buffer];
char Timming_Buffer[Max_Debug_Time_Buffer];

/* Below are the global variable for NVM RAM mirroring*/
uint8 NVM_Ram_Mirror_Buffer[Max_Available_EEPROM];  /* Buffer storing the NVM RAM mirroe. */
uint8 * NVM_ParamaterMirror[Total_NVM_Paramaters];  /* Pointer to storing each paramater Buffer. */

/*******************************************************************************
 *  Functions Extern deceleration
*******************************************************************************/

/* Function to get time difference with respect to current time*/
unsigned long Get_Time_Elapse(unsigned long Reference_Time);
/* For print debug trace.*/
extern void Debug_Trace(const char *fmt, ...);



/*******************************************************************************
 *  Class Objects.
*******************************************************************************/

CRC16 MY_CRC;

/*******************************************************************************
 *  Startup Functions
*******************************************************************************/
void setup()
{
  /* Start the Serial Port*/
  Serial.begin(115200);

  /* Initate the Micro Settings. */
  Init_MCU();
  /* Perform NVM read operatations.*/
  Init_NVM_Stack();

  /* Initialise all timmer and External interrupts*/
  Init_GPT_ICU();
}

void loop()
{
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
  sprintf(Timming_Buffer, "%011ld: ", millis());
  Serial.write(Timming_Buffer);

  if (Ret_Var > 0)
  {
    /* Print the  out to Uart Serial.*/
    (void)Serial.write(buffer);
  }
  else
  {
    (void)Serial.write("Error in Generating the debug Trace.");
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
  if (Current_Time < Reference_Time)
  {
    Delta_Time = Current_Time + (0xFFFFFFFF - Reference_Time);
  }
  else /* No over flow detected*/
  {
    Delta_Time = Current_Time - Reference_Time;
  }

  /* Return the difference*/
  return (Delta_Time);
}


/* ************************************************************************
 * Function to convert CRC in buffer to respective CRC value.
 * *************************************************************************/
NVM_CRC_DataType Convert_STR_2_CRC(uint8 * InputBuffer)
{
  uint8 Index;
  CRC_Split_t  Current_CRC;

  for( Index = 0; Index < NVM_CRC_NoOfBytes; Index++) 
  {
    Current_CRC.CRC_String[Index]  = InputBuffer[Index];
  }

 return((NVM_CRC_DataType)Current_CRC.CRC_Value);
}


/* ************************************************************************
 * Function to convert CRC in value to respective CRC buffer.
 * *************************************************************************/
void Convert_CRC_2_STR(NVM_CRC_DataType CRC_Value, uint8 * OutputBuffer)
{
  uint8 Index;
  CRC_Split_t  Current_CRC;

  Current_CRC.CRC_Value = CRC_Value;

  for( Index = 0; Index < NVM_CRC_NoOfBytes; Index++) 
  {
    OutputBuffer[Index] = Current_CRC.CRC_String[Index];
  }
 
}


/*
===========================================================================
===========================================================================
          Public functions related to NVM data Processing.
===========================================================================
==========================================================================
*/

/* ************************************************************************
 * Function to Process the NVM data, Validate Configuration and store.
 * *************************************************************************/

void Init_NVM_Stack(void)
{
  uint8 Error_Status = E_OK;
  uint16 ForLoopIndex;
  uint16 TotalNvm_Memory;
  float NvmUtilization;

  /* Do basic validatation of NVM configuration.*/

  /* Check the Configuration Max value, If Not set error flag..*/
  if (NVM_ID_Max != Total_NVM_Paramaters)
  {
    Debug_Trace("Error:- Size of Configuration table is not matching with Max Number of NVM paramaters...");
    Error_Status = E_NOT_OK;
  }

  /* Check if total sizes of the NVM is within the limit.*/
  else
  {
    /* Loop for all array and get the Sum.*/
    for (ForLoopIndex = 0, TotalNvm_Memory = 0; ForLoopIndex < Total_NVM_Paramaters; ForLoopIndex++)
    {
      TotalNvm_Memory += NVM_Param_Config_Table[ForLoopIndex].NVMParam_Length + NVM_CRC_NoOfBytes;
    }
    /* Check if the total sizes is within the Limit.*/
    if (TotalNvm_Memory >= Max_Available_EEPROM)
    {
      Debug_Trace("Error:- Total NVM paramaters configured (%d) is grated than Max allowed size (%d)...", TotalNvm_Memory, Max_Available_EEPROM);
      Error_Status = E_NOT_OK;
    }
  }

  if (E_OK != Error_Status)
  {
    Perform_Reset();
  }
  NvmUtilization = ((float)((float)TotalNvm_Memory / (float)Max_Available_EEPROM) )* 100;
  Debug_Trace("NVM configuration Basic Check is OK, Total Consumed is %d Bytes out of %d. And Total NVM Utilization is %f ...",TotalNvm_Memory, Max_Available_EEPROM, NvmUtilization);
  /* Trigger NVM read all to update the RAM mirroe after reading from NVM.*/
  Nvm_Read_All();
}

/* ************************************************************************
 * Function to read all data from NVM and store in mirror if CRC is correct, 
 *    else update with default value.
 * *************************************************************************/
void Nvm_Read_All(void)
{

  uint16 NVMParam_LoopIndex;
  uint16 NVMEachData_Index;
  uint16 Current_ParamLength;
  uint16 Current_Mirror_Start_Address;
  NVM_CRC_DataType Calculated_NVM_CRC;
  NVM_CRC_DataType Stored_NVM_CRC;
  /* Variable required only when its enebled.*/
#if Debug_Print_All_NVM_Read_All_Value == STD_ON
   uint8 TempValue;
   uint16 Inner_Loop_Index;
#endif


   /* Initialise the NVM*/
    EEPROM.begin(Max_Available_EEPROM);

  /* Loop for all NVM paramaters. */
  for (NVMParam_LoopIndex = 0, Current_Mirror_Start_Address = 0, Current_ParamLength = 0;
       NVMParam_LoopIndex < Total_NVM_Paramaters;
       NVMParam_LoopIndex++)
  {
    /* Get Current Length.*/
    Current_ParamLength = NVM_Param_Config_Table[NVMParam_LoopIndex].NVMParam_Length;

    /* Update the Mirror Start Address*/
    NVM_ParamaterMirror[NVMParam_LoopIndex] = (uint8 *)&NVM_Ram_Mirror_Buffer[Current_Mirror_Start_Address];

    /* Read the NVM data.*/
    for (NVMEachData_Index = 0; NVMEachData_Index < (Current_ParamLength + NVM_CRC_NoOfBytes); NVMEachData_Index++)
    {
      ((uint8 *)NVM_ParamaterMirror[NVMParam_LoopIndex])[NVMEachData_Index] = EEPROM.read((Current_Mirror_Start_Address + NVMEachData_Index));
    }

    /* Calculate the CRC.*/
    MY_CRC.setPolynome(NVM_CRC_Polynomial);
    MY_CRC.add((uint8_t *)NVM_ParamaterMirror[NVMParam_LoopIndex], Current_ParamLength);
    Calculated_NVM_CRC = MY_CRC.getCRC();
    MY_CRC.restart();

    /* Read Stored CRC*/
    Stored_NVM_CRC = Convert_STR_2_CRC((uint8 *)(NVM_ParamaterMirror[NVMParam_LoopIndex] + Current_ParamLength));
    /* Check if CRC is matching..*/
    if (Stored_NVM_CRC == Calculated_NVM_CRC)
    {
      Debug_Trace("CRC calculation for paramater with ID %d is OK...", NVMParam_LoopIndex);
    }
    else /* CRC calculation failed*/
    {
      Debug_Trace("Warning:- CRC calculation Failed for paramater with ID %d, Setting default value...", NVMParam_LoopIndex);
      /* RAM mirror shall set with default value, because There is NO point in updating the NVM after fault is detected.. 
         Those values shall be update only when there is any New request for NVM update. */
     
     /* If data type is of String*/
     if ( NVM_StringType == NVM_Param_Config_Table[NVMParam_LoopIndex].NVMParam_Type)
     {
       /* If Default value is configured.*/
       if(NVM_Param_Config_Table[NVMParam_LoopIndex].NVMParam_Default != CharNULLPtr)
       {
          strcpy((char *)NVM_ParamaterMirror[NVMParam_LoopIndex], (char *)NVM_Param_Config_Table[NVMParam_LoopIndex].NVMParam_Default);
       } /* Default value not configured.*/
       else /* Set Zero \ '\0' in First location, which render it as empty string*/
       {
         ((uint8 *)NVM_ParamaterMirror[NVMParam_LoopIndex])[0] = '\0';
       }
     }
     else /* It's a Normal array, needs to copy all data*/
     {
       /* If Default value is configured.*/
       if(NVM_Param_Config_Table[NVMParam_LoopIndex].NVMParam_Default != CharNULLPtr)
       {
         /* Copy all data from default memory.*/
          memcpy((uint8 *)NVM_ParamaterMirror[NVMParam_LoopIndex], (uint8 *)NVM_Param_Config_Table[NVMParam_LoopIndex].NVMParam_Default,  Current_ParamLength);
       } /* Default value not configured.*/
       else /* Set Zero \ '\0' in First location, which render it as empty string*/
       {
          /* Set all element as Zero.*/
          memset((uint8 *)NVM_ParamaterMirror[NVMParam_LoopIndex], 0x00,  Current_ParamLength);
       }
     }

     /* Calculate New check sum and store.*/
     /* Calculate the CRC.*/
     MY_CRC.setPolynome(NVM_CRC_Polynomial);
     MY_CRC.add((uint8_t *)NVM_ParamaterMirror[NVMParam_LoopIndex], Current_ParamLength);
     Calculated_NVM_CRC = MY_CRC.getCRC();
     MY_CRC.restart();

     /* Convert Checksum in to array*/
     Convert_CRC_2_STR(Calculated_NVM_CRC,(uint8 *)(NVM_ParamaterMirror[NVMParam_LoopIndex] + Current_ParamLength));

    /* Re calculate CRC again to make sure the Current calculation is correct.*/
    /* Calculate the CRC.*/
    MY_CRC.setPolynome(NVM_CRC_Polynomial);
    MY_CRC.add((uint8_t *)NVM_ParamaterMirror[NVMParam_LoopIndex], Current_ParamLength);
    Calculated_NVM_CRC = MY_CRC.getCRC();
    MY_CRC.restart();

    /* Read Stored CRC*/
    Stored_NVM_CRC = Convert_STR_2_CRC((uint8 *)(NVM_ParamaterMirror[NVMParam_LoopIndex] + Current_ParamLength));
    /* Check if CRC is matching..*/
    if (Stored_NVM_CRC != Calculated_NVM_CRC)
    {
      Debug_Trace("Error:- CRC calculation for paramater with ID %d is Not Successful after multiple attempt, So resterting...", NVMParam_LoopIndex);
      Perform_Reset();
    }

/* Print Respective mirror value and its check sums based on the type.*/
#if Debug_Print_All_NVM_Read_All_Value == STD_ON
    Debug_Trace("Info:- NVM Mirror final value for paramater %d is as mentioned below", NVMParam_LoopIndex);
    
    /* If type is string then Print it as a string, Else print all value.*/
    /* If data type is of String*/
     if ( NVM_StringType == NVM_Param_Config_Table[NVMParam_LoopIndex].NVMParam_Type)
     {
        Serial.write("      Value In string :- ");
        /*Use Direct Print without using debug function such that intermidate buffer use can reduce.*/
        Serial.write((char *)NVM_ParamaterMirror[NVMParam_LoopIndex]);
     }
     else /* It's a Normal array, needs to copy all data*/
     {
       Serial.write("      Values In HEX (0th Index to Max) :- ");
        /* Loop for each byte and write*/
        for (Inner_Loop_Index = 0; Inner_Loop_Index < NVM_Param_Config_Table[NVMParam_LoopIndex].NVMParam_Length;Inner_Loop_Index++)
        {
          TempValue = * ((uint8 *)(NVM_ParamaterMirror[NVMParam_LoopIndex] + Inner_Loop_Index));
          Serial.print(TempValue, HEX); 
          Serial.write(" ");
        }
     }

     /* Add New Line */
     Serial.write("\n");
#endif


    }
    /* Increase Address Pointer to reach Next paramater start Location.*/
    Current_Mirror_Start_Address += Current_ParamLength + NVM_CRC_NoOfBytes;
  }
}

/*
===========================================================================
===========================================================================
          Public functions related to System Operatations
===========================================================================
==========================================================================
*/

/* ************************************************************************
 * Function to Initialise all System related functions.
 * *************************************************************************/
void Init_MCU(void)
{
  /* Start WDG */


  /* Initializes all port settings.*/



}

/* ************************************************************************
 * Function to Initialise all Timmer and External Interrupt related settings.
 * *************************************************************************/
void Init_GPT_ICU(void)
{
  /* Initializes all timer related settings.*/

 /* Initializes all External interrupts.*/

}

/* ************************************************************************
 * Function to perform SW reset when ever any critical fault detected.
 * *************************************************************************/
void Perform_Reset(void)
{
  Debug_Trace("Dissable and Resetting the Water Purifier Due to Above mentioned error....");

  /* Dissable all Output.*/

  /* Perform Reset.*/
  ESP.restart();
}
