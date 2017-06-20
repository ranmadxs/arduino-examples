#include "YaiOS.h"
#include <Wire.h>
#include "YaiCommunicator.h"


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
		yaiUtil.string2YaiCommand(yaiCommand);
		logDebug("CMD:" + yaiCommand.command + ", P1:" + yaiCommand.p1);
		executeCommand(yaiCommand);
	}
	jsonReturn = "\"TOTAL_EXE\":"+String(totalExecuteds);
	return jsonReturn;
}

YaiCommand YaiOS::executeCommand(YaiCommand yaiCommand){
	YaiCommand yaiResponse;
	YaiCommand yaiResponseSvc;

	yaiResponse.p1 = String(STATUS_NOK);

	boolean propagate = false;
	String content = "Command not found";
	String resultStr = "NOK";
	String responseSvc;
	String jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
	boolean getLogs = false;


	if(yaiCommand.command != "" && yaiCommand.type != ""){
		int command = yaiCommand.command.toInt();

		if(command == YAI_GET_CURRENT_LOG){
			yaiResponse.type = String(YAI_COMMAND_TYPE_NONE);
			propagate = false;
			yaiResponse.p1 = String(STATUS_OK);
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
			yaiResponse.type = String(YAI_COMMAND_TYPE_RESULT);
			logDebug("Ejecutando: " + yaiCommand.message);
			yaiResponse.p1 = String(STATUS_OK);
			propagate = false;
			resultStr = "OK";
			content = "{\"CLIENT_IP\":\""+ YaiOS::getClientIP()+"\"";
			yaiResponse.p2 = YaiOS::getClientIP();
			if(yaiCommand.p1 == "true"){
				content += ", \"MAC\":\""+ YaiOS::getMac()+"\"";
				yaiResponse.p3 = YaiOS::getMac();
				content += ", \"DNS_IP\":\""+ YaiOS::getServerIP()+"\"";
				yaiResponse.p4 = YaiOS::getServerIP();
				content += ", \"DNS_SSID\":\""+ YaiOS::getServerSsid()+"\"";
				yaiResponse.p5 = YaiOS::getServerSsid();
			}
			content += "}";
			jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
		}
  
		//Comandos que se propagan sin delay
		if(command == OBSTACLE_READER){
			resultStr = "OK";
			propagate = true;
			yaiResponse.address = I2C_CLIENT_YAI_MOTOR;
		}

		//Comandos que se propagan con delay
		if (command == SERVO_STOP || command == SERVO_ACTION_CONTINUOUS || command == SERVO_ACTION_ANGLE){
			resultStr = "OK";
			propagate = true;
			int tiempoStop = yaiCommand.p2.toInt();

			yaiResponse.address = I2C_CLIENT_YAI_SERVO;
			delay(tiempoStop);
		}

		if(command == ROVER_MOVE_MANUAL_BODY || command == ROVER_STOP || command == LASER_ACTION ){
			resultStr = "OK";
			propagate = true;
			int tiempoStop = yaiCommand.p2.toInt();

			yaiResponse.address = I2C_CLIENT_YAI_MOTOR;
			delay(tiempoStop);
		}


	}
	if(propagate){
		//Serial.println(yaiCommand.message);
		yaiResponse.command = yaiCommand.command;
		yaiResponse.type = yaiCommand.type;
		yaiResponse.message = yaiCommand.message;
		yaiResponse.p1 = yaiCommand.p1;
		yaiResponse.p2 = yaiCommand.p2;
		yaiResponse.p3 = yaiCommand.p3;
		yaiResponse.p4 = yaiCommand.p4;
		yaiResponse.p5 = yaiCommand.p5;
		yaiResponse.p6 = yaiCommand.p6;
		yaiResponse.p7 = yaiCommand.p7;
		logDebug("Propagando: " + yaiCommand.message);
		jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":\"PROPAGATE\", \"TYPE\":"+yaiCommand.type+"}";
	}

	yaiResponse.propagate = propagate;
	yaiResponse.json = jsonResult;

	return yaiResponse;
}

/*
YaiCommand YaiOS::propagateCommand(YaiCommand yaiCommand){
	YaiCommand yaiCommandProp;
	yaiCommandProp.p1 = String(STATUS_NOK);
	if(yaiCommand.type == String(YAI_COMMAND_TYPE_SERIAL)){
		yaiCommandProp.p1 = String(STATUS_OK);
		Serial.println(yaiCommand.message);
	}
	if(yaiCommand.type == String(YAI_COMMAND_TYPE_I2C)){
		yaiCommandProp.p1 = String(STATUS_OK);
		//yaiCommunicator.sendI2CCommand(yaiCommand.message, yaiCommand.address);
	}
	return yaiCommandProp;
}
*/
