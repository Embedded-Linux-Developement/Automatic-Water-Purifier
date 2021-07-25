
#ifndef MyStdTypes_h
#define MyStdTypes_h


/*******************************************************************************
 *  Enums and typedefs
*******************************************************************************/

/*following are the Standard type */
typedef  signed char        sint8;     /* Slandered Data type for signed 8 bit   / 1 byte variable.*/
typedef  signed short       sint16;    /* Slandered Data type for signed 16 bit  / 2 byte variable.*/
typedef  signed long        sint32;    /* Slandered Data type for signed 32 bit  / 4 byte variable.*/
typedef  signed long long   sint64;    /* Slandered Data type for signed 64 bit  / 8 byte variable.*/

typedef  unsigned char      uint8;     /* Slandered Data type for unsigned 8 bit   / 1 byte variable.*/  
typedef  unsigned short     uint16;    /* Slandered Data type for unsigned 16 bit  / 2 byte variable.*/
typedef  unsigned long      uint32;     /* Slandered Data type for unsigned 32 bit  / 4 byte variable.*/
typedef  unsigned long long uint64;    /* Slandered Data type for unsigned 64 bit  / 8 byte variable.*/



/*Following Enumerators are to Set the recovery Actions.*/
enum  Setting_Recovery_Actions{
  Recovery_None       = 0x55,  /* Represent No recovery is configured, Or Bo nothing*/
  Recovery_Time_Bound = 0x89, /* Recover after certain configured time */
  Recovery_On_PowerOn = 0xAA  /* Recover only after a power on cycle.*/
};

/*Following Enumerators are to Set Different Functional Mode.*/
enum  WP_Operatation_Mode{
  WF_Mode_Auto     = 0x5A, /* Indicate Select the different Mode automaticaly. */
  WF_Mode_Inline   = 0x47, /* Indicate the mode in which Only Inline water shall be used.*/
  WF_Mode_Via_Pump = 0xA9  /* Indicate the mode in which Only Pump shall be used to deef water supplay.*/
};


/* This union data type split the uint16 / uint32 variable to string and Vise versa. */
typedef union Data_Split_Tag
{
    uint8  U8_Data;
    uint16 U16_Data;
    uint32 U32_Data;
    uint8  SplitArray[4];

}Data_Split_t;


/*******************************************************************************
 *  Program Specific Macros.
*******************************************************************************/

/* Macro to represent the config ON/OFF status*/
#define STD_ON 0x22
#define STD_OFF 0x55

/* Macro to represent the error flags*/
#define E_OK      0x25   /* Represent starte is OK*/
#define E_NOT_OK  0x5A   /* Represent starte is NOT OK*/

/* Macro to represent On OFF Relay status*/
#define Relay_ON LOW
#define Relay_OFF HIGH

/* Macro to represent Button ON /OFF status*/
#define Button_ON LOW
#define Button_OFF HIGH

/* Limit Switch ON/ OFF ranges*/
#define Button_ON LOW
#define Button_OFF HIGH


#define CharNULLPtr (uint8 *)0x00  /* MAcro to represent the Null pointer within this program. */

/* Internal Macros used for indicate different Magic Number.*/
#define NoOf_Byte_One   1U
#define NoOf_Byte_Two   2U
#define NoOf_Byte_Three 3U
#define NoOf_Byte_Four  4U

#define Int_Zero        0U
#define Int_One         1U
#define Int_Two         2U
#define Int_Four        4U
#define Int_OneHundred  100U

#define uint32_Max        0xFFFFFFFFU
#define uint32_Min        (uint32)0x00000000U



/*******************************************************************************
 *  Macro Functions
*******************************************************************************/




#endif /* End of  MyStdTypes_h */
