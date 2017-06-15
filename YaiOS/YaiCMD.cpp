#include "YaiOS.h"
#include <Wire.h>
//#include "YaiCommunicator.h"


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
	boolean getLogs = false;


	if(yaiCommand.command != "" && yaiCommand.type != ""){
		int command = yaiCommand.command.toInt();

		if(command == YAI_GET_CURRENT_LOG){
			propagate = false;
			getLogs = true;
			boolean printSerial = false;
			if(yaiCommand.p3 == "true"){
				printSerial = true;
			}
			int lineInit = yaiCommand.p1.toInt();
			int lineEnd = yaiCommand.p2.toInt();
			YaiParseFile yaiParseFile;
			yaiParseFile = YaiOS::getFileLogLines(lineInit, lineEnd, printSerial);
			jsonResult = yaiParseFile.content;
		}

		if(command == YAI_SERIAL_CMD_GET_IP){
			propagate = false;
			resultStr = "OK";
			content = "{\"CLIENT_IP\":\""+ YaiOS::getClientIP()+"\"";
			if(yaiCommand.p1 == "true"){
				content += ", \"MAC\":\""+ YaiOS::getMac()+"\"";
				content += ", \"DNS_IP\":\""+ YaiOS::getServerIP()+"\"";
				content += ", \"DNS_SSID\":\""+ YaiOS::getServerSsid()+"\"";
			}
			content += "}";
			jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
		}
  
		//Comandos que se propagan sin delay
		if(command == OBSTACLE_READER){
			resultStr = "OK";
			propagate = true;

			//if(yaiCommand.type == String("YAI_COMMAND_TYPE_I2C")){
			//	propagate = false;
			//	yaiCommunicator.sendI2CCommand(yaiCommand.message, I2C_CLIENT_YAI_MOTOR);
			//}
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
		if(!getLogs){
			Serial.println(jsonResult);
			logInfo(">> " + jsonResult);
		}
	}
	return jsonResult;
}

