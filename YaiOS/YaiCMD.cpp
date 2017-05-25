#include "YaiOS.h"

//https://www.w3schools.com/code/tryit.asp?filename=FFHYS1V0HNCL
String YaiOS::executeCommand(String pipelineCommand[], int totalCmds){
	String jsonReturn = "";
	logInfo("YAI:executeCommand");
	int totalExecuteds = 0;
	for (int i = 0; i < totalCmds; i++){
		logDebug(pipelineCommand[i]);
		totalExecuteds++;
		String root[8];
		yaiUtil.getElementRoot(pipelineCommand[i], root);
		logDebug("CMD:" + root[0] + ", P1:" + root[1]);
    executeCommand(pipelineCommand[i]);
	}
	jsonReturn = "\"TOTAL_EXE\":"+String(totalExecuteds);
	return jsonReturn;
}
//TODO: Refactor del tiempo se debe factorizar
String YaiOS::executeCommand(String strCommand){

  String jsonResult = strCommand;
  String inputCommand;
  boolean propagate = false;
  logInfo("<< " + strCommand);
  if(strCommand.indexOf("RESULT") > 0){
    jsonResult = inputCommand;
  }  

  String root[8];
  yaiUtil.getElementRoot(strCommand, root);
  String responseSvc = "";
  boolean respCommand = false;
  String commandRoot = root[0];
  String p1 = root[1];
  String p2 = root[2];
  String p3 = root[3];
  String p4 = root[4];
  String p5 = root[5];
  String p6 = root[6];
  String p7 = root[7];
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
	  jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
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
    if(p1 == "true"){
      content += ", \"MAC\":\""+ YaiOS::getMac()+"\"";
    }    
    content += "}";
    jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
  }
  
  if (command == ROVER_MOVE_MANUAL_BODY || command == ROVER_STOP || command == LASER_ACTION || command == OBSTACLE_READER){
	respCommand = true;
    propagate = true;
  }

  if(!respCommand){
    resultStr = "NOK";
    content = "\"Command not found\"";
  }
  if(propagate){
    Serial.println(strCommand);
    logDebug("Propagando: " + strCommand);
    jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":\"PROPAGATE\"}";
  }else{
    Serial.println(jsonResult);
    logInfo(">> " + jsonResult);
  }
  return jsonResult;
}

