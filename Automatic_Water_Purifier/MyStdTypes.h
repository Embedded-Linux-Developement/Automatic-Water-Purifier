
#ifndef MyStdTypes_h
#define MyStdTypes_h

/*****************************************************************************************************
File belongings to  Automatic_Water_Purifier program in githib, 
Link to Program GitHub Repository:- https://github.com/Embedded-Linux-Developement/Automatic-Water-Purifier
Description:- On of the file  Automatic Water Purifier, 
              Its a fully automatic water purifier Supporting code.

Copy Write:- 
Licence:- 
    <Automatic Water Purifier>
    Copyright (C) 2021  Jerry James

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

Auther:- Jerry James
E-mail:- Jerryonwork@gmail.com
Date  :- 15 Sep 2021
version:- V2.0.1

*******************************************************************************************************/

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
typedef  unsigned long      uint32;    /* Slandered Data type for unsigned 32 bit  / 4 byte variable.*/
typedef  unsigned long long uint64;    /* Slandered Data type for unsigned 64 bit  / 8 byte variable.*/



/*Following Enumerators are to Set the recovery Actions.*/
enum  Setting_Recovery_Actions{
  Recovery_None       = 0x55,  /* Represent No recovery is configured, Or Bo nothing */
  Recovery_Time_Bound = 0x89,  /* Recover after certain configured time */
  Recovery_On_PowerOn = 0xAA   /* Recover only after a power on cycle.*/
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

/* Macro to UV Lamp feedback Support*/
#define UV_Feedback_Both 0x96   /* Indicate both LDR reading shall be consider and if any failed decleared fault in UV lamp.*/
#define UV_Feedback_Any  0x77   /* Indicate if any one is working then take its result.*/
#define UV_Feedback_None 0x77   /* Shall Not consider the feedback, Simply bypass it.*/

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
