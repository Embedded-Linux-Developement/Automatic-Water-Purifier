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


/* Include required Html template header files*/
#include "Web_Server_Home_html.h"
#include "Web_Server_Debug_Trace_html.h"
#include "Web_Server_Calibration_html.h"
#include "Web_Server_Settings_html.h"
#include "Web_Server_About_html.h"


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
#define BufferStream_Max_Size 3000

/* Golbal bariable to store the Buffer stream data.*/
char BufferStream_ForDebugHTMLTrace[BufferStream_Max_Size + 10];

/* Local global to store the User names and paswords*/
char WiFi_Nw_Current_ssid[52];
char WiFi_Nw_Current_password[27];

char WiFi_Soft_AP_Current_SSIS_Name[52];
char WiFi_Soft_AP_Current_password[27];


/*Macro to define Max allowed Sizes for the array to store html page.*/
#define Max_HTML_Page_Sizes 20000
/* Global array to Populate and store the required HTML page to be displayed.*/
char Final_HTML_Page[Max_HTML_Page_Sizes];


/*******************************************************************************
 *  Functions Extern deceleration
 *******************************************************************************/
void WiFiEvent(WiFiEvent_t event);

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

void Web_Server_LiveStatus_Page(void)
{

Final_HTML_Page[Max_HTML_Page_Sizes -1] = 10;
}



#if 0
/* ************************************************************************
 * Function to Populate web page for Live status.
 * *************************************************************************/


/*
===========================================================================
===========================================================================
                      Public Generic functions
===========================================================================
===========================================================================
*/


/* ************************************************************************
 * Function to log latest status or to Monitor the provess..
 * *************************************************************************/
void Web_Server_Processing(void)
{

  /* Check if any  client has connected*/
  client = server.available();

  if (client)
  { /* If a new client connects,*/

    /* Read current time.*/
    previousTime = millis();

    // Debug_Trace("New Clint has been connected...");

    /* Clean the string to make a String to hold incoming data from the client*/
    currentLine = "";

    /*loop while the client's connected and No time out detected.*/
    while ((client.connected()) && (Get_Time_Elapse(previousTime) <= html_TimeOut_Clint))
    {

      /* if there's bytes to read from the client, */
      if (client.available())
      {
        /* Read each available Byte form client*/
        ClientCurrent_Char = client.read();

        /* Stor into a string variable.*/
        Client_Header_Request += ClientCurrent_Char;

        /* if the byte is a newline character */
        if (ClientCurrent_Char == '\n')
        {
          /* if the current line is blank, you got two newline characters in a row.
             that's the end of the client HTTP request, so send a response:
          */
          if (currentLine.length() == 0)
          {
            /* Trigger function to populate required webpage to show live status.*/
            Web_Server_LiveStatus_Page();

            // Break out of the while loop
            break;
          }
          else
          { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        }
        else if (ClientCurrent_Char != '\r')
        {                                    // if you got anything else but a carriage return character,
          currentLine += ClientCurrent_Char; // add it to the end of the currentLine
        }
      }



    }
    // Clear the header variable
    Client_Header_Request = "";
    // Close the connection
    client.stop();
  }
}

#endif






/* ************************************************************************
 * Function to Set On WiFi Event
 * *************************************************************************/
void WiFiEvent(WiFiEvent_t event)
{

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
    Debug_Trace("%s:- Disconnected from WiFi access point, So trying to reconnect.", WiFi_Nw_Current_ssid);
    /* Try to Re-Connect to Wifi Network.*/
    WiFi.begin(WiFi_Nw_Current_ssid, WiFi_Nw_Current_password);
    break;
  case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
    Debug_Trace("%s:- Authentication mode of access point has changed", WiFi_Nw_Current_ssid);
    break;
  case SYSTEM_EVENT_STA_GOT_IP:
    Debug_Trace("%s:- Obtained New IP address and is %s ", WiFi_Nw_Current_ssid, WiFi.localIP().toString().c_str());
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

  /* Set Call back Event for the Wifi Status*/
  WiFi.onEvent(WiFiEvent);


  /*Read Wifi SSID  and pasword from from NVM.*/
  Nvm_Read_Each(NVM_ID_Value_WiFiSSIDName, (uint8 *)WiFi_Nw_Current_ssid);
  Nvm_Read_Each(NVM_ID_Value_WiFiSSIDPasword, (uint8 *)WiFi_Nw_Current_password);

  /*Read Soft Access Point SSID  and pasword from from NVM.*/
  Nvm_Read_Each(NVM_ID_Value_WiFiSSIDName, (uint8 *)WiFi_Soft_AP_Current_SSIS_Name);
  Nvm_Read_Each(NVM_ID_Value_WiFiSSIDPasword, (uint8 *)WiFi_Soft_AP_Current_password);



 
 /* Set WiFi mode to work in Both Station and Soft Access Point*/
  WiFi.mode(WIFI_MODE_APSTA);
 
  /* Start Soft AP*/
  WiFi.softAP(WiFi_Soft_AP_Current_SSIS_Name, WiFi_Soft_AP_Current_password);
  /* Start Wifi Station.*/
  WiFi.begin(WiFi_Nw_Current_ssid, WiFi_Nw_Current_password);


  /* Add additional logic for Time out and automatic switching between AP and WiFi station based on the availability.
    Reffer the Approach mentioned in https://techtutorialsx.com/2021/01/04/esp32-soft-ap-and-station-modes/
   */



/* Server for Home Page.*/
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) 
    {
 
    request->send(200, "text/html", Html_Head_Home);
  });



/* Server for Debug Trace page.*/
    server.on("/DebugTrace", HTTP_GET, [](AsyncWebServerRequest * request) 
    {

     Web_Server_LiveStatus_Page();
 
    request->send(200, "text/html", Html_Head_Debug_Trace);
  });


/* Server for Calibration page.*/
    server.on("/Calibration", HTTP_GET, [](AsyncWebServerRequest * request) 
    {
 
    request->send(200, "text/html", Html_Head_Calibration);
  });


/* Server for Settings page.*/
    server.on("/Settings", HTTP_GET, [](AsyncWebServerRequest * request) 
    {
 
    request->send(200, "text/html", Html_Head_Settings);
  });

/* Server for About page.*/
    server.on("/About", HTTP_GET, [](AsyncWebServerRequest * request) 
    {
 
    request->send(200, "text/html", Html_Head_About);
  });



 

  server.begin();

}












