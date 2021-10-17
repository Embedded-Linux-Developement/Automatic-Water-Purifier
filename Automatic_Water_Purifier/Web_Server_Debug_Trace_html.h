
/*****************************************************************************************************
Header file  Web_Server_Debug_Trace_html.h
Description:- Simple header file to store Html templates for Debug Trave Page

*******************************************************************************************************/

#ifndef Web_Server_Debug_Trace_html_H
#define Web_Server_Debug_Trace_html_H

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

/* Define Header part*/

const char Html_Head_Debug_Trace[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
  <meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
  <title>Water Purifier Trace Debug</title>
  <!-- Add 1 Sec Auto refresh -->
  <!-- <meta http-equiv="refresh" content="1">   -->

  <style>
    html {
      height: 100%;
    }

    body {
      min-height: 100%;
    }

    ul {
      list-style-type: none;
      margin: 0;
      padding: 0;
      overflow: hidden;
      background-color: #333;
    }

    li {
      float: left;
    }

    li a {
      display: block;
      color: white;
      text-align: center;
      padding: 14px 16px;
      text-decoration: none;
    }

    li a:hover:not(.active) {
      background-color: #111;
    }

    .active {
      background-color: #04AA6D;
    }
  </style>

</head>

<body>
  <ul>
    <li><a href="/">Home</a></li>
    <li><a class="active" href="/DebugTrace">Debug Trace</a></li>
    <li><a href="/Calibration">Calibration</a></li>
    <li><a href="/Settings">Settings</a></li>
    <li><a href="/About">About</a></li>
  </ul>


  <h1 style="background-color:#04AA6D;text-align: center;">Following are the Debug trace Live Output</h1>
  <div style="text-align: left;">
    <!-- below line shall be replace with required Debug info at run time. -->
    <h1>DO_NOT_REMOVE:-Custom_Add_Debug_String_Hear</h1>


  </div>
  <ul>
    <li><a href="/">Home</a></li>
    <li><a class="active" href="/DebugTrace">Debug Trace</a></li>
    <li><a href="/Calibration">Calibration</a></li>
    <li><a href="/Settings">Settings</a></li>
    <li><a href="/About">About</a></li>
  </ul>

  <script>
    // Add below Script to scrole to the bottum 
    //window.scrollTo(0, document.body.scrollHeight);
    function scrollToBottom() {
      window.scrollTo(0, document.body.scrollHeight);
    }
    history.scrollRestoration = "manual";
    window.onload = scrollToBottom;
  </script>

</body>

</html>
)=====";




#endif /* End of  Web_Server_Debug_Trace_html_H*/
