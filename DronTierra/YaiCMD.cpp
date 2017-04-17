#include "YaiOS.h"
#include <ArduinoJson.h>
//#include "RoverLink.h"


DynamicJsonBuffer dynJsonBuffer;

String YaiOS::executeCommand(String jsonCommand){
  JsonObject& root = dynJsonBuffer.parseObject(jsonCommand);
  String commandRoot = root["COMMAND"];
  boolean respCommand = false;
  String p1 = root["P1"];
  String p2 = root["P2"];
  String p3 = root["P3"];
  String content = "{";
  String resultStr = "OK";
  //Serial.print(commandRoot);
  int command = commandRoot.toInt();
  if(command == YAI_SERIAL_CMD_GET_IP){
	respCommand = true;    
    content += "\"IP\":\""+ YaiOS::getClientIP()+"\"";
    if(root["P1"] == "true"){
      content += ", \"MAC\":\""+ YaiOS::getMac()+"\"";
    }    
  }
  
  if (command == ROVER_STOP){
	respCommand = true;
    int tiempoStop = p2.toInt();
    Serial.println("Stop in " + p2);
    delay(tiempoStop);
    Serial.println("CALL RoverLink Stop NOW ");
    roverLn.motorStop(p3.toInt());
  }

  if (command == ROVER_MOVE_MANUAL_BODY){
	  respCommand = true;
  }

  if(!respCommand){
    resultStr = "NOK";
    content = "\"Command not found\"";
  }
  content += "}";
  String jsonResult = "{\"result\":\""+resultStr+"\", \"content\":"+content+"}";
  Serial.println(jsonResult);
  return jsonResult;
}
