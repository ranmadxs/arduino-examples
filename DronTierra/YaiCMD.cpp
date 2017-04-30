#include "YaiOS.h"
#include <ArduinoJson.h>
//#include "RoverLink.h"


DynamicJsonBuffer dynJsonBuffer;

//TODO: Refactor del tiempo se debe factorizar
String YaiOS::executeCommand(String jsonCommand){
  JsonObject& root = dynJsonBuffer.parseObject(jsonCommand);
  String inputCommand;
  root.printTo(inputCommand);
  Serial.println("<< " + inputCommand);

  String commandRoot = root["COMMAND"];
  String responseSvc = "";
  boolean respCommand = false;
  String p1 = root["P1"];
  String p2 = root["P2"];
  String p3 = root["P3"];
  String p4 = root["P4"];
  String p5 = root["P5"];
  String p6 = root["P6"];
  String p7 = root["P7"];
  String content = "";
  String resultStr = "OK";
  //Serial.print(commandRoot);
  int command = commandRoot.toInt();
  
  if(command == SERVO_ACTION_ANGLE){
	  respCommand = true;
	  int tiempoStop = p2.toInt();
	  delay(tiempoStop);
	  responseSvc = servoLn.servoAngle(p1.toInt(), p3.toInt(), p4.toInt());
	  content += "{\"time:\":" + p2 + ", \"servo\":"+responseSvc+"}";
  }
  
  if(command == SERVO_ACTION_CONTINUOUS){
	  respCommand = true;
	  int tiempoStop = p2.toInt();
	  delay(tiempoStop);
	  responseSvc = servoLn.servoMove(p1.toInt(), p3.toInt(), p4.toInt(), p5.toInt());
	  content += "{\"time:\":" + p2 + ", \"servo\":"+responseSvc+"}";
  }

  if(command == SERVO_STOP){
	  respCommand = true;
	  int tiempoStop = p2.toInt();
	  delay(tiempoStop);
	  responseSvc = servoLn.servoStop(p1.toInt(), p3.toInt());
	  content += "{\"time:\":" + p2 + ", \"servo\":"+responseSvc+"}";
  }

  if(command == YAI_SERIAL_CMD_GET_IP){
	respCommand = true;    
    content += "{\"IP\":\""+ YaiOS::getClientIP()+"\"";
    if(root["P1"] == "true"){
      content += ", \"MAC\":\""+ YaiOS::getMac()+"\"";
    }    
    content += "}";
  }
  if (command == LASER_ACTION){
    respCommand = true; 
    int tiempoStop = p2.toInt();
    content += "{\"laserStatus\": "+p1+", \"time\": " + p2 + "}";
    delay(tiempoStop);
    boolean activar = false;
    if(p1 == "true"){
      activar = true;
    }
    roverLn.laser(activar);
  }
  
  if (command == ROVER_STOP){
	respCommand = true;
    int tiempoStop = p2.toInt();
    delay(tiempoStop);    
    roverLn.motorStop(p1.toInt());
    content += "{\"time:\":" + p2 + ", \"rover\":\"STOP\"}";
  }

  if (command == ROVER_MOVE_MANUAL_BODY){
	  respCommand = true;
	  int tiempoStop = p2.toInt();
	  delay(tiempoStop);	  
	  responseSvc = roverLn.motorMove(p1.toInt(), p4.toInt());
	  content += "{\"time:\":" + p2 + ", \"rover\":\""+responseSvc+"\"}";
  }

  if(!respCommand){
    resultStr = "NOK";
    content = "\"Command not found\"";
  }
  String jsonResult = "{\"result\":\""+resultStr+"\", \"content\":"+content+"}";
  Serial.println(">> " + jsonResult);
  return jsonResult;
}
