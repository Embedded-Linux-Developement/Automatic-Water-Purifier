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
#include "Web_Server_Html_Status_Page_Config.h"


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

/* Variable to store the HTTP request*/
String Client_Header_Request;
String currentLine;

/* Previous time for time out purpose.*/
unsigned long previousTime = 0;

char ClientCurrent_Char;

// Initialize the client library
WiFiClient client;

/*******************************************************************************
 *  Functions Extern deceleration
 *******************************************************************************/

/*******************************************************************************
 *  Class Objects.
 *******************************************************************************/

/*Set web server port number to 80 */
WiFiServer server(80);


/*
===========================================================================
===========================================================================
                      Privite functions
===========================================================================
===========================================================================
*/

/* ************************************************************************
 * Function to Populate web page for Live status.
 * *************************************************************************/
void Web_Server_LiveStatus_Page(void)
{

  /* HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK) */
  /* and a content-type so the client knows what's coming, then a blank line:*/
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  // Display the HTML web Header part
  client.print(Html_Templates_Debug_Trace_Page_Header);

  /* Get Queue string*/
  Populate_BufferStream_FromQueue(BufferStream_ForDebugHTMLTrace, BufferStream_Max_Size);
  /* Print HTML processed Page*/
  client.print(BufferStream_ForDebugHTMLTrace);

  /* Print Html Footer for the Debug trace*/
  client.print(Html_Templates_Debug_Trace_Page_Footer);

  // The HTTP response ends with another blank line
  client.println();
}

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

/* ************************************************************************
 * Function to Init the Web server Required
 * *************************************************************************/
void Web_Server_Init(void)
{
  /* change these values to match your network*/
  char Current_ssid[100];
  char Current_password[100];

  /*Read SSID from NVM.*/
  Nvm_Read_Each(NVM_ID_Value_WiFiSSIDName, (uint8 *)Current_ssid);
  Nvm_Read_Each(NVM_ID_Value_WiFiSSIDPasword, (uint8 *)Current_password);

  /* Try to connect to Wifi Access point based on the configuration.*/
  WiFi.begin(Current_ssid, Current_password);

  /* Waite until it get connect*/
  while (WiFi.status() != WL_CONNECTED)
  {
    /* Waite for 100ns befor reading status again.*/
    delay(100 / portTICK_PERIOD_MS);
  }

  /* If connected began the server.*/
  if (WiFi.status() == WL_CONNECTED)
  {
    /* Start the server.*/
    server.begin();

    Debug_Trace("WiFi get connected and IP address is %s", WiFi.localIP().toString().c_str());
  }
  /* If not able to connect to the Web server.*/
  else
  {
    Debug_Trace("Failed to connect to the configured WiFi %s", NVM_ID_Value_WiFiSSIDName);
  }

  /* Add additional logic for Time out and automatic switching between AP and WiFi station based on the availability.
    Reffer the Approach mentioned in https://techtutorialsx.com/2021/01/04/esp32-soft-ap-and-station-modes/
   */
}












