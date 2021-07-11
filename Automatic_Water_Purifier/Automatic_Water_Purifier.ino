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
  /* Test NVM based on the configuration.*/
  NVM_READ_Write_Test();

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
===========================================================================
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


/* *************************************************************************
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
===========================================================================
*/

/* *************************************************************************
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

/* ****************************************************************************
 * Function to read all data from NVM and store in mirror if CRC is correct, 
 *    else update with default value.
 * ****************************************************************************/
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
   uint8 Current_Length;
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
        /* Copy to local variable to save Excitation time, to read every time from ROM. */
        Current_Length = NVM_Param_Config_Table[NVMParam_LoopIndex].NVMParam_Length;
        /* Loop for each byte and write*/
        for (Inner_Loop_Index = 0; Inner_Loop_Index < Current_Length;Inner_Loop_Index++)
        {
          TempValue = ((uint8 *)NVM_ParamaterMirror[NVMParam_LoopIndex])[Inner_Loop_Index];
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



/* *****************************************************************************
 * Function to Read as Integer from the NVM based on the Paramater ID.
 *  1. Function are for the NVM Paramaters which needs to return an Integer,
 *        And of type NVM_VoidType in configuration. 
 *  2. If requested for paramater with type NVM_StringType is requested, 
 *       then first 4 byte or length ( which ever is the smallest) 
 *       shall be considered and convert into Respective integer.
 * ****************************************************************************/
uint32 Nvm_Read_Each(NVMParam_ID_Enum Input_Requested_NVMParam)
{
  uint32 Return_Value = uint32_Max; /*Set Higest value as invalid value.*/
  Data_Split_t Split_Var;
  uint8 Loop_Index;
  uint8 Current_Length;
  NVMParam_ID_Enum Requested_NVMParam;

  /* Validate the Requested Index, and correct Same.*/
  Requested_NVMParam = NVM_Get_NVM_Param_Index(Input_Requested_NVMParam);

  /* Check if requested paramater is valied.*/
  if (Requested_NVMParam < NVM_ID_Max)
  {
    /* Checking of type is not required because any way convertion is performing based on the data length only.*/
    /* Validate the NVM mirror */
    Nvm_Validate_CRC_And_Recover(Requested_NVMParam);

    /* If its a one byte data.*/
    if (NoOf_Byte_One == NVM_Param_Config_Table[Requested_NVMParam].NVMParam_Length)
    {
      Return_Value = ((uint8 *)NVM_ParamaterMirror[Requested_NVMParam])[Int_Zero];
    }
    /* If number of byte is grater than 2 and less than 4, if more than 4, only consider upto 4*/
    else
    {
      Current_Length = ((NVM_Param_Config_Table[Requested_NVMParam].NVMParam_Length <= NoOf_Byte_Four) ? NVM_Param_Config_Table[Requested_NVMParam].NVMParam_Length : NoOf_Byte_Four);
      /* Loop for each variable and store, after paramater length set value as Zero*/
      for (Loop_Index = 0, Split_Var.U32_Data = uint32_Min; Loop_Index < Current_Length; Loop_Index++)
      {
        /* Read each data from mirror and store in t split array.*/
        Split_Var.SplitArray[Loop_Index] = ((uint8 *)NVM_ParamaterMirror[Requested_NVMParam])[Loop_Index];
      }

      Return_Value = Split_Var.U32_Data;
    }
  }
  else /* Wrong paramater passed.*/
  {
    Debug_Trace("Dev Error:- Requested Paramater ID %d to function %s is wrong...", Input_Requested_NVMParam, __func__);
  }

  return (Return_Value);
}

/* ********************************************************************************
 * Function to Read as string / array from the NVM based on the Paramater ID.
 *  1. Function are for the NVM Paramaters which needs to return an String / array,
 *        And of type NVM_StringType in configuration. 
 *  2. If requested for paramater with type NVM_VoidType is requested, 
 *       then based on length each element shall store into output array.
 *  3. Its responsibilty of user to give adequate sizes to Second Input argument 
 *       Return_Nvm_Value.
 * *********************************************************************************/
void Nvm_Read_Each(NVMParam_ID_Enum Input_Requested_NVMParam, uint8 *Return_Nvm_Value)
{

  uint8 Loop_Index;
  uint8 Current_Length;
  NVMParam_ID_Enum Requested_NVMParam;

  /* Validate the Requested Index, and correct Same.*/
  Requested_NVMParam = NVM_Get_NVM_Param_Index(Input_Requested_NVMParam);

  /* Check if requested paramater is valied.*/
  if (Requested_NVMParam < NVM_ID_Max)
  {
    /* Validate the NVM mirror */
    Nvm_Validate_CRC_And_Recover(Requested_NVMParam);
    /* If its a String, Then do a string copy.*/
    if (NVM_StringType == NVM_Param_Config_Table[Requested_NVMParam].NVMParam_Type)
    {
      /* Do string copy */
      strcpy((char *)Return_Nvm_Value, (char *)NVM_ParamaterMirror[Requested_NVMParam]);
    }
    /* for any other type copy all data back.*/
    else
    {
      /* Copy to local variable to save Excitation time, to read every time from ROM. */
      Current_Length = NVM_Param_Config_Table[Requested_NVMParam].NVMParam_Length;
      /* Loop for each variable and store, Expecting the length of buffer is enough.*/
      for (Loop_Index = 0; Loop_Index < Current_Length; Loop_Index++)
      {
        /* Read each data from mirror and store in to return array.*/
        Return_Nvm_Value[Loop_Index] = ((uint8 *)NVM_ParamaterMirror[Requested_NVMParam])[Loop_Index];
      }
    }
  }
  else /* Wrong paramater passed.*/
  {
    Debug_Trace("Dev Error:- Requested Paramater ID %d to function %s is wrong...", Input_Requested_NVMParam, __func__);
  }
}


/* ********************************************************************************
 * Function to validate NVM CRC status based on the Paramater ID. 
 *     And trigger Nvm Read all service if fault is detected.
 * *********************************************************************************/
void Nvm_Validate_CRC_And_Recover(NVMParam_ID_Enum Input_Requested_NVMParam)
{
  NVM_CRC_DataType Calculated_NVM_CRC;
  NVM_CRC_DataType Stored_NVM_CRC;
  uint8 Loop_Index;
  uint8 Current_Length;
  NVMParam_ID_Enum Requested_NVMParam;

  /* Validate the Requested Index, and correct Same.*/
  Requested_NVMParam = NVM_Get_NVM_Param_Index(Input_Requested_NVMParam);

  /* Copy to local variable to save Excitation time, to read every time from ROM. */
  Current_Length = NVM_Param_Config_Table[Requested_NVMParam].NVMParam_Length;

  /* Calculate New check sum and store.*/
  /* Calculate the CRC.*/
  MY_CRC.setPolynome(NVM_CRC_Polynomial);
  MY_CRC.add((uint8_t *)NVM_ParamaterMirror[Requested_NVMParam], Current_Length);
  Calculated_NVM_CRC = MY_CRC.getCRC();
  MY_CRC.restart();

  /* Read Stored CRC from mirror*/
  Stored_NVM_CRC = Convert_STR_2_CRC((uint8 *)(NVM_ParamaterMirror[Requested_NVMParam] + Current_Length));
  /* Check if CRC is matching..*/
  if (Stored_NVM_CRC != Calculated_NVM_CRC)
  {
    Debug_Trace("Error:- CRC calculation for paramater with ID %d is Not Successful, So triggering NVM Real All Service...", NVM_Param_Config_Table[Requested_NVMParam].NVMParam_ID);
    Nvm_Read_All();
  }

  /* Return is Not considered as same, shall not make any sense, As recovert action already performed... */
}

/* ********************************************************************************
 * Function to validate different aspect of NVM paramaters.
 * *********************************************************************************/
void NVM_READ_Write_Test(void)
{
  uint16 Param_Loop_Index;
  uint16 Data_Loop_Index;
  uint16 Current_Length;
  NVMParam_ID_Enum Converted_Index;
  uint8 Temp_Buffer[Int_OneHundred]; /* Expecting maximum Size of a paramater is 100 bytes.*/
  uint8 TestResult;

/*========================================================================*/
/* Validate the Default Data, If Enabled.*/
#if (NVM_Stack_Default_Test == STD_ON)
  /*========================================================================*/
  /* 
 * This testing will work only if NVM data is Not set updated.
 * This Test will test the updating of Defalt value.
*/

  /* Set default test result.*/
  TestResult = E_OK;
  /* Loop through each NVM paramater's */
  for (Param_Loop_Index = 0; Param_Loop_Index < NVM_ID_Max; Param_Loop_Index++)
  {
    /* Get Index of the Paramater. */
    Converted_Index = NVM_Get_NVM_Param_Index((NVMParam_ID_Enum)Param_Loop_Index);
    /* Store current data length */
    Current_Length = NVM_Param_Config_Table[Converted_Index].NVMParam_Length;

    /* Check and skype if Data length is more than expected.*/
    if (Current_Length >= Int_OneHundred)
    {
      Debug_Trace("Test Warning:- Default value checking for NVM paramater ID %d is skyped, Because length of this paramater is more than Test internal buffer.", NVM_Param_Config_Table[Converted_Index].NVMParam_ID);
      /* Skype this loop as not matching test design criteria.*/
      continue;
    }

    /* Read the Data from NVM Mirror.*/
    Nvm_Read_Each(NVM_Param_Config_Table[Converted_Index].NVMParam_ID, Temp_Buffer);

    /* Check the type of the NVM Paramater.*/
    if (NVM_Param_Config_Table[Converted_Index].NVMParam_Type == NVM_StringType)
    {
      /* Read the Data from NVM Mirror.*/
      if (strcmp((char *)Temp_Buffer, (char *)NVM_Param_Config_Table[Converted_Index].NVMParam_Default) != Int_Zero)
      {
        /* Set as result Failed.*/
        TestResult = E_NOT_OK;
        Debug_Trace("Test Failed:- Default value checking for NVM paramater ID %d is failed, It means at present NVM did not have default value.", NVM_Param_Config_Table[Converted_Index].NVMParam_ID);
      }
    }
    else /* If Type is not of string.*/
    {

      /* Loop for each element and validate.*/
      for (Data_Loop_Index = 0; Data_Loop_Index < Current_Length; Data_Loop_Index++)
      {
        /* Check if any data is mismatching.*/
        if (Temp_Buffer[Data_Loop_Index] != ((char *)NVM_Param_Config_Table[Converted_Index].NVMParam_Default)[Data_Loop_Index])
        {
          /* Mismatch found*/
          /* Set as result Failed.*/
          TestResult = E_NOT_OK;
          Debug_Trace("Test Failed:- Default value checking for NVM paramater ID %d is failed, It means at present NVM did not have default value.", NVM_Param_Config_Table[Converted_Index].NVMParam_ID);
          /* Break the loop*/
          Data_Loop_Index += Current_Length;
        }
      }
    }
  }

  /* Check Final result.*/
  if (TestResult == E_OK)
  {
    Debug_Trace("Test Passed:- Over all Default value Test Passed.");
  }
  else
  {
    Debug_Trace("Test Failed:- Over all Default value Test Failed.");
  }

#endif  /* End of NVM_Stack_Default_Test*/



    /* Return is Not considered as same, shall not make any sense, As recovert action already performed... */
}


/* ********************************************************************************
 * Function to get the Index based on Index Table of NVM paramater
 * *********************************************************************************/
NVMParam_ID_Enum NVM_Get_NVM_Param_Index(NVMParam_ID_Enum Requested_NVMParam)
{

  NVMParam_ID_Enum Return_Index;
  uint8 Loop_Index;

  /* Set Max value as invalid as its detectable.*/
  Return_Index = NVM_ID_Max;
  /* Check if requested above Max Value*/
  if (Requested_NVMParam < NVM_ID_Max)
  {

    /* Check if the Requested NVM paramater ID is inline with the Index of the array, If same then return same.*/
    if (NVM_Param_Config_Table[Requested_NVMParam].NVMParam_ID == Requested_NVMParam)
    {
      /* Return Index*/
      Return_Index = Requested_NVMParam;
    }
    else /* Index mismatch's, Do search operatation.*/
    {
      /* Loop for each variable and store, Expecting the length of buffer is enough.*/
      for (Loop_Index = Int_Zero, Return_Index = NVM_ID_Max; ((Loop_Index < NVM_ID_Max) && (NVM_ID_Max == Return_Index)); Loop_Index++)
      {
        /*Check if ID matches.*/
        if (Requested_NVMParam == NVM_Param_Config_Table[Requested_NVMParam].NVMParam_ID)
        {
          /* Captured current Index as its matchecs.*/
          Return_Index = (NVMParam_ID_Enum)Loop_Index;
        }
      }
    }
  }
  /* Return Actual Index.*/
  return (Requested_NVMParam);
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
