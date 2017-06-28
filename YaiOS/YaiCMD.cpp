#include "YaiOS.h"
#include "YaiCommons.h"
#include "YaiCommunicator.h"


//https://www.w3schools.com/code/tryit.asp?filename=FFHYS1V0HNCL
String YaiOS::executeCommand(String pipelineCommand[], int totalCmds, YaiCommunicator yaiCommunicator){
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
		executeCommand(yaiCommand, yaiCommunicator);
	}
	jsonReturn = "\"TOTAL_EXE\":"+String(totalExecuteds);
	return jsonReturn;
}

YaiCommand YaiOS::executeCommand(YaiCommand yaiCommand, YaiCommunicator yaiCommunicator){
	YaiCommand yaiResponse;
	YaiCommand yaiResponseSvc;

	yaiResponse.p1 = String(STATUS_NOK);

	boolean propagate = false;
	String strPropagate = "false";
	String content = "Command not found";
	String resultStr = "NOK";
	String responseSvc;
	String jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
	boolean getLogs = false;
	String jsonContent = "\""+ String(YAI_COMMAND_TYPE_NONE) + "\"";

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
			jsonContent = "\"" + yaiParseFile.content + "\"";
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
			jsonContent = content;
		}
  
		//Comandos que se propagan sin delay
		if(command == OBSTACLE_READER){
			resultStr = "OK";
			propagate = true;
			yaiCommand.address = I2C_CLIENT_YAI_MOTOR;
			yaiResponse = yaiCommunicator.propagateCommand(yaiCommand);
		}

		//Comandos que se propagan con delay
		if (command == SERVO_STOP){
			resultStr = "OK";
			propagate = true;
			int tiempoStop = yaiCommand.p2.toInt();

			yaiCommand.address = I2C_CLIENT_YAI_SERVO;

			delay(tiempoStop);
			yaiResponse = yaiCommunicator.propagateCommand(yaiCommand);
		}

		if (command == SERVO_ACTION_CONTINUOUS){
			resultStr = "OK";
			propagate = true;
			int tiempoStop = yaiCommand.p2.toInt();

			yaiResponse.address = I2C_CLIENT_YAI_SERVO;
			delay(tiempoStop);
			yaiResponse = yaiCommunicator.propagateCommand(yaiCommand);
		}

		if (command == SERVO_ACTION_ANGLE){
			resultStr = "OK";
			propagate = true;
			int tiempoStop = yaiCommand.p2.toInt();

			yaiResponse.address = I2C_CLIENT_YAI_SERVO;
			delay(tiempoStop);
			yaiResponse = yaiCommunicator.propagateCommand(yaiCommand);
		}
		if(command == ROVER_MOVE_MANUAL_BODY ){
			resultStr = "OK";
			propagate = true;
			int tiempoStop = yaiCommand.p2.toInt();

			yaiCommand.address = I2C_CLIENT_YAI_MOTOR;
			delay(tiempoStop);
			yaiResponse = yaiCommunicator.propagateCommand(yaiCommand);
		}

		if(command == ROVER_STOP){
			resultStr = "OK";
			propagate = true;
			int tiempoStop = yaiCommand.p2.toInt();

			yaiCommand.address = I2C_CLIENT_YAI_MOTOR;
			delay(tiempoStop);
			yaiResponse = yaiCommunicator.propagateCommand(yaiCommand);
			if(yaiResponse.p1 == String(STATUS_OK)){
				yaiResponse.json = "{\"TIME:\":" + yaiCommand.p2 + ", \"ROVER\":\"STOP\"}";
			}else{
				yaiResponse.json = "\"" + yaiResponse.p2 + "\"";
			}
		}

		if(command == LASER_ACTION ){
			propagate = true;
			int tiempoStop = yaiCommand.p2.toInt();

			yaiCommand.address = I2C_CLIENT_YAI_MOTOR;
			delay(tiempoStop);
			yaiResponse = yaiCommunicator.propagateCommand(yaiCommand);
			yaiUtil.string2YaiRespCommand(yaiResponse);
			resultStr = yaiResponse.p1;
			if(yaiResponse.p1 == String(STATUS_OK)){
				yaiResponse.json = "{\"LASER_STATUS\": \""+yaiResponse.p1+"\", \"TIME\": " + yaiCommand.p2 + "}";
			}else{
				yaiResponse.json = "\"" + yaiResponse.p2 + "\"";
			}
		}

	}
	if(propagate){
		//Serial.println(yaiCommand.message);
		/*
		yaiResponse.command = yaiCommand.command;
		yaiResponse.type = yaiCommand.type;
		yaiResponse.message = yaiCommand.message;
		yaiResponse.address = yaiCommand.address;
		yaiResponse.p1 = yaiCommand.p1;
		yaiResponse.p2 = yaiCommand.p2;
		yaiResponse.p3 = yaiCommand.p3;
		yaiResponse.p4 = yaiCommand.p4;
		yaiResponse.p5 = yaiCommand.p5;
		yaiResponse.p6 = yaiCommand.p6;
		yaiResponse.p7 = yaiCommand.p7;
		*/
		logDebug("Propagando: " + yaiCommand.message);
		strPropagate = "true";
		//Momentaneo dejo esto aca luego lo muevo a cada caso
		jsonContent = yaiResponse.json;
	}


	jsonResult = "{\"RESULT\":\""+resultStr+"\", \"PROPAGATE\": "+strPropagate+", \"CONTENT\": "
			+jsonContent+", \"TYPE\":\""+yaiCommand.type+"\"}";
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
