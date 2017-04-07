#include "YaiOS.h"

YaiOS::YaiOS(){}

//https://www.w3schools.com/code/tryit.asp?filename=FEDGLL9EGXWO
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm
//http://patorjk.com/software/taag/
//Font Name: Slant Relif
//Font Name: Small Slant


String YaiOS::getIndex(){
	String indexHtml = 
	"\
<html>\
<head>\
	<style type='text/css'>\
	.vinculos a {\
		font-family: Tahoma, Geneva, sans-serif;\
		font-size: 14px;\
		font-weight: 900;\
		text-decoration: none;\
		color: #666666;\
		border: 1px solid #FFFFFF;\	
	}\
	.vinculos a:hover {\
		font-family: Tahoma, Geneva, sans-serif;\
		font-size: 14px;\
		font-weight: 900;\
		background-color: #FFCCFF;\
		text-decoration: none;\
		color: #FF0000;\
		border: 1px solid #FF0000;\
	}\
	</style>\
<title>YAI-OS [Home]</title>\
</head>\
<body>\
<pre>\
";
indexHtml = indexHtml +
"__/\\\\\\________/\\\\\\_____/\\\\\\\\\\\\\\\\\\_____/\\\\\\\\\\\\\\\\\\\\\\_____________________/\\\\\\\\\\__________/\\\\\\\\\\\\\\\\\\\\\\___        " + '\r' +
" _\\///\\\\\\____/\\\\\\/____/\\\\\\\\\\\\\\\\\\\\\\\\\\__\\/////\\\\\\///____________________/\\\\\\///\\\\\\______/\\\\\\/////////\\\\\\_       " + '\r' +
"  ___\\///\\\\\\/\\\\\\/_____/\\\\\\/////////\\\\\\_____\\/\\\\\\_____________________/\\\\\\/__\\///\\\\\\___\\//\\\\\\______\\///__      " + '\r' +
"   _____\\///\\\\\\/______\\/\\\\\\_______\\/\\\\\\_____\\/\\\\\\______/\\\\\\\\\\\\\\\\\\\\\\__/\\\\\\______\\//\\\\\\___\\////\\\\\\_________     " + '\r' +
"    _______\\/\\\\\\_______\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\_____\\/\\\\\\_____\\///////////__\\/\\\\\\_______\\/\\\\\\______\\////\\\\\\______    " + '\r' +
"     _______\\/\\\\\\_______\\/\\\\\\/////////\\\\\\_____\\/\\\\\\___________________\\//\\\\\\______/\\\\\\__________\\////\\\\\\___   " + '\r' +
"      _______\\/\\\\\\_______\\/\\\\\\_______\\/\\\\\\_____\\/\\\\\\____________________\\///\\\\\\__/\\\\\\_____/\\\\\\______\\//\\\\\\__  " + '\r' +
"       _______\\/\\\\\\_______\\/\\\\\\_______\\/\\\\\\__/\\\\\\\\\\\\\\\\\\\\\\__________________\\///\\\\\\\\\\/_____\\///\\\\\\\\\\\\\\\\\\\\\\/___ " + '\r' +
"        _______\\///________\\///________\\///__\\///////////_____________________\\/////_________\\///////////_____" + '\r' +
"</pre>";

String htmlVerion =
"<pre>\
 _   __    ___   ___ \r\                          
| | / ____/ _ \\ <  / \r\
| |/ /___/ // _ / /  \r\
|___/    \\___(_/_/   \r\
</pre>\
";
String htmlContent =
"\
	<div class='vinculos'>\
    <ul>\
	   <li><a href='/api'>API Reference </a></li>\
     <li><a href='/roverJoystick'>Rover</a></li>\
    </ul>\
	</div>\
</body>\
</html>\
	";
  indexHtml = indexHtml + htmlVerion + htmlContent;
	return indexHtml;
}