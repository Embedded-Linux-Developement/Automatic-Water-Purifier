
/*****************************************************************************************************
Header file  Web_Server_Calibration_html.h
Description:- Simple header file to store Html templates for Calibration Page

*******************************************************************************************************/

#ifndef Web_Server_Calibration_html_H
#define Web_Server_Calibration_html_H

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

const char Html_Head_Calibration[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<title>Water Purifier Calibration</title>
<!-- Add 1 Sec Auto refresh -->
<!-- <meta http-equiv="refresh" content="1">   -->

<head>
  <style>
    /***************************For Button*************************************/
    .Small_btn {
      border: none;
      color: white;
      padding: 8px 8px;
      font-size: 12px;
      cursor: pointer;
      border-radius: 8px;

    }

    .btn {
      border: none;
      color: white;
      padding: 14px 28px;
      font-size: 16px;
      cursor: pointer;
      border-radius: 8px;

    }

    .Green {
      background-color: #04AA6D;
    }

    /* Green */
    .Green:hover {
      background-color: #46a049;
    }

    .Blue {
      background-color: #2196F3;
    }

    /* Blue */
    .Blue:hover {
      background: #0b7dda;
    }

    .Amber {
      background-color: #ff9800;
    }

    /* Amber */
    .Amber:hover {
      background: #e68a00;
    }

    .Red {
      background-color: #f44336;
    }

    /* Red */
    .Red:hover {
      background: #da190b;
    }

    .Gray {
      background-color: #e7e7e7;
      color: black;
    }

    /* Gray */
    .Gray:hover {
      background: #ddd;
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
    <li><a href="/DebugTrace">Debug Trace</a></li>
    <li><a class="active" href="/Calibration">Calibration</a></li>
    <li><a href="/Settings">Settings</a></li>
    <li><a href="/About">About</a></li>
    <li><a href="/update">OAT</a></li>
  </ul>

  <h2 style="text-align: center;"> Calibration TBD </h2>

  <button onclick="window.location.href='/Perform_ReStart';" class="btn Green">Click to Re-Start the System</button>


</body>

</html>
)=====";




#endif /* End of  Web_Server_Calibration_html_H*/
