#include "YaiOS.h"
#include <ArduinoJson.h>
//#include "RoverLink.h"


DynamicJsonBuffer dynJsonBuffer;

String YaiOS::executeCommand(String jsonCommand){
  JsonObject& root = dynJsonBuffer.parseObject(jsonCommand);
  String commandRoot = root["COMMAND"];
  String moveResponse = "";
  boolean respCommand = false;
  String p1 = root["P1"];
  String p2 = root["P2"];
  String p3 = root["P3"];
  String p4 = root["P4"];
  String content = "";
  String resultStr = "OK";
  //Serial.print(commandRoot);
  int command = commandRoot.toInt();
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
    content += "{\"time:\":" + p2 + ", \"move\":\"STOP\"}";
  }

  if (command == ROVER_MOVE_MANUAL_BODY){
	  respCommand = true;
	  int tiempoStop = p2.toInt();
	  delay(tiempoStop);	  
	  moveResponse = roverLn.motorMove(p1.toInt(), p4.toInt());    
    content += "{\"time:\":" + p2 + ", \"move\":\""+moveResponse+"\"}";
  }

  if(!respCommand){
    resultStr = "NOK";
    content = "\"Command not found\"";
  }
  String jsonResult = "{\"result\":\""+resultStr+"\", \"content\":"+content+"}";
  Serial.println(jsonResult);
  return jsonResult;
}
