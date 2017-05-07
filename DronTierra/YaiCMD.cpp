#include "YaiOS.h"
#include <ArduinoJson.h>
//#include "RoverLink.h"


DynamicJsonBuffer dynJsonBuffer;

//TODO: Refactor del tiempo se debe factorizar
String YaiOS::executeCommand(String jsonCommand){

  String jsonResult = jsonCommand;

  JsonObject& root = dynJsonBuffer.parseObject(jsonCommand);
  String inputCommand;
  boolean propagate = false;
  root.printTo(inputCommand); 
  if(root.containsKey("COMMAND")){
    propagate = true;
    Serial.println("<< " + inputCommand);
  }
  if(root.containsKey("RESULT")){
    propagate = false;
    jsonResult = inputCommand;
  }  
  
   
  boolean printJson = true;
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
    propagate = false;
	  respCommand = true;
	  int tiempoStop = p2.toInt();
	  delay(tiempoStop);
	  responseSvc = servoLn.servoAngle(p1.toInt(), p3.toInt(), p4.toInt());
	  content += "{\"time:\":" + p2 + ", \"servo\":"+responseSvc+"}";
  }
  
  if(command == SERVO_ACTION_CONTINUOUS){
    propagate = false;
	  respCommand = true;
	  int tiempoStop = p2.toInt();
	  delay(tiempoStop);
	  responseSvc = servoLn.servoMove(p1.toInt(), p3.toInt(), p4.toInt(), p5.toInt());
	  content += "{\"time:\":" + p2 + ", \"servo\":"+responseSvc+"}";
    jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
  }

  if(command == SERVO_STOP){
    propagate = false;
	  respCommand = true;
	  int tiempoStop = p2.toInt();
	  delay(tiempoStop);
	  responseSvc = servoLn.servoStop(p1.toInt(), p3.toInt());
	  content += "{\"time:\":" + p2 + ", \"servo\":"+responseSvc+"}";
    jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
  }

  if(command == YAI_SERIAL_CMD_GET_IP){
    propagate = false;
	  respCommand = true;    
    content += "{\"IP\":\""+ YaiOS::getClientIP()+"\"";
    if(root["P1"] == "true"){
      content += ", \"MAC\":\""+ YaiOS::getMac()+"\"";
    }    
    content += "}";
    jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
  }
  
  if (command == ROVER_MOVE_MANUAL_BODY || command == ROVER_STOP || command == LASER_ACTION){
	  respCommand = true;
    propagate = true;
  }

  if(!respCommand){
    resultStr = "NOK";
    content = "\"Command not found\"";
  }
  String csvCommand = commandRoot+","+p1+","+p2+","+p3+","+p4+","+p5+","+p6+","+p7;  
  if(propagate){
    Serial.println(csvCommand);
  }else{
    Serial.println(jsonResult);
  }
  return jsonResult;
}

