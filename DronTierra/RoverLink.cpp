#include "RoverLink.h"

//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm

RoverLink::RoverLink(){}

String RoverLink::getIndex(){
  //char indexHtml[800];
  String indexHtml = 
"<!DOCTYPE html>\
<html>\
<head>\
<style>\
table {\
    border-collapse: collapse;\
    width: 80%;\
}\
\
th, td {\
    text-align: left;\
    padding: 6px;\
    font-family: Arial;\
    font-size: 10px;\
}\
\
#rcorners {\
    font-family: Arial;\
    font-size: 12px;\
 color: white;\
    border-radius: 4px;\
    padding-bottom: 5px;     \
    padding-top: 2px;   \
    width: 75px;\
    height: 10px;  \
    valign: center;\
    text-align: center;\
    background: #0f6ab4;\
}\
\
#rcorners_serial {\
    font-family: Arial;\
    font-size: 12px;\
  color: white;\
    border-radius: 4px;\
    padding-bottom: 5px;     \
    padding-top: 2px;   \
    width: 75px;\
    height: 10px;  \
    valign: center;\
    text-align: center;\
    background: #F09A05;\
}\
\
.red-\
\
tr:nth-child(even){background-color: #f2f2f2}\
\
th {\
    background-color: #4CAF50;\
    color: white;\
}\
</style>\
</head>\
<body>\
\
<h2>Rover Link API</h2>\
<hr/>\
<h3>Rover Type Enumeration</h3>\
<table>\
  <tr>\
    <th>Name</th>\
    <th>Value</th>\
    <th>Description</th>\
  </tr>\
  <tr>\
    <td>ROVER_TYPE_2WD</td>\
    <td>1001</td>\
    <td>Tipo Rover con dos ruedas de tracci&oacute;n y una de gu&iacute;a sin tracci&oacute;n</td>\
  </tr>\
</table>\
<h3>Rover Body Move Type Enumeration</h3>\
<table>\
  <tr>\
    <th>Name</th>\
    <th>Value</th>\
    <th>Description</th>\
  </tr>\
  <tr>\
    <td>ROVER_BODY_MOVE_TYPE_LEFT</td>\
    <td>2001</td>\
    <td>Mover Izquierda</td>\
  </tr>\
  <tr>\
    <td>ROVER_BODY_MOVE_TYPE_RIGHT</td>\
    <td>2002</td>\
    <td>Mover Derecha</td>\
  </tr>\
  <tr>\
    <td>ROVER_BODY_MOVE_TYPE_FORWARD</td>\
    <td>2003</td>\
    <td>Mover Adelante</td>\
  </tr>\
  <tr>\
    <td>ROVER_BODY_MOVE_TYPE_BACK</td>\
    <td>2004</td>\
    <td>Mover Atrás</td>\
  </tr>  \
</table>\
<h3>Rover Serial Enumeration</h3>\
<table>\
  <tr>\
    <th>Name</th>\
    <th>Value</th>\
    <th>Description</th>\
  </tr>\
  <tr>\
    <td>ROVER_SERIAL_CMD_GET_IP</td>\
    <td>3001</td>\
    <td>Obtiene la ip del Rover por comunicaci&oacute;n serial</td>\
  </tr>\
</table>\
<hr/>\
<h3>ROVER_MOVE_MANUAL_BODY</h3>\
<p id='rcorners'>GET / POST</p>\
<p id='rcorners_serial'>SERIAL</p>\
<p>Comando para efectuar un movimiento del Rover, tomando como referencia la direcci&oacute;n que tenga en el momento de enviar el comando.</p>\
<table>\
  <tr>\
    <th>Parameter</th>\
    <th>Value</th>\
    <th>Description</th>\
  </tr>\
  <tr>\
    <td>P1</td>\
    <td>ROVER_TYPE_ENUM</td>\
    <td>Indica el tipo de Rover</td>\
  </tr>\
  <tr>\
    <td>P2</td>\
    <td>int</td>\
    <td>Tiempo en que se detiene, 0 se detiene inmediato</td>\
  </tr>  \
  <tr>\
    <td>P3</td>\
    <td>int</td>\
    <td>Indica la distancia que recorre</td>\
  </tr>  \
  <tr>\
    <td>P4</td>\
    <td>ROVER_MOVE_BODY_ENUM</td>\
    <td>Indica sentido del movimiento</td>\
  </tr>  \
  <tr>\
    <td>P5</td>\
    <td>None</td>\
    <td></td>\
  </tr>  \
  <tr>\
    <td>P6</td>\
    <td>None</td>\
    <td></td>\
  </tr> \
  <tr>\
    <td>P7</td>\
    <td>None</td>\
    <td></td>\
  </tr>   \
</table>\
<hr/>\
<h3>ROVER_STOP</h3>\
<p id='rcorners'>GET / POST</p>\
<p id='rcorners_serial'>SERIAL</p>\
<p>Detiene el Rover</p>\
<table>\
  <tr>\
    <th>Parameter</th>\
    <th>Value</th>\
    <th>Description</th>\
  </tr>\
  <tr>\
    <td>P1</td>\
    <td>ROVER_TYPE_ENUM</td>\
    <td>Indica el tipo de Rover</td>\
  </tr>\
  <tr>\
    <td>P2</td>\
    <td>int</td>\
    <td>Tiempo en que se detiene, 0 se detiene inmediato</td>\
  </tr>  \
  <tr>\
    <td>P3</td>\
    <td>int</td>\
    <td>Indica la distancia que recorre</td>\
  </tr>  \
  <tr>\
    <td>P4</td>\
    <td>None</td>\
    <td></td>\
  </tr>  \
  <tr>\
    <td>P5</td>\
    <td>None</td>\
    <td></td>\
  </tr>  \
  <tr>\
    <td>P6</td>\
    <td>None</td>\
    <td></td>\
  </tr> \
  <tr>\
    <td>P7</td>\
    <td>None</td>\
    <td></td>\
  </tr>   \
</table>\
</body>\
</html>\
";
  return indexHtml;
}

