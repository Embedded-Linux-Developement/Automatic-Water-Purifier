/*******************************************************************************
 *  External Includes
 *******************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "MyStdTypes.h"
#include "ESP32_NVM_Stack.h"
#include "Generic_Utilityes.h"
#include "System_Utilityes.h"
#include "Web_Server.h"


// Load Wi-Fi library
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>


/* Include required Html template header files*/
#include "Web_Server_Home_html.h"
#include "Web_Server_Debug_Trace_html.h"
#include "Web_Server_Calibration_html.h"
#include "Web_Server_Settings_html.h"
#include "Web_Server_About_html.h"
#include "Asynchronous_Morse_Code_Generator.h"

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

/*-----------------------------------------------------------------------------------------------
References used for developing This webserver..
1. HTTP server with multiple pages ==>  https://www.arduinoslovakia.eu/blog/2019/4/esp8266---http-server-s-viac-strankami?lang=en  
2. HTTP Request Methods: GET vs POST => https://randomnerdtutorials.com/esp32-http-get-post-arduino/
3. for get Lib Path https://randomnerdtutorials.com/esp32-async-web-server-espasyncwebserver-library/
4. For support both AP and Station mode at same time.


Required Libs:- 

AsyncTCP = https://github.com/me-no-dev/AsyncTCP
ESPAsyncWebServer = https://github.com/me-no-dev/ESPAsyncWebServer
AsyncElegantOTA = https://github.com/me-no-dev/ESPAsyncWebServer

To install
 You can find or change the location of your sketchbook folder at File > Preferences > Sketchbook location. 
   Copy it in the “libraries” folder inside your sketchbook. Start the Arduino Software (IDE), 
   go to Sketch > Include Library. Verify that the library you just added is available in the list.

-------------------------------------------------------------------------------------------------*/

/*******************************************************************************
 *  Variables and Constense
 *******************************************************************************/

/*Define timeout time in milliseconds (example: 2000ms = 2s)*/
#define html_TimeOut_Clint 2000

/* Macro to allocate Bufferstream memory.*/
#define BufferStream_Max_Size 6000

/* Golbal bariable to store the Buffer stream data.*/
char BufferStream_ForDebugHTMLTrace[BufferStream_Max_Size + 10];

/* Local global to store the User names and paswords*/
char WiFi_Nw_Current_ssid[52];
char WiFi_Nw_Current_password[27];

char WiFi_Soft_AP_Current_SSIS_Name[52];
char WiFi_Soft_AP_Current_password[27];
/*Get The Host Name*/
char WiFi_Station_Name[75];


/*Macro to define Max allowed Sizes for the array to store html page.*/
#define Max_HTML_Page_Sizes 20000
/* Global array to Populate and store the required HTML page to be displayed.*/
String Final_HTML_Page;

/* Following are the User name and Pasword for OAT*/
const char OAT_UserName[50] = "JamesP_WP";
const char OAT_Pasword[50] = "ThisServerIP_1024Retuen";

uint32 Restart_Request = 0x00;

/*******************************************************************************
 *  Functions Extern deceleration
 *******************************************************************************/
void WiFiEvent(WiFiEvent_t event);
void Web_Server_Populate_Debug_Trace_Page(void);

/*******************************************************************************
 *  Class Objects.
 *******************************************************************************/

/*Set web server port number to 80 */
AsyncWebServer server(80);


/*
===========================================================================
===========================================================================
                      Privite functions
===========================================================================
===========================================================================
*/


/* ************************************************************************
 * Function to Populate Debug web page for Live status.
 * *************************************************************************/
void Web_Server_Populate_Debug_Trace_Page(void)
{
   /* Clear the string and Copy the content from the constand array*/
   Final_HTML_Page = "";
   Final_HTML_Page = Html_Head_Debug_Trace;

   /* Get Debug Info into a global variable.*/
   Populate_BufferStream_FromQueue(BufferStream_ForDebugHTMLTrace, BufferStream_Max_Size);

   /* Add 5 Sec Auto Refresh rate */
   Final_HTML_Page.replace("<!-- <meta http-equiv=\"refresh\" content=\"1\">   -->","<meta http-equiv=\"refresh\" content=\"1\">");

   /* Replace the String into Final HTML template*/
   Final_HTML_Page.replace("<h1>DO_NOT_REMOVE:-Custom_Add_Debug_String_Hear</h1>",BufferStream_ForDebugHTMLTrace);


}


/* ************************************************************************
 * Function to Populate Home Page for Water Purifier.
 * *************************************************************************/

 /* String for storing the User Info*/
 String UserInfo;

 /* String to store the Perline INfo to be printed.*/
 String PerLine_String_Info;
 String PerLine_String_Info_2;
/* Normal Array based string for population*/
char Array_PerLine_String[300];
char String_For_Morse_Code[150];

void Web_Server_Populate_Home_Page(void)
{

/* Variable to store the sensor status*/
Sensor_InputStatus_Status Current_Sensor_Status;
Sys_UV_Lamp_Feedback_Status UV_Lamp_Current_Status;
uint16 Current_Sensor_Raw_Value;
uint32 U32Current_Sensor_Raw_Value;
double DoubleCurrent_Sensor_Raw_Value;


  /* Clear the string and Copy the content from the constand array*/
  Final_HTML_Page = "";
  Final_HTML_Page = Html_Head_Home;

  PerLine_String_Info = "";
  PerLine_String_Info_2 = "";
  UserInfo = "<ol>\n";

  /* Add 5 Sec Auto Refresh rate */
  Final_HTML_Page.replace("<!-- <meta http-equiv=\"refresh\" content=\"1\">   -->", "<meta http-equiv=\"refresh\" content=\"1\">");

  /* Get Over all status of the */
  switch (Get_Current_Processing_Status())
  {

  case Init_State:
  {
    /* Update string for ID_1*/
    PerLine_String_Info = "<button class=\"btn Gray\">Init In Progress</button>";
    break;
  }
  case Normal_Tank_Not_Full:
  {
    /* Update string for ID_1*/
    PerLine_String_Info = "<button class=\"btn Green\">OK, Filtering in Progress</button>";
    break;
  }
  case OverFlow_Tank_Not_Full:
  {
    /* Update string for ID_1*/
    PerLine_String_Info = "<button class=\"btn Amber\">Warning, More Water Filtered</button>";

    /* Update string for ID_100 */
    UserInfo += "<li style=\"float: none;\">Consumed More Water, And Over flow Sensor Not detected. So Please Check Overflow Sensor position.</li>\n";

    break;
  }
  case Tank_Full:
  {
    /* Update string for ID_1*/
    PerLine_String_Info = "<button class=\"btn Green\">OK and Tank is Full</button>";
    break;
  }
  case Tank_High_Presure:
  {
    /* Update string for ID_1*/
    PerLine_String_Info = "<button class=\"btn Amber\">High Presure is Detected</button>";
    break;
  }
  case Tank_Sensor_Fault:
  {
    /* Update string for ID_1*/
    PerLine_String_Info = "<button class=\"btn Amber\">Fault Fault in Sensor</button>";

    /* Update string for ID_100*/
    UserInfo += "<li style=\"float: none;\">Fault detected in one of the Sensor, Please check Debug Trace and take corrective action.</li>\n";

    break;
  }
  case Tank_UV_Lamp_Fault:
  {

    /* Update string for ID_1*/
    PerLine_String_Info = "<button class=\"btn Amber\">UV Lamp Stop working</button>";

    /* Update string for ID_100*/
    UserInfo += "<li style=\"float: none;\">Fault detected in one / both sensors of the UV lamp, Please check Please check Lamp is its working, If not please replace with New UV lamp.</li>\n";

    break;
  }
  case Tank_Emergency_Stop:
  {
    /* Check if Emergency Stop os because of Dry Run*/
    if (Is_DryRunDetected())
    {
      /* Update string for ID_1*/
      PerLine_String_Info = "<button class=\"btn Red\">Dry Run Detected</button>";

      /* Update string for ID_100*/
      UserInfo += "<li style=\"float: none;\">Performed Emergency Stop, Because of Dry run detected. After addressing fault Re-Start System to recover from Emergency Fault.</li>\n";
    }
    else /* For all other fault*/
    {

      /* Update string for ID_1*/
      PerLine_String_Info = "<button class=\"btn Red\">Performed Emergency Stop</button>";

      /* Update string for ID_100*/
      UserInfo += "<li style=\"float: none;\">After fixing fault Re-Start System to recover from Emergency Fault.</li>\n";
    }
    break;
  }
  }

  /* Replace ID_1 String*/
  Final_HTML_Page.replace("<!--ID_1_Start--> <button class=\"btn Green\">Normal And OK</button>", PerLine_String_Info);

  /* Update string for ID_2*/
  PerLine_String_Info = "";
  PerLine_String_Info_2 = "";
  /* Read Float status*/
  Current_Sensor_Status = NON_Critical_GetStatus_OverFlow();
  /* Read Raw value*/
  Current_Sensor_Raw_Value = GetStatus_OverFlow_Sensor_Raw_Value();

  if (Current_Sensor_Status == Sensor_ON)
  {
    /* Get String for ID_2*/
    PerLine_String_Info = "<button class=\"Small_btn Green\">Tank Full</button>";

    /* Get String for ID_33*/
    PerLine_String_Info_2 = "<button class=\"Small_btn Green\">ON</button>";

    /* Get String for ID_34*/
    sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Green_Box\"> Raw Value = %d</button>", Current_Sensor_Raw_Value);
  }
  else if (Current_Sensor_Status == Sensor_OFF)
  {
    /* Get String for ID_2*/
    PerLine_String_Info = "<button class=\"Small_btn Amber\">Tank NOT Full</button>";

    /* Get String for ID_33*/
    PerLine_String_Info_2 = "<button class=\"Small_btn Red\">OFF</button>";

    /* Get String for ID_34*/
    sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Red_Box\"> Raw Value = %d</button>", Current_Sensor_Raw_Value);
  }
  else if (Current_Sensor_Status == Sensor_Fault)
  {
    /* Get String for ID_2*/
    PerLine_String_Info = "<button class=\"Small_btn Red\">Fault in Sensor</button>";

    /* Get String for ID_33*/
    PerLine_String_Info_2 = "<button class=\"Small_btn Amber\">Fault</button>";

    /* Get String for ID_34*/
    sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Amber_Box\"> Raw Value = %d</button>", Current_Sensor_Raw_Value);
  }
  else
  {
    /* Get String for ID_2*/
    PerLine_String_Info = "<button class=\"Small_btn Red\">Error in Processing</button>";
    /* Get String for ID_33*/
    PerLine_String_Info_2 = "<button class=\"Small_btn Red\">Error</button>";
    /* Get String for ID_34*/
    sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Red_Box\"> Raw Value = %d</button>", Current_Sensor_Raw_Value);
  }

  /* Replace Html String for ID 2*/
  Final_HTML_Page.replace("<!--ID_2_Start--> <button class=\"Small_btn Green\">Tank Full</button>", PerLine_String_Info);
  /* Replace Html String for ID 33*/
  Final_HTML_Page.replace("<!--ID_33_Start--><button class=\"Small_btn Green\">ON</button>", PerLine_String_Info_2);
  /* Replace Html String for ID 34*/
  Final_HTML_Page.replace("<!--ID_34_Start--> <button class=\"SmallBox_btn Gray_Box\"> Raw Value =2500</button>", Array_PerLine_String);

  /* Get current flow rate for ID_4*/
  DoubleCurrent_Sensor_Raw_Value = Get_Instantinous_FlowRate_InLpM();

  /* Check if High Flow Rate detected.*/
  if (Is_HighWaterFlowRateDetected())
  {
    /* Get String for ID_3*/
    PerLine_String_Info = "<button class=\"Small_btn Red\">High Flow Rate Detected</button>";

    /* Get String for ID_4*/
    sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Red_Box\">%fLpM</button>", DoubleCurrent_Sensor_Raw_Value);

    /* Update string for ID_100*/
    UserInfo += "<li style=\"float: none;\">Water Flow Rate is Very High, Please Consider Changing for water leak or Damaged filter from indide.</li>\n";
  
  }
  /* Check if Low Flow Rate detected.*/
  else if (Is_LowWaterFlowRateDetected())
  {
    /* Get String for ID_3*/
    PerLine_String_Info = "<button class=\"Small_btn Amber\">Low Flow Rate Detected</button>";

    /* Get String for ID_4*/
    sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Amber_Box\">%fLpM</button>", DoubleCurrent_Sensor_Raw_Value);

   /* Update string for ID_100*/
    UserInfo += "<li style=\"float: none;\">Water Flow Rate is Low, Please Consider Changing Filter, If Input water supplay is good.</li>\n";

  }
  else
  {
    /* Get String for ID_3*/
    PerLine_String_Info = "<button class=\"Small_btn Green\">Flow is Normal</button>";

    /* Get String for ID_4*/
    sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Green_Box\">%fLpM</button>", DoubleCurrent_Sensor_Raw_Value);
  }

  /* Replace Html String for ID_3*/
  Final_HTML_Page.replace("<!--ID_3_Start--> <button class=\"Small_btn Green\">Flow is Normal</button>", PerLine_String_Info);
  /* Replace Html String for ID_4*/
  Final_HTML_Page.replace("<!--ID_4_Start--> <button class=\"SmallBox_btn Green_Box\">4.5LpM</button>", Array_PerLine_String);


  /* Get current flow rate for ID_5*/
  DoubleCurrent_Sensor_Raw_Value = Get_Current_SectionWaterFlowedInL();
  /* Get String for ID_5*/
  sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Green_Box\">%fL</button>", DoubleCurrent_Sensor_Raw_Value);
  /* Replace Html String for ID_5*/
  Final_HTML_Page.replace("<!--ID_5_Start--> <button class=\"SmallBox_btn Green_Box\">10L</button>", Array_PerLine_String);

  /* Get current flow rate for ID_6*/
  DoubleCurrent_Sensor_Raw_Value = Get_Current_WaterFlowedInL();
  /* Get String for ID_6*/
  sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Green_Box\">%fL</button>", DoubleCurrent_Sensor_Raw_Value);
  /* Replace Html String for ID_6*/
  Final_HTML_Page.replace("<!--ID_6_Start--> <button class=\"SmallBox_btn Green_Box\">30L</button>", Array_PerLine_String);

/* Get current UV lamp Status for ID_7*/
UV_Lamp_Current_Status = NON_Critical_Get_UV_Lamp_Feedback();

/* Check if Lamp is OK*/
if(UV_Lamp_Current_Status == UV_Lamp_Feedback_ON)
{
  /* Get String for ID_7*/
  PerLine_String_Info = "<button class=\"Small_btn Green\">UV Lamp is ON and OK</button>";

  /* Get String for ID_30*/
  sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Green_Box\">%s</button>", GetStatus_UV_Lamp_Sensor_Raw_Value());

}
else if(UV_Lamp_Current_Status == UV_Lamp_Feedback_OFF)
{
  /* Get String for ID_7*/
  PerLine_String_Info = "<button class=\"Small_btn Green\">UV Lamp is OFF and OK</button>";

  /* Get String for ID_30*/
  sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Green_Box\">%s</button>", GetStatus_UV_Lamp_Sensor_Raw_Value());
}
else if(UV_Lamp_Current_Status == UV_Lamp_Feedback_InProgres)
{
  /* Get String for ID_7*/
  PerLine_String_Info = "<button class=\"Small_btn Gray\">UV Lamp state change is in Progres</button>";

  /* Get String for ID_30*/
  sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Gray_Box\">%s</button>", GetStatus_UV_Lamp_Sensor_Raw_Value());
}
else if(UV_Lamp_Current_Status == UV_Lamp_Feedback_Fault)
{
  /* Get String for ID_7*/
  PerLine_String_Info = "<button class=\"Small_btn Red\">Fault detected in UV lamp feedback.</button>";

  /* Get String for ID_30*/
  sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Red_Box\">%s</button>", GetStatus_UV_Lamp_Sensor_Raw_Value());
}
else
{
  /* Get String for ID_7*/
  PerLine_String_Info = "<button class=\"Small_btn Red\">Error detected in UV lamp feedback.</button>";
  
  /* Get String for ID_30*/
  sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Red_Box\">%s</button>", GetStatus_UV_Lamp_Sensor_Raw_Value());
}

  /* Replace Html String for ID_7*/
  Final_HTML_Page.replace("<!--ID_7_Start--> <button class=\"Small_btn Green\">Working OK</button>", PerLine_String_Info);

  /* Replace Html String for ID_30*/
  Final_HTML_Page.replace("<!--ID_30_Start--> <button class=\"SmallBox_btn Gray_Box\">UV Sensor 1 = 2500, UV Sensor 2 = 2500</button>", Array_PerLine_String);

/* Get Status and value for High Presure sensor. for ID_31 and ID_32*/
Current_Sensor_Status = NON_Critical_GetStatus_HighPresere();
Current_Sensor_Raw_Value = GetStatus_HighPresere_Sensor_Raw_Value();

/* check High preseure is ON*/
if(Current_Sensor_Status == Sensor_ON)
{
  /* Get String for ID_31*/
  PerLine_String_Info = "<button class=\"Small_btn Red\">ON</button>";

  /* Get String for ID_32*/
  sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Red_Box\"> Raw Value = %d</button>", Current_Sensor_Raw_Value);

}
else if(Current_Sensor_Status == Sensor_OFF)
{
  /* Get String for ID_31*/
  PerLine_String_Info = "<button class=\"Small_btn Green\">OFF</button>";

  /* Get String for ID_32*/
  sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Green_Box\"> Raw Value = %d</button>", Current_Sensor_Raw_Value);

}
else if(Current_Sensor_Status == Sensor_Fault)
{
  /* Get String for ID_31*/
  PerLine_String_Info = "<button class=\"Small_btn Amber\">Fault</button>";

  /* Get String for ID_32*/
  sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Amber_Box\"> Raw Value = %d</button>", Current_Sensor_Raw_Value);

}
else
{
    /* Get String for ID_31*/
  PerLine_String_Info = "<button class=\"Small_btn Gray\">Error</button>";

  /* Get String for ID_32*/
  sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Gray_Box\"> Raw Value = %d</button>", Current_Sensor_Raw_Value);
}

  /* Replace Html String for ID_31*/
  Final_HTML_Page.replace("<!--ID_31_Start--><button class=\"Small_btn Green\">ON</button>", PerLine_String_Info);

  /* Replace Html String for ID_32*/
  Final_HTML_Page.replace("<!--ID_32_Start--> <button class=\"SmallBox_btn Gray_Box\"> Raw Value =2500</button>", Array_PerLine_String);

/* Read Flow Raw value for ID_35*/
U32Current_Sensor_Raw_Value = Get_Current_Flow_Raw_Value();

  /* Get String for ID_35*/
  sprintf(Array_PerLine_String, "<button class=\"SmallBox_btn Gray_Box\"> Tick Value = %d</button>", U32Current_Sensor_Raw_Value);

  /* Replace Html String for ID_35*/
  Final_HTML_Page.replace("<!--ID_35_Start--> <button class=\"SmallBox_btn Gray_Box\"> Tick Value =2500</button>", Array_PerLine_String);

/* Check if required to update*/
if(UserInfo.length() >=9)
{
 UserInfo += "\n</ol> \n";
  /* Replace Html String for ID_100*/
  Final_HTML_Page.replace("<!--ID_100_Start--><p>Nothing Specific For Now...</p>", UserInfo);
}

}

/*
===========================================================================
===========================================================================
                      Public Generic functions
===========================================================================
===========================================================================
*/



/* ************************************************************************
 * Function to Set On WiFi Event
 * *************************************************************************/
void WiFiEvent(WiFiEvent_t event)
{
 Define_Perodic_Statement(SYSTEM_EVENT_STA_DISCONNECTED_Message);

  switch (event)
  {
  /* ----------------------------------------------------------
           Events Related to Wifi Satiation connection.
  -------------------------------------------------------------*/
  case SYSTEM_EVENT_WIFI_READY:
    Debug_Trace("WiFi interface ready");
    break;
  case SYSTEM_EVENT_SCAN_DONE:
    Debug_Trace("%s:-Completed scan for access points", WiFi_Nw_Current_ssid);
    break;
  case SYSTEM_EVENT_STA_START:
    Debug_Trace("%s:-WiFi client started", WiFi_Nw_Current_ssid);
    break;
  case SYSTEM_EVENT_STA_STOP:
    Debug_Trace("%s:- WiFi clients stopped", WiFi_Nw_Current_ssid);
    break;
  case SYSTEM_EVENT_STA_CONNECTED:
    Debug_Trace("%s:- Connected to access point", WiFi_Nw_Current_ssid);
    break;
  case SYSTEM_EVENT_STA_DISCONNECTED:

    Start_Perodic_Statement(SYSTEM_EVENT_STA_DISCONNECTED_Message, 10000)
        Debug_Trace("%s:- Disconnected from WiFi access point, So trying to reconnect.", WiFi_Nw_Current_ssid);

    End_Perodic_Statement()

    sprintf(String_For_Morse_Code,"WiFi Station %s Disconnected, Trying to Reconnect",WiFi_Nw_Current_ssid);
    /*Send Morse Code for Status*/
    Morse_Code_Sent(String_For_Morse_Code,MorseCodeBUffer_2);

        /* Try to Re-Connect to Wifi Network.*/
        WiFi.begin(WiFi_Nw_Current_ssid, WiFi_Nw_Current_password);
    break;
  case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
    Debug_Trace("%s:- Authentication mode of access point has changed", WiFi_Nw_Current_ssid);
    break;
  case SYSTEM_EVENT_STA_GOT_IP:
    Debug_Trace("%s:- Obtained New IP address and is %s ", WiFi_Nw_Current_ssid, WiFi.localIP().toString().c_str());

    sprintf(String_For_Morse_Code,"Obtained New IP address %s",WiFi.localIP().toString().c_str());
    /*Send Morse Code for Status*/
    Morse_Code_Sent(String_For_Morse_Code,MorseCodeBUffer_2);

    break;
  case SYSTEM_EVENT_STA_LOST_IP:
    Debug_Trace("%s:- Lost IP address and IP address is reset to 0", WiFi_Nw_Current_ssid);
    break;
  case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
    Debug_Trace("%s:- WiFi Protected Setup (WPS): succeeded in enrollee mode", WiFi_Nw_Current_ssid);
    break;
  case SYSTEM_EVENT_STA_WPS_ER_FAILED:
    Debug_Trace("%s:- WiFi Protected Setup (WPS): failed in enrollee mode", WiFi_Nw_Current_ssid);
    break;
  case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
    Debug_Trace("%s:- WiFi Protected Setup (WPS): timeout in enrollee mode", WiFi_Nw_Current_ssid);
    break;
  case SYSTEM_EVENT_STA_WPS_ER_PIN:
    Debug_Trace("%s:- WiFi Protected Setup (WPS): pin code in enrollee mode", WiFi_Nw_Current_ssid);
    break;

    /* ----------------------------------------------------------
             Events Related to Soft AP (Access Point)
    -------------------------------------------------------------*/

  case SYSTEM_EVENT_AP_START:
    Debug_Trace("%s:- WiFi access point started and IP address is %s.", WiFi_Soft_AP_Current_SSIS_Name, WiFi.softAPIP().toString().c_str());
    break;
  case SYSTEM_EVENT_AP_STOP:
    Debug_Trace("%s:- WiFi access point stopped.", WiFi_Soft_AP_Current_SSIS_Name);
    break;
  case SYSTEM_EVENT_AP_STACONNECTED:
    Debug_Trace("%s:- a New Client connected.", WiFi_Soft_AP_Current_SSIS_Name);
    break;
  case SYSTEM_EVENT_AP_STADISCONNECTED:
    Debug_Trace("%s:- aClient disconnected.", WiFi_Soft_AP_Current_SSIS_Name);
    break;
  case SYSTEM_EVENT_AP_STAIPASSIGNED:
    Debug_Trace("%s:- Assigned IP address to client", WiFi_Soft_AP_Current_SSIS_Name);
    break;
  case SYSTEM_EVENT_AP_PROBEREQRECVED:
    Debug_Trace("%s:- Received probe request", WiFi_Soft_AP_Current_SSIS_Name);
    break;
  case SYSTEM_EVENT_GOT_IP6:
    Debug_Trace("%s:- IPv6 is preferred", WiFi_Soft_AP_Current_SSIS_Name);
    break;

  case SYSTEM_EVENT_ETH_START:
    Debug_Trace("Ethernet started");
    break;
  case SYSTEM_EVENT_ETH_STOP:
    Debug_Trace("Ethernet stopped");
    break;
  case SYSTEM_EVENT_ETH_CONNECTED:
    Debug_Trace("Ethernet connected");
    break;
  case SYSTEM_EVENT_ETH_DISCONNECTED:
    Debug_Trace("Ethernet disconnected");
    break;
  case SYSTEM_EVENT_ETH_GOT_IP:
    Debug_Trace("Obtained IP address");
    break;
  default:
    break;
  } /* End of event switch.*/
}

/* ************************************************************************
 * Function to Init the Web server Required
 * *************************************************************************/
void Web_Server_Init(void)
{

// Set your Static IP address
IPAddress local_IP(192, 168, 0, 180);
// Set your Gateway IP address
IPAddress gateway(192, 168, 0, 1);

IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8); // optional
IPAddress secondaryDNS(8, 8, 4, 4); // optional


WiFi.disconnect(true); 

  /* Set Call back Event for the Wifi Status*/
  WiFi.onEvent(WiFiEvent);


  /*Read Wifi SSID  and pasword from from NVM.*/
  Nvm_Read_Each(NVM_ID_Value_WiFiSSIDName, (uint8 *)WiFi_Nw_Current_ssid);
  Nvm_Read_Each(NVM_ID_Value_WiFiSSIDPasword, (uint8 *)WiFi_Nw_Current_password);

  /*Read Soft Access Point SSID  and pasword from from NVM.*/
  Nvm_Read_Each(NVM_ID_Value_WiFiSSIDName, (uint8 *)WiFi_Soft_AP_Current_SSIS_Name);
  Nvm_Read_Each(NVM_ID_Value_WiFiSSIDPasword, (uint8 *)WiFi_Soft_AP_Current_password);

  Nvm_Read_Each(NVM_ID_Value_WiFiServerName, (uint8 *)WiFi_Station_Name);




 
 /* Set WiFi mode to work in Both Station and Soft Access Point*/
  WiFi.mode(WIFI_MODE_APSTA);
 
  /* Start Soft AP*/
  WiFi.softAP(WiFi_Soft_AP_Current_SSIS_Name, WiFi_Soft_AP_Current_password);

// Configures static IP address
if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
  Debug_Trace("STA Failed to configure");
}

  //WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(WiFi_Station_Name); //define hostname


  /* Start Wifi Station.*/
  WiFi.begin(WiFi_Nw_Current_ssid, WiFi_Nw_Current_password);


  /* Add additional logic for Time out and automatic switching between AP and WiFi station based on the availability.
    Reffer the Approach mentioned in https://techtutorialsx.com/2021/01/04/esp32-soft-ap-and-station-modes/
   */

  /* Server for Home Page.*/
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
      /* Populate string for home page.*/
      Web_Server_Populate_Home_Page();

    request->send(200, "text/html", Final_HTML_Page);
    /* Clean the string */
    Final_HTML_Page = ""; });

  /* Server for Debug Trace page.*/
  server.on("/DebugTrace", HTTP_GET, [](AsyncWebServerRequest *request)
            {
     /* Populate the Page.*/
     Web_Server_Populate_Debug_Trace_Page();

    request->send(200, "text/html", Final_HTML_Page);

    /* Clean the string */
    Final_HTML_Page = ""; });

  /* Server for Calibration page.*/
  server.on("/Calibration", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", Html_Head_Calibration); });

  /* Server for Settings page.*/
  server.on("/Settings", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", Html_Head_Settings); });

  /* Server for About page.*/
  server.on("/About", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", Html_Head_About); });

  /* Server for Perform Restart*/
  server.on("/Perform_ReStart", HTTP_GET, [](AsyncWebServerRequest *request)
            { 
              Debug_Trace(" Reset Request received, Going to process...");
              /* Redirect the page Before Restarting, to avoid continue restart*/
              request->redirect("/");
              Restart_Request = 0x5555AAAA;

               });





  /* Start OAT service.*/
  AsyncElegantOTA.begin(&server,OAT_UserName, OAT_Pasword);
 

  server.begin();

}



/* ************************************************************************
 * Function to process OAT request periodicity.
 * *************************************************************************/
void OAT_Web_Server_Processing(void)
{


  /* Loop for OAT*/
  AsyncElegantOTA.loop();

  /* Re-Start is a Restart request is set*/
  if (Restart_Request == 0x5555AAAA)
  {
    /* Add a 2 Sec Delay*/
    Delay_In_ms(3000);

    /* Perform Restart..*/
    Perform_Reset();
  }


}
