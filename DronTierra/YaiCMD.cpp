#include "YaiOS.h"


DynamicJsonBuffer dynJsonBuffer;

void YaiOS::executeCommand(String jsonCommand){
  JsonObject& root = dynJsonBuffer.parseObject(jsonCommand);
  String commandRoot = root["COMMAND"];
  String p1 = root["P1"];
  String p2 = root["P2"];
  String p3 = root["P3"];
  //Serial.print(commandRoot);
  int command = commandRoot.toInt();
  if(command == YAI_SERIAL_CMD_GET_IP){
    Serial.println("IP: "  + YaiOS::getClientIP());
    if(root["P1"] == "true"){
      Serial.println("MAC: "  + YaiOS::getMac());
    }    
  }
  
  if (command == ROVER_STOP){
    int tiempoStop = p2.toInt();
    Serial.println("Stop in " + p2);
    delay(tiempoStop);
    Serial.println("CALL RoverLink Stop NOW ");
  }

}
