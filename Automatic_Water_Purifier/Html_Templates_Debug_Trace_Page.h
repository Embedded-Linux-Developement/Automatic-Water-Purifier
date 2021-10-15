
/*****************************************************************************************************
Header file  Html_Templates.h
Description:- Simple header file to store Html templates 

*******************************************************************************************************/

#ifndef Html_Templates_H
#define Html_Templates_H

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
E-mail:- Jerrymbc@gmail.com
Date  :- 15 Sep 2021
version:- V2.0.1

*******************************************************************************************************/


/* Define Header part*/
const char Html_Templates_Debug_Trace_Page_Header[] = "<!DOCTYPE html> \n \
<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1252\">  \n \
   <title>Payyampallil Water purifier Trace Debug</title>  \n \
   <!-- Add 1 Sec Auto refresh -->  \n \
   <meta http-equiv=\"refresh\" content=\"1\">   \n \
 </head>  \n \
 <body>  \n \
   <h1 style=\"background-color:Green;text-align: center;\">Live Debug trace for Water purifier</h1>   \n \
   <div style=\"text-align: center;\"> ";



const char Html_Templates_Debug_Trace_Page_Footer[] = "</div> \n </body> \n\
</html>";







#endif /* End of  Html_Templates_H */
