#include "YaiOS.h"

//https://www.w3schools.com/code/tryit.asp?filename=FFHYS1V0HNCL
String YaiOS::executeCommand(String pipelineCommand[], int totalCmds){
	String jsonReturn = "";
	logInfo("YAI:executeCommand");
	int totalExecuteds = 0;
	for (int i = 0; i < totalCmds; i++){
		logDebug(pipelineCommand[i]);
		totalExecuteds++;
		YaiCommand yaiCommand;
		yaiCommand.type = String(YAI_COMMAND_TYPE_SERIAL);
		yaiCommand.message = pipelineCommand[i];
		yaiUtil.string2Serial(yaiCommand);
		logDebug("CMD:" + yaiCommand.command + ", P1:" + yaiCommand.p1);
		executeCommand(yaiCommand);
	}
	jsonReturn = "\"TOTAL_EXE\":"+String(totalExecuteds);
	return jsonReturn;
}
//TODO: Refactor del tiempo se debe factorizar
String YaiOS::executeCommand(YaiCommand yaiCommand){
	boolean propagate = false;
	String content = "Command not found";
	String resultStr = "NOK";
	String responseSvc;
	//Serial.println("<< " + yaiCommand.message);
	String jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
	if(yaiCommand.type == String(YAI_COMMAND_TYPE_RESULT)){
		jsonResult = yaiCommand.message;
	}

	if(yaiCommand.command != ""){
		int command = yaiCommand.command.toInt();

		if(command == SERVO_ACTION_ANGLE){
			propagate = false;
			resultStr = "OK";
			int tiempoStop = yaiCommand.p2.toInt();
			delay(tiempoStop);
			responseSvc = servoLn.servoAngle(yaiCommand.p1.toInt(), yaiCommand.p3.toInt(), yaiCommand.p4.toInt());
			content = "{\"time:\":" + yaiCommand.p2 + ", \"servo\":"+responseSvc+"}";
			jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
		}
  
		if(command == SERVO_ACTION_CONTINUOUS){
			propagate = false;
			resultStr = "OK";
			int tiempoStop = yaiCommand.p2.toInt();
			delay(tiempoStop);
			responseSvc = servoLn.servoMove(yaiCommand.p1.toInt(), yaiCommand.p3.toInt(), yaiCommand.p4.toInt(), yaiCommand.p5.toInt());
			content = "{\"time:\":" + yaiCommand.p2 + ", \"servo\":"+responseSvc+"}";
			jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
		}

		if(command == SERVO_STOP){
			propagate = false;
			resultStr = "OK";
			int tiempoStop = yaiCommand.p2.toInt();
			delay(tiempoStop);
			responseSvc = servoLn.servoStop(yaiCommand.p1.toInt(), yaiCommand.p3.toInt());
			content = "{\"time:\":" + yaiCommand.p2 + ", \"servo\":"+responseSvc+"}";
			jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
		}

		if(command == YAI_SERIAL_CMD_GET_IP){
			propagate = false;
			resultStr = "OK";
			content = "{\"IP\":\""+ YaiOS::getClientIP()+"\"";
			if(yaiCommand.p1 == "true"){
				content += ", \"MAC\":\""+ YaiOS::getMac()+"\"";
			}
			content += "}";
			jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
		}
  
		if (command == ROVER_MOVE_MANUAL_BODY || command == ROVER_STOP || command == LASER_ACTION || command == OBSTACLE_READER){
			propagate = true;
		}
	}
	if(propagate){
		Serial.println(yaiCommand.message);
		logDebug("Propagando: " + yaiCommand.message);
		jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":\"PROPAGATE\"}";
	}else{
		Serial.println(jsonResult);
		logInfo(">> " + jsonResult);
	}
	return jsonResult;
}

