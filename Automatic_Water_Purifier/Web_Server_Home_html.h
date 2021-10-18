
/*****************************************************************************************************
Header file  Web_Server_Home_html.h
Description:- Simple header file to store Html templates for Home Page

*******************************************************************************************************/

#ifndef Web_Server_Home_html_H
#define Web_Server_Home_html_H

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

const char Html_Head_Home[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Water Purifier</title>
<!-- Add 1 Sec Auto refresh -->
<!-- <meta http-equiv="refresh" content="1">   -->

<head>
  <style>
    /************************For Window Splitting******************************/
    * {
      box-sizing: border-box;
    }

    /* Create two equal columns that floats next to each other */
    .column {
      float: left;
      width: 50%;
      padding: 10px;
      height: 90%;
      /* Should be removed. Only for demonstration */
    }

    /* Clear floats after the columns */
    .row:after {
      content: "";
      display: table;
      clear: both;
    }


    /***************************For Box type Button****************************/
    .SmallBox_btn {
      border: 2px solid black;
      background-color: white;
      color: black;
      padding: 4px 8px;
      font-size: 12px;
      border-radius: 8px;
    }


    .Box_btn {
      border: 2px solid black;
      background-color: white;
      color: black;
      padding: 14px 28px;
      font-size: 16px;
      border-radius: 8px;
    }

    /* Green */
    .Green_Box {
      border-color: #04AA6D;
      color: green;
    }

    .Green_Box:hover {
      background-color: #04AA6D;
      color: white;
    }

    /* Blue */
    .Blue_Box {
      border-color: #2196F3;
      color: dodgerblue;
    }

    .Blue_Box:hover {
      background: #2196F3;
      color: white;
    }

    /* Orange */
    .Amber_Box {
      border-color: #ff9800;
      color: orange;
    }

    .Amber_Box:hover {
      background: #ff9800;
      color: white;
    }

    /* Red */
    .Red_Box {
      border-color: #f44336;
      color: red;
    }

    .Red_Box:hover {
      background: #f44336;
      color: white;
    }

    /* Gray */
    .Gray_Box {
      border-color: #e7e7e7;
      color: black;
    }

    .Gray_Box:hover {
      background: #e7e7e7;
    }

    /***************************For Button*************************************/
    .Small_btn {
      border: none;
      color: white;
      padding: 8px 8px;
      font-size: 12px;
      border-radius: 8px;

    }

    .btn {
      border: none;
      color: white;
      padding: 14px 28px;
      font-size: 16px;
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

    /***************************For Navigation Bar*************************************/
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
    <li><a class="active" href="/">Home</a></li>
    <li><a href="/DebugTrace">Debug Trace</a></li>
    <li><a href="/Calibration">Calibration</a></li>
    <li><a href="/Settings">Settings</a></li>
    <li><a href="/About">About</a></li>
    <li><a href="/update">OAT</a></li>
  </ul>
  <div style="text-align: center;">
    <h1> Welcome to Payyampallil Water Purifier </h1>

    <h2>Over All Water Purifier Status:-</h2>
    <!--ID_1_Start--> <button class="btn Green">Normal And OK</button>
  </div>
  <div class="row">
    <div class="column">
      <h2 style="text-align: center;"> All Generic Status</h2>

      <h3>Current Tank Status:-</h3>
      <!--ID_2_Start--> <button class="Small_btn Green">Tank Full</button>

      <h3>Current Water Flow Status:-</h3>
      <!--ID_3_Start--> <button class="Small_btn Green">Flow is Normal</button>

      <h3>Current Water Flow Rate:-</h3>
      <!--ID_4_Start--> <button class="SmallBox_btn Green_Box">4.5LpM</button>

      <h3>Recentely Filtered Water Volume:-</h3>
      <!--ID_5_Start--> <button class="SmallBox_btn Green_Box">10L</button>

      <h3>Total Filtered Water Volume:-</h3>
      <!--ID_6_Start--> <button class="SmallBox_btn Green_Box">30L</button>

      <h3>UV lamp Status:-</h3>
      <!--ID_7_Start--> <button class="Small_btn Green">Working OK</button>
    </div>

    <div class="column">
      <h2 style="text-align: center;"> All Sensores Raw Data</h2>

      <h3>UV Lamp LDR Sensor Raw Values:-</h3>
      <!--ID_30_Start--> <button class="SmallBox_btn Gray_Box">UV Sensor 1 = 2500, UV Sensor 2 = 2500</button>

      <h3>High Presure Sensor Raw Value:-</h3>
      <!--ID_31_Start--><button class="Small_btn Green">ON</button>
      <!--ID_32_Start--> <button class="SmallBox_btn Gray_Box"> Raw Value =2500</button>

      <h3>Float Sensor Raw Value:-</h3>
      <!--ID_33_Start--><button class="Small_btn Green">ON</button>
      <!--ID_34_Start--> <button class="SmallBox_btn Gray_Box"> Raw Value =2500</button>

      <h3>Water flow Sensor Raw Value in Tick:-</h3>
      <!--ID_35_Start--> <button class="SmallBox_btn Gray_Box"> Tick Value =2500</button>


    </div>
  </div>


  <div style="text-align: left;">
    <h2>Any Specific Action Required from User:- </h2>
    <!--ID_100_Start--><p>Nothing Specific For Now...</p>
  </div>
  <ul>
    <li><a class="active" href="/">Home</a></li>
    <li><a href="/DebugTrace">Debug Trace</a></li>
    <li><a href="/Calibration">Calibration</a></li>
    <li><a href="/Settings">Settings</a></li>
    <li><a href="/About">About</a></li>
    <li><a href="/update">OAT</a></li>
  </ul>
</body>

</html>

)=====";




#endif /* End of  Web_Server_Home_html_H*/
