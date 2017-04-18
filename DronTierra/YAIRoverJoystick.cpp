#include "YaiOS.h"
#include "YaiConstants.h"

//https://www.w3schools.com/code/tryit.asp?filename=FEQ6NAHD1Y2M
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm

String YaiOS::getRoverJoystick(){
  String html = 
  "\ 
		  <html>\
		  <head>\
		  <script type='application/javascript' src='../yai.js'></script>\
		  <style type='text/css'>\
		  .contenedorTableDiv {\
		      display: table;\
		      border: 0px solid #000;\
		      width: 333px;\
		      text-align: center;\
		      margin: 0 auto;\
		  }\
		  .contenidos {\
		      display: table-row;\
		  }\
		  .columna {\
		      display: table-cell;\
		      border: 0px solid #000;\
		      vertical-align: middle;\
		      padding: 10px;\
		  }\
		  \
		  body {\
		    text-align: center;\
		    margin: 6em 0 0 0;\
		    padding: 0;\
		  }\
		  \
		  div {\
		    display: inline-block;\
		    vertical-align: middle;\
		  }\
		  \
		  a {\
		    display: inline-block;\
		    border-radius: 50%;\
		  }\
		  \
		  \
		  a:hover .center, a:hover .left, a:hover .top, a:hover .bottom, a:hover .right{\
		    border: 0.5em solid #e74c3c;\
		  }\
		  \
		  a:hover .left:after, a:hover .top:after, a:hover .bottom:after, a:hover .right:after {\
		    border-top: 0.5em solid #e74c3c;\
		    border-right: 0.5em solid #e74c3c;\
		  }\
		  \
		  a:hover .center:after {\
		    border-top: 0.5em solid #e74c3c;\
		    border-right: 0.5em solid #e74c3c;\
		    border-bottom: 0.5em solid #e74c3c;\
		    border-left: 0.5em solid #e74c3c;  \
		  }\
		  \
		  .left {\
		    display: inline-block;\
		    //background-color: blue;\
		    width: 4em;\
		    height: 4em;\
		    border: 0.5em solid #333;\
		    border-radius: 50%;\
		    margin-right: 1.5em;\
		  }\
		  \
		  .left:after {\
		    content: '';\
		  	display: inline-block;\
		    margin-top: 1.05em;\
		    margin-left: 0.6em;\
		    width: 1.4em;\
		    height: 1.4em;\
		    border-top: 0.5em solid #333;\
		    border-right: 0.5em solid #333;\
		    -moz-transform: rotate(-135deg);\
		    -webkit-transform: rotate(-135deg);\
		    transform: rotate(-135deg);\
		  }\
		  \
		  .center {\
		    display: inline-block;\
		    width: 4em;\
		    height: 4em;\
		    border: 0.5em solid #333;\
		    border-radius: 50%;\
		  }\
		  \
		  .center:after {\
		    content: '';\
		    display: inline-block;\
		    margin-top: 0.7em;\
		    width: 1.4em;\
		    height: 1.4em;\
		    border-top: 0.5em solid #333;\
		    border-right: 0.5em solid #333;\
		    border-bottom: 0.5em solid #333;\
		    border-left: 0.5em solid #333;\
		  }\
		  \
		  .top {\
		    display: inline-block;\
		    width: 4em;\
		    height: 4em;\
		    border: 0.5em solid #333;\
		    border-radius: 50%;\
		    margin-right: 0.75em;\
		  }\
		  \
		  .top:after {\
		    content: '';\
		  	display: inline-block;\
		    margin-top: 1.4em;\
		    width: 1.4em;\
		    height: 1.4em;\
		    border-top: 0.5em solid #333;\
		    border-right: 0.5em solid #333;\
		    -moz-transform: rotate(-45deg);\
		    -webkit-transform: rotate(-45deg);\
		    transform: rotate(-45deg);\
		  }\
		  \
		  .bottom {\
		    display: inline-block;\
		    width: 4em;\
		    height: 4em;\
		    border: 0.5em solid #333;\
		    border-radius: 50%;\
		    margin-left: 0.75em;\
		  }\
		  \
		  .bottom:after {\
		    content: '';\
		  	display: inline-block;\
		    margin-top: 0.6em;\
		    width: 1.4em;\
		    height: 1.4em;\
		    border-top: 0.5em solid #333;\
		    border-right: 0.5em solid #333;\
		    -moz-transform: rotate(135deg);\
		    -webkit-transform: rotate(135deg);\
		    transform: rotate(135deg);\
		  }\
		  \
		  .right {\
		    display: inline-block;\
		    width: 4em;\
		    height: 4em;\
		    border: 0.5em solid #333;\
		    border-radius: 50%;\
		    margin-left: 1.5em;\
		  }\
		  \
		  .right:after {\
		    content: '';\
		    display: inline-block;\
		    margin-top: 1.05em;\
		    margin-left: -0.6em;\
		    width: 1.4em;\
		    height: 1.4em;\
		    border-top: 0.5em solid #333;\
		    border-right: 0.5em solid #333;\
		    -moz-transform: rotate(45deg);\
		    -webkit-transform: rotate(45deg);\
		    transform: rotate(45deg);\
		  }		\
		  </style>\
		  \
		  </head>\
		  \
		  <body>\
		  \
		  <center>\
		  \
		  <div class='contenedorTableDiv'>\
		      <div class='contenidos'>\
		          <div class='columna'></div>\
		          <div class='columna'>\
		            <a href='javascript:void(0);'>\
		              <span class='top' onclick=\"actionMove('"+String(ROVER_BODY_MOVE_TYPE_FORWARD)+"', '"+String(ROVER_TYPE_2WD)+"')\"></span>\
		            </a>        \
		          </div>\
		          <div class='columna'></div>\
		      </div>\
		      <div class='contenidos'>\
		          <div class='columna'>\
		            <a href='javascript:void(0);'>\
		              <span class='left' onclick=\"actionMove('"+String(ROVER_BODY_MOVE_TYPE_LEFT)+"', '"+String(ROVER_TYPE_2WD)+"')\"></span>\
		            </a>        \
		          </div>\
		          <div class='columna'>\
		            <a href='javascript:void(0);'>\
		              <span class='center' onclick=\"actionStop('"+String(ROVER_TYPE_2WD)+"')\"></span>\
		            </a>                \
		          </div>\
		          <div class='columna'>\
		            <a href='javascript:void(0);'>\
		              <span class='right' onclick=\"actionMove('"+String(ROVER_BODY_MOVE_TYPE_RIGHT)+"', '"+String(ROVER_TYPE_2WD)+"')\"></span>\
		            </a>        \
		          </div>\
		      </div>\
		      <div class='contenidos'>\
		          <div class='columna'></div>\
		          <div class='columna'>\
		            <a href='javascript:void(0);'>\
		              <span class='bottom' onclick=\"actionMove('"+String(ROVER_BODY_MOVE_TYPE_BACK)+"', '"+String(ROVER_TYPE_2WD)+"')\"></span>\
		            </a>        \
		          </div>\
		          <div class='columna'></div>\
		      </div>\
		  </div>\
		  </center>\
		  </body>\
		  </html>\
   ";
  return html;
}
