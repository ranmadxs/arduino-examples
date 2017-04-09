#include "YaiOS.h"


DynamicJsonBuffer dynJsonBuffer;

void YaiOS::executeCommand(String jsonCommand){
  JsonObject& root = dynJsonBuffer.parseObject(jsonCommand);
  String commandRoot = root["COMMAND"];
  //Serial.print(commandRoot);
  int command = commandRoot.toInt();
  switch (command) {
    case YAI_SERIAL_CMD_GET_IP:
      Serial.println("IP: "  + YaiOS::getClientIP());
      if(root["P1"] == "true"){
        Serial.println("MAC: "  + YaiOS::getMac());
      }
    break;
    default:
      Serial.println("ERROR: Unknow command");
    break;
  }
}
