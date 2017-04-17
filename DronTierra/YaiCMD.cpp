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
  String p4 = root["P4"];
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
    //Serial.println("Type " + p1);
    Serial.println("Stop in " + p2);
    delay(tiempoStop);
    content += "\"Stop in " + p2 + "\"";
    roverLn.motorStop(p1.toInt());
  }

  if (command == ROVER_MOVE_MANUAL_BODY){
	  respCommand = true;
	  int tiempoStop = p2.toInt();
	  //Serial.println("Type " + p1);
	  Serial.println("moveIn in " + p2);
	  //Serial.println("to " + p4);
	  delay(tiempoStop);
	  content += "\"Move in " + p2 + "\"";
	  roverLn.motorMove(p1.toInt(), p4.toInt());
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
