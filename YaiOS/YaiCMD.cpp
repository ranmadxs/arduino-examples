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

String YaiOS::executeCommand(YaiCommand yaiCommand){
	boolean propagate = false;
	String content = "Command not found";
	String resultStr = "NOK";
	String responseSvc;
	String jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";

	if(yaiCommand.command != ""){
		int command = yaiCommand.command.toInt();

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
  
		//Comandos que se propagan sin delay
		if(command == OBSTACLE_READER){
			resultStr = "OK";
			propagate = true;
		}

		//Comandos que se propagan con delay
		if (command == ROVER_MOVE_MANUAL_BODY || command == ROVER_STOP ||
				command == LASER_ACTION ||
				command == SERVO_STOP || command == SERVO_ACTION_CONTINUOUS || command == SERVO_ACTION_ANGLE){
			resultStr = "OK";
			propagate = true;
			int tiempoStop = yaiCommand.p2.toInt();
			delay(tiempoStop);
		}
	}
	if(propagate){
		Serial.println(yaiCommand.message);
		logDebug("Propagando: " + yaiCommand.message);
		jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":\"PROPAGATE\", \"TYPE\":"+yaiCommand.type+"}";
	}else{
		Serial.println(jsonResult);
		logInfo(">> " + jsonResult);
	}
	return jsonResult;
}

