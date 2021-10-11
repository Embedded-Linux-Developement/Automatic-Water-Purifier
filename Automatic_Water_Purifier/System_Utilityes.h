
#ifndef System_Utilityes_H
#define System_Utilityes_H

#include "MyStdTypes.h"
#include "driver/pcnt.h" 


/*******************************************************************************
 *  System Utility related Configuration Start
*******************************************************************************/

/* MAcro defining the wait Time to complete System shutdown from start.*/
#define CompleteSystem_ShutDown_Wait_Time  6000    /* Configured as 6 Sec*/

/* Macro to defining the wait Time to Restart the fault checking in ms*/
#define Fault_Recheck_Wait_Time  2000    /* Configured as 2 Sec*/



/*-----------------------------------------------------------------------------
 *  System Utility related Configuration END
-------------------------------------------------------------------------------*/




/*******************************************************************************
 *  Program Specific data types.
*******************************************************************************/
/*Following Enumerators are to represent the UV lamp status*/
enum  Sys_UV_Lamp_Status{
  UV_Lamp_ON     = 0x5A, /* Indicate Lamp is ON. */
  UV_Lamp_OFF    = 0x0F, /* Indicate Lamp is OFF.*/
  UV_Lamp_UnInit = 0xA9  /* Indicate Lamp is Uninit.*/
};

/*Following Enumerators are to represent the UV lamp status*/
enum  Sys_UV_Lamp_Feedback_Status{
  UV_Lamp_Feedback_ON        = 0x98,  /* Indicate Lamp is ON Via feedback. */
  UV_Lamp_Feedback_OFF       = 0x89,  /* Indicate Lamp is OFF Via feedback.*/
  UV_Lamp_Feedback_InProgres = 0x5A,  /* Indicate Lamp is Starting is in progress.*/
  UV_Lamp_Feedback_Fault     = 0xE0   /* Indicate Lamp Fault detected Via feedback.*/
};


/* Enum to define Operatation Status*/
enum  Sys_Operatation_Status{
  Operatation_ON        = 0x5A, /* Indicate request is to ON. */
  Operatation_OFF       = 0x0F, /* Indicate request is to OFF.*/
  Operatation_InProgres = 0xA9  /* Indicate request is to In-Progres.*/
};

/* Enum to define Operatation Status*/
enum  Sensor_InputStatus_Status{
  Sensor_ON     = 0x44, /* Indicate Sensor is ON. */
  Sensor_OFF    = 0x48, /* Indicate Sensor is OFF.*/
  Sensor_Fault  = 0x94  /* Indicate Sensor is Fault.*/
};


/* Enum to define the state mechine of the Operatations*/
enum  Sensor_InputStatus_Status{
  Init_State                 = 0x45, /* Indicate Initialization sequence is in progress.*/
  Normal_Tank_Not_Full       = 0x65, /* Indicate Tank is Not full and needs to On the Water flow*/
  OverFlow_Tank_Not_Full     = 0x75, /* Indicate Tank full indicator not responding after considerable amound of water flows.*/
  Tank_Full                  = 0x85, /* Indicate Tank is full and Stop the flow..*/
  Tank_High_Presure          = 0x99, /* Indicate Some of the High Presure is detected at the input.*/
  Tank_Sensor_Fault          = 0x95, /* Indicate Some of the Sensor detected the Fault.*/
  Tank_Emergency_Stop        = 0xA5  /* Performe Emergency stop, Once inter in to this state It cannot come out. Needs power cycle.*/
};



/*******************************************************************************
 *  Macros
*******************************************************************************/

#define PCNT_UNIT_Used             PCNT_UNIT_0                  /* Select the Pulse Count 0  as the unit..*/
#define PCNT_Overflow_LIM_VAL       10000                       /* Set the max limit to trigger the interrupt*/
#define WaterFlow_Default_Calib_VAL 1000                        /* Paramater represent the default Calib value to be used if configured value is wrong.*/
#define PCNT_INPUT_SIG_IO          P2D_WaterFlowSensor_Input                           /* Pulse Input selected as GPIO 4 */

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

/* Macro to Declear Check flag, Shall use create new Check flag*/
#define Declear_Check_Flag(Flag_Name) (unsigned char Flag_Name = Sys_Flag_Init)

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





/*******************************************************************************
 *  Macro Functios
*******************************************************************************/

#define Delay_In_ms(DelayTime_in_Ms) delay((int)DelayTime_in_Ms / portTICK_PERIOD_MS)





/*******************************************************************************
 *  Public Function Definations Functions
*******************************************************************************/

extern void Init_MCU(void);
extern void Init_System_Utilityes_Variables(void);
extern void Init_GPT_ICU(void);
extern void Perform_Reset(void);

extern void Web_Server_Init(void);
extern void Web_Server_Processing(void);

extern void Init_PulseCounter (void);
extern void Clean_Water_Flow_Counters(void);
extern double Get_Current_WaterFlowedInL(void);
extern double Get_Current_SectionWaterFlowedInL(void);
extern void ProcessWaterFlowRate(void);
extern void ReStartFlowRate_Processing(void);
extern double Get_Instantinous_FlowRate_InLpM(void);

#endif /* End of  System_Utilityes_H */
