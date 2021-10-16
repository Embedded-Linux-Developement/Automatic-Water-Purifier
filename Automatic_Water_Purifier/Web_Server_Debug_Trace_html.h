
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
 

   <h1 style="background-color:Green;text-align: center;">Following are the Debug trace Live Output</h1>  
   <div style="text-align: left;"> 



<h2 style="text-align: center;"> Debug Trace Error Hadling </h2><p style="color:red">

  No Queue Overflow detected Yet... <br>
  No Queue Timeout detected Yet... <br>

</p><hr style="border: 1px dashed Green">

<h2 style="text-align: center;"> Debug Trave Messages </h2> <p> 

00000055143: Index = 104 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000055643: Index = 105 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000056143: Index = 106 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000056643: Index = 107 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000057143: Index = 108 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000057643: Index = 109 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000058143: Index = 110 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000058643: Index = 111 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000059143: Index = 112 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000059643: Index = 113 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000060143: Index = 114 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000060643: Index = 115 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000061143: Index = 116 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000061643: Index = 117 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000062143: Index = 118 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>
00000062643: Index = 119 Hello I am here, To Test the debug Trace printing_,To Test the debug T<br>


</p><hr style="border: 1px dashed blue">


</div> 

</body></html>
)=====";




#endif /* End of  Web_Server_Debug_Trace_html_H*/
