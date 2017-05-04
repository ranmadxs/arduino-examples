#include "YaiOS.h"
//TODO: Terminar DOC de Servos
//https://www.w3schools.com/code/tryit.asp?filename=FEY9MS5IGZ4S
// ----> Revisar esta https://www.w3schools.com/code/tryit.asp?filename=FEY9MS5IGZ4S
//https://saeedalipoor.github.io/icono/
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm

String YaiOS::getAPI(){
  String indexHtml =
"<!DOCTYPE html><html><head><style> table{border-collapse:collapse;width:80%}th,td{text-align:left;padding:6px;font-family:Arial;font-size:10px}#rcorners{font-family:Arial;font-size:12px;color:white;border-radius:4px;padding-bottom:5px;padding-top:2px;width:75px;height:10px;valign:center;text-align:center;background:#0f6ab4}#rcorners_serial{font-family:Arial;font-size:12px;color:white;border-radius:4px;padding-bottom:5px;padding-top:2px;width:75px;height:10px;valign:center;text-align:center;background:#F09A05}.red-tr:nth-child(even){background-color:#f2f2f2}th{background-color:#4CAF50;color:white}</style></head><body><h2>YaiOS API</h2><hr/><h3>Component Type Enumeration</h3><table><tr><th>Name</th><th>Value</th><th>Description</th></tr><tr><td>ROVER_TYPE_2WD</td><td>1001</td><td>Tipo Rover con dos ruedas de tracci&oacute;n y una de gu&iacute;a sin tracci&oacute;n</td></tr><tr><td>SERVO_TYPE_SG90</td><td>2001</td><td>Tipo servo SG90, 130&deg;</td></tr></table><h3>Rover Move Enumeration</h3><table><tr><th>Name</th><th>Value</th><th>Description</th></tr><tr><td>ROVER_BODY_MOVE_TYPE_LEFT</td><td>10001</td><td>Mover Izquierda</td></tr><tr><td>ROVER_BODY_MOVE_TYPE_RIGHT</td><td>10002</td><td>Mover Derecha</td></tr><tr><td>ROVER_BODY_MOVE_TYPE_FORWARD</td><td>10003</td><td>Mover Adelante</td></tr><tr><td>ROVER_BODY_MOVE_TYPE_BACK</td><td>10004</td><td>Mover Atr&aacute;s</td></tr></table><h3>Servo Direction Enumeration</h3><table><tr><th>Name</th><th>Value</th><th>Description</th></tr><tr><td>SERVO_DIRECTION_VERTICAL</td><td>20001</td><td>Mover Servo Vertical</td></tr><tr><td>SERVO_DIRECTION_HORIZONTAL</td><td>20002</td><td>Mover Servo Horizontal</td></tr><tr><td>SERVO_DIRECTION_ALL</td><td>20003</td><td>Mover todos los servos en todas las direcciones (Horizontal y Vertical)</td></tr></table><h3>Servo Move Enumeration</h3><table><tr><th>Name</th><th>Value</th><th>Description</th></tr><tr><td>SERVO_CLOCKWISE</td><td>21002</td><td>Mover Servo en sentido Horario</td></tr><tr><td>SERVO_COUNTER_CLOCKWISE</td><td>21001</td><td>Mover Servo en sentido antihorario</td></tr></table><hr/><h3>ROVER_MOVE_MANUAL_BODY (ID: 100001)</h3><p id='rcorners'>GET / POST</p><p id='rcorners_serial'>SERIAL</p><p>Comando para efectuar un movimiento del Rover, tomando como referencia la direcci&oacute;n que tenga en el momento de enviar el comando.</p><table><tr><th>Parameter</th><th>Value</th><th>Description</th></tr><tr><td>P1</td><td>Component Type Enumeration</td><td>Indica el tipo de Rover</td></tr><tr><td>P2</td><td>int</td><td>Tiempo en que se detiene en milisegundos, 0 se detiene inmediato</td></tr><tr><td>P3</td><td>int</td><td>Indica la distancia que recorre</td></tr><tr><td>P4</td><td>Rover Move Enumeration</td><td>Indica sentido del movimiento</td></tr><tr><td>P5</td><td>None</td><td></td></tr><tr><td>P6</td><td>None</td><td></td></tr><tr><td>P7</td><td>None</td><td></td></tr></table><h3>Try it out!</h3><pre>\
curl -X GET --header \"Accept: application/json;charset=UTF-8\" \"http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=100001&P1=1001&P2=0&P3=0&P4=10003&P5=None&P6=None&P7=None\"\
</pre><h4>Http Request</h4><pre>\
http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=100001&P1=1001&P2=0&P3=0&P4=10003&P5=None&P6=None&P7=None\
</pre><h3>ROVER_STOP (ID: 100002)</h3><p id='rcorners'>GET / POST</p><p id='rcorners_serial'>SERIAL</p><p>Detiene el Rover</p><table><tr><th>Parameter</th><th>Value</th><th>Description</th></tr><tr><td>P1</td><td>Component Type Enumeration</td><td>Indica el tipo de Rover</td></tr><tr><td>P2</td><td>int</td><td>Tiempo en que se detiene en milisegundos, 0 se detiene inmediato</td></tr><tr><td>P3</td><td>int</td><td>Indica la distancia que recorre antes de detenerse</td></tr><tr><td>P4</td><td>None</td><td></td></tr><tr><td>P5</td><td>None</td><td></td></tr><tr><td>P6</td><td>None</td><td></td></tr><tr><td>P7</td><td>None</td><td></td></tr></table><h3>Try it out!</h3><pre>\
curl -X GET --header \"Accept: application/json;charset=UTF-8\" \"http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=100002&P1=1001&P2=0&P3=None&P4=None&P5=None&P6=None&P7=None\"\
</pre><h4>Http Request</h4><pre>\
http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=100002&P1=1001&P2=0&P3=None&P4=None&P5=None&P6=None&P7=None\
</pre><h3>ROVER_SERIAL_CMD_GET_IP (ID: 100003)</h3><p id='rcorners'>GET / POST</p><p id='rcorners_serial'>SERIAL</p><p>Comando que nos entrega informaci&oacute;n del dispositivo de red.</p><table><tr><th>Parameter</th><th>Value</th><th>Description</th></tr><tr><td>P1</td><td>boolean</td><td>Si se encuentra en true devuelve la MAC</td></tr><tr><td>P2</td><td>None</td><td></td></tr><tr><td>P3</td><td>None</td><td></td></tr><tr><td>P4</td><td>None</td><td></td></tr><tr><td>P5</td><td>None</td><td></td></tr><tr><td>P6</td><td>None</td><td></td></tr><tr><td>P7</td><td>None</td><td></td></tr></table><h3>Try it out!</h3><pre>\
curl -X GET --header \"Accept: application/json;charset=UTF-8\" \"http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=100003&P1=false&P2=None&P3=None&P4=None&P5=None&P6=None&P7=None\"\
</pre><h4>Http Request</h4><pre>\
http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=100003&P1=false&P2=None&P3=None&P4=None&P5=None&P6=None&P7=None\
</pre><h3>LASER_ACTION (ID: 100004)</h3><p id='rcorners'>GET / POST</p><p id='rcorners_serial'>SERIAL</p><p>Comando que nos entrega informaci&oacute;n del dispositivo de red.</p><table><tr><th>Parameter</th><th>Value</th><th>Description</th></tr><tr><td>P1</td><td>boolean</td><td>Indica el estado del laser, true=activo, false=inactivo</td></tr><tr><td>P2</td><td>int</td><td>Tiempo en [ms] en ejecutar la acci&oacute;n del laser</td></tr><tr><td>P3</td><td>None</td><td></td></tr><tr><td>P4</td><td>None</td><td></td></tr><tr><td>P5</td><td>None</td><td></td></tr><tr><td>P6</td><td>None</td><td></td></tr><tr><td>P7</td><td>None</td><td></td></tr></table><h3>Try it out!</h3><pre>\
curl -X GET --header \"Accept: application/json;charset=UTF-8\" \"http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=100004&P1=true&P2=0&P3=None&P4=None&P5=None&P6=None&P7=None\"\
</pre><h4>Http Request</h4><pre>\
http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=100004&P1=true&P2=0&P3=None&P4=None&P5=None&P6=None&P7=None\
</pre><h3>SERVO_ACTION_CONTINUOUS (ID: 200001)</h3><p id='rcorners'>GET / POST</p><p id='rcorners_serial'>SERIAL</p><p>Comando que nos entrega informaci&oacute;n del dispositivo de red.</p><table><tr><th>Parameter</th><th>Value</th><th>Description</th></tr><tr><td>P1</td><td>Component Type Enumeration</td><td>Indica el tipo de servo</td></tr><tr><td>P2</td><td>int</td><td>Tiempo en [ms] en ejecutar la acci&oacute;n del servo</td></tr><tr><td>P3</td><td>Servo Direction Enumeration</td><td>Indica el servo que ejecuta la acci&oacuten;</td></tr><tr><td>P4</td><td>Servo Move Enumeration</td><td>Indica el sentido del movimiento del servo</td></tr><tr><td>P5</td><td>int</td><td>Grados que recorre el servo cada 15 [ms]</td></tr><tr><td>P6</td><td>None</td><td></td></tr><tr><td>P7</td><td>None</td><td></td></tr></table><h3>Try it out!</h3><pre>\
curl -X GET --header \"Accept: application/json;charset=UTF-8\" \"http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=200001&P1=2001&P2=0&P3=20001&P4=21001&P5=2&P6=None&P7=None\"\
</pre><h4>Http Request</h4><pre>\
http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=200001&P1=2001&P2=0&P3=20001&P4=21001&P5=2&P6=None&P7=None\
</pre><h3>SERVO_ACTION_ANGLE (ID: 200002)</h3><p id='rcorners'>GET / POST</p><p id='rcorners_serial'>SERIAL</p><p>Comando que nos entrega informaci&oacute;n del dispositivo de red.</p><table><tr><th>Parameter</th><th>Value</th><th>Description</th></tr><tr><td>P1</td><td>Component Type Enumeration</td><td>Indica el tipo de servo</td></tr><tr><td>P2</td><td>int</td><td>Tiempo en [ms] en ejecutar la acci&oacute;n del servo</td></tr><tr><td>P3</td><td>Servo Direction Enumeration</td><td>Indica el servo que ejecuta la acci&oacuten;</td></tr><tr><td>P4</td><td>int</td><td>&Aacute;ngulo que se mueve el servo</td></tr><tr><td>P5</td><td>None</td><td></td></tr><tr><td>P6</td><td>None</td><td></td></tr><tr><td>P7</td><td>None</td><td></td></tr></table><h3>Try it out!</h3><pre>\
curl -X GET --header \"Accept: application/json;charset=UTF-8\" \"http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=200002&P1=2001&P2=0&P3=20003&P4=25&P5=None&P6=None&P7=None\"\
</pre><h4>Http Request</h4><pre>\
http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=200002&P1=2001&P2=0&P3=20003&P4=25&P5=2&P6=None&P7=None\
</pre><h3>SERVO_STOP (ID: 200003)</h3><p id='rcorners'>GET / POST</p><p id='rcorners_serial'>SERIAL</p><p>Comando que nos entrega informaci&oacute;n del dispositivo de red.</p><table><tr><th>Parameter</th><th>Value</th><th>Description</th></tr><tr><td>P1</td><td>Component Type Enumeration</td><td>Indica el tipo de servo</td></tr><tr><td>P2</td><td>int</td><td>Tiempo en [ms] en ejecutar la acci&oacute;n del servo</td></tr><tr><td>P3</td><td>Servo Direction Enumeration</td><td>Indica el servo que ejecuta la acci&oacuten;</td></tr><tr><td>P4</td><td>None</td><td></td></tr><tr><td>P5</td><td>None</td><td></td></tr><tr><td>P6</td><td>None</td><td></td></tr><tr><td>P7</td><td>None</td><td></td></tr></table><h3>Try it out!</h3><pre>\
curl -X GET --header \"Accept: application/json;charset=UTF-8\" \"http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=200003&P1=2001&P2=0&P3=20003&P4=None&P5=None&P6=None&P7=None\"\
</pre><h4>Http Request</h4><pre>\
http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=200003&P1=2001&P2=0&P3=20003&P4=None&P5=None&P6=None&P7=None\
</pre><hr /><h3>Serial Json Message</h3><pre>\
{\
  'COMMAND':'COMMAND_ID', \
  'P1':'VALUE', \
  'P2':'VALUE', \
  'P3':'VALUE', \
  'P4':'VALUE', \
  'P5':'VALUE', \
  'P6':'VALUE', \
  'P7':'VALUE' \
}\
</pre><p>Examples:</p><h5>ROVER_SERIAL_CMD_GET_IP:</h5><pre>\
{'COMMAND':'100003', 'P1':'false', 'P2':'None', 'P3':'None', 'P4':'None', \
  'P5':'None', 'P6':'None', 'P7':'None'}\
</pre><h5>Stop all servos:</h5><pre>\
{'COMMAND':'200003', 'P1':'2001', 'P2':'0', 'P3':'20003', 'P4':'None',   'P5':'None', 'P6':'None', 'P7':'None'}\
</pre><h5>Servo move (horario y antihorario):</h5><pre>\
{'COMMAND':'200001', 'P1':'2001', 'P2':'0', 'P3':'20001', 'P4':'21002',   'P5':'20', 'P6':'None', 'P7':'None'}\
</pre><pre>\
{'COMMAND':'200001', 'P1':'2001', 'P2':'0', 'P3':'20002', 'P4':'21002',   'P5':'20', 'P6':'None', 'P7':'None'}\
</pre><h5>Servo move angle:</h5><pre>\
{'COMMAND':'200002', 'P1':'2001', 'P2':'0', 'P3':'20003', 'P4':'25',   'P5':'None', 'P6':'None', 'P7':'None'}\
</pre></body></html>\
";
  return indexHtml;
}

