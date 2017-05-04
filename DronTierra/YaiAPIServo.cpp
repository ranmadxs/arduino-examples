#include "YaiOS.h"
//TODO: Terminar DOC de Servos
//https://www.w3schools.com/code/tryit.asp?filename=FF03D1LDUA4N
//https://saeedalipoor.github.io/icono/
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm

String YaiOS::getAPIServo(){
  String indexHtml =
  "<!DOCTYPE html><html><head><style>table{border-collapse: collapse; width: 80%;}th, td{text-align: left; padding: 6px; font-family: Arial; font-size: 10px;}#rcorners{font-family: Arial; font-size: 12px;color: white; border-radius: 4px; padding-bottom: 5px; padding-top: 2px; width: 75px; height: 10px; valign: center; text-align: center; background: #0f6ab4;}#rcorners_serial{font-family: Arial; font-size: 12px;color: white; border-radius: 4px; padding-bottom: 5px; padding-top: 2px; width: 75px; height: 10px; valign: center; text-align: center; background: #F09A05;}.red-tr:nth-child(even){background-color: #f2f2f2}th{background-color: #4CAF50; color: white;}</style></head><body><h2>YaiOS Servo API</h2><hr/><h3>Servo Direction Enumeration</h3><table> <tr> <th>Name</th> <th>Value</th> <th>Description</th> </tr><tr> <td>SERVO_DIRECTION_VERTICAL</td><td>20001</td><td>Mover Servo Vertical</td></tr><tr> <td>SERVO_DIRECTION_HORIZONTAL</td><td>20002</td><td>Mover Servo Horizontal</td></tr><tr> <td>SERVO_DIRECTION_ALL</td><td>20003</td><td>Mover todos los servos en todas las direcciones (Horizontal y Vertical)</td></tr></table><h3>Servo Move Enumeration</h3><table> <tr> <th>Name</th> <th>Value</th> <th>Description</th> </tr><tr> <td>SERVO_CLOCKWISE</td><td>21002</td><td>Mover Servo en sentido Horario</td></tr><tr> <td>SERVO_COUNTER_CLOCKWISE</td><td>21001</td><td>Mover Servo en sentido antihorario</td></tr></table><hr/><h3>SERVO_ACTION_CONTINUOUS (ID: 200001)</h3><p id='rcorners'>GET / POST</p><p id='rcorners_serial'>SERIAL</p><p>Comando que nos entrega informaci&oacute;n del dispositivo de red.</p><table> <tr> <th>Parameter</th> <th>Value</th> <th>Description</th> </tr><tr> <td>P1</td><td>Component Type Enumeration</td><td>Indica el tipo de servo</td></tr><tr> <td>P2</td><td>int</td><td>Tiempo en [ms] en ejecutar la acci&oacute;n del servo</td></tr><tr> <td>P3</td><td>Servo Direction Enumeration</td><td>Indica el servo que ejecuta la acci&oacuten;</td></tr><tr> <td>P4</td><td>Servo Move Enumeration</td><td>Indica el sentido del movimiento del servo</td></tr><tr> <td>P5</td><td>int</td><td>Grados que recorre el servo cada 15 [ms]</td></tr><tr> <td>P6</td><td>None</td><td></td></tr><tr> <td>P7</td><td>None</td><td></td></tr></table><h3>Try it out!</h3><pre>\
curl -X GET --header \"Accept: application/json;charset=UTF-8\" \"http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=200001&P1=2001&P2=0&P3=20001&P4=21001&P5=2&P6=None&P7=None\"\
</pre><h4>Http Request</h4><pre>\
http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=200001&P1=2001&P2=0&P3=20001&P4=21001&P5=2&P6=None&P7=None\
</pre><h3>SERVO_ACTION_ANGLE (ID: 200002)</h3><p id='rcorners'>GET / POST</p><p id='rcorners_serial'>SERIAL</p><p>Comando que nos entrega informaci&oacute;n del dispositivo de red.</p><table> <tr> <th>Parameter</th> <th>Value</th> <th>Description</th> </tr><tr> <td>P1</td><td>Component Type Enumeration</td><td>Indica el tipo de servo</td></tr><tr> <td>P2</td><td>int</td><td>Tiempo en [ms] en ejecutar la acci&oacute;n del servo</td></tr><tr> <td>P3</td><td>Servo Direction Enumeration</td><td>Indica el servo que ejecuta la acci&oacuten;</td></tr><tr> <td>P4</td><td>int</td><td>&Aacute;ngulo que se mueve el servo</td></tr><tr> <td>P5</td><td>None</td><td></td></tr><tr> <td>P6</td><td>None</td><td></td></tr><tr> <td>P7</td><td>None</td><td></td></tr></table><h3>Try it out!</h3><pre>\
curl -X GET --header \"Accept: application/json;charset=UTF-8\" \"http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=200002&P1=2001&P2=0&P3=20003&P4=25&P5=None&P6=None&P7=None\"\
</pre><h4>Http Request</h4><pre>\
http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=200002&P1=2001&P2=0&P3=20003&P4=25&P5=2&P6=None&P7=None\
</pre><h3>SERVO_STOP (ID: 200003)</h3><p id='rcorners'>GET / POST</p><p id='rcorners_serial'>SERIAL</p><p>Comando que nos entrega informaci&oacute;n del dispositivo de red.</p><table> <tr> <th>Parameter</th> <th>Value</th> <th>Description</th> </tr><tr> <td>P1</td><td>Component Type Enumeration</td><td>Indica el tipo de servo</td></tr><tr> <td>P2</td><td>int</td><td>Tiempo en [ms] en ejecutar la acci&oacute;n del servo</td></tr><tr> <td>P3</td><td>Servo Direction Enumeration</td><td>Indica el servo que ejecuta la acci&oacuten;</td></tr><tr> <td>P4</td><td>None</td><td></td></tr><tr> <td>P5</td><td>None</td><td></td></tr><tr> <td>P6</td><td>None</td><td></td></tr><tr> <td>P7</td><td>None</td><td></td></tr></table><h3>Try it out!</h3><pre>\
curl -X GET --header \"Accept: application/json;charset=UTF-8\" \"http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=200003&P1=2001&P2=0&P3=20003&P4=None&P5=None&P6=None&P7=None\"\
</pre><h4>Http Request</h4><pre>\
http://"+ YaiOS::getClientIP()+"/cmd?COMMAND=200003&P1=2001&P2=0&P3=20003&P4=None&P5=None&P6=None&P7=None\
</pre><hr/><h3>Serial Json Message</h3><p>Examples:</p><h5>Stop all servos:</h5><pre>\
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
