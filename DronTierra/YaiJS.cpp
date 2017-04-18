#include "YaiOS.h"
#include "YaiConstants.h"

String YaiOS::getJS(){
  String html = 
  "\
  var ipClient = '"+ YaiOS::getClientIP()+"';\  
  function actionMove(move) { \
    alert('Move:'+move);\
    var xhttp = new XMLHttpRequest();\
	xhttp.open('GET', 'http://'+ipClient+'/cmd?COMMAND=100001&P1=1001&P2=0&P3=0&P4=2003&P5=None&P6=None&P7=None', false);\
    xhttp.setRequestHeader('Content-type', 'text/html');\
	xhttp.send();\
	alert('XDDDD');\
	alert(xhttp.responseText);\
  }\
  ";
  return html;
}
