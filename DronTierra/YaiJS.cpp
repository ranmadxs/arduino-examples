#include "YaiOS.h"
#include "YaiConstants.h"

String YaiOS::getJS(){
  String html = 
  "\
  var ipClient = '"+ YaiOS::getClientIP()+"';\  
  var ROVER_STOP = '"+ ROVER_STOP +"';\
  var ROVER_MOVE_MANUAL_BODY = '"+ ROVER_MOVE_MANUAL_BODY +"';\
  function actionMove(move, roverType) { \
    alert('Action Move:'+move);\
    var xhttp = new XMLHttpRequest();\
	xhttp.open('GET', 'http://'+ipClient+'/cmd?COMMAND='+ROVER_MOVE_MANUAL_BODY+'&P1='+roverType+'&P2=0&P3=0&P4='+move+'&P5=None&P6=None&P7=None', false);\
    xhttp.setRequestHeader('Content-type', 'text/html');\
	xhttp.send();\
	alert(xhttp.responseText);\
  }\
  function actionStop(roverType) { \
    alert('action STOP');\
    var xhttp = new XMLHttpRequest();\
	xhttp.open('GET', 'http://'+ipClient+'/cmd?COMMAND='+ROVER_STOP+'&P1='+roverType+'&P2=0&P3=0&P4=None&P5=None&P6=None&P7=None', false);\
    xhttp.setRequestHeader('Content-type', 'text/html');\
	xhttp.send();\
	alert(xhttp.responseText);\
  }\
  ";
  return html;
}
