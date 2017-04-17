#include "YaiOS.h"

String YaiOS::getJS(){
  String html = 
  "\
  function mouseDown(move) { \
    document.getElementById('actionDiv').innerHTML = move;\
  }\
  \
  function mouseUp() {\
    document.getElementById('actionDiv').innerHTML = 'STOP';\
  }\
  ";
  return html;
}
