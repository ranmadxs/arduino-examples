#include <Arduino.h>
#include "ServoLink.h"
#include "YaiCommons.h"
#include <string.h>
#include <Thread.h>
#include <ThreadController.h>

ServoLink servoLink;

YaiUtil yaiUtil;

int TIME_INTERVAL_SERVO = 15;
Thread threadServoRun;
ThreadController threadController;

void callBackServoMovement(){
	servoLink.callBackMovement();
}

YaiCommand executeCommand(YaiCommand yaiCommand){
	YaiCommand yaiResponse;
	YaiCommand yaiResponseSvc;
	yaiResponse.type = String(YAI_COMMAND_TYPE_RESULT);
	yaiResponse.p1 = String(STATUS_NOK);
	yaiResponse.p2 = String(YAI_COMMAND_TYPE_NONE);
	yaiResponse.p3 = String(YAI_COMMAND_TYPE_NONE);
	yaiResponse.p4 = String(YAI_COMMAND_TYPE_NONE);
	//String content = "Command not found";
	//String resultStr = "NOK";
	//String responseSvc;
	String commandRoot = yaiCommand.command;
	//String jsonResult = "{\""+String(YAI_COMMAND_TYPE_RESULT)+"\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
	//boolean respCommand = false;
	//Serial.println("Cmd:" + commandRoot);
	if (commandRoot == String(SERVO_ACTION_ANGLE)){
		//resultStr = "OK";
		yaiResponse.p1 = String(STATUS_OK);
		//respCommand = true;
		yaiResponseSvc = servoLink.servoAngle(yaiCommand.p1.toInt(), yaiCommand.p3.toInt(), yaiCommand.p4.toInt());
		yaiResponse.p2 = yaiResponseSvc.p2;
		yaiResponse.p3 = yaiResponseSvc.p3;
		//content = "{\"TIME:\":" + yaiCommand.p2 + ", \"SERVO\":"+responseSvc+"}";
	}
	if (commandRoot == String(SERVO_ACTION_CONTINUOUS)){
		//resultStr = "OK";
		yaiResponse.p1 = String(STATUS_OK);
		//respCommand = true;
		yaiResponseSvc = servoLink.servoMove(yaiCommand.p1.toInt(), yaiCommand.p3.toInt(), yaiCommand.p4.toInt(), yaiCommand.p5.toInt());
		yaiResponse.p2 = yaiResponseSvc.p2;
		//content = "{\"TIME:\":" + yaiCommand.p2 + ", \"SERVO\":"+responseSvc+"}";
	}
	if(commandRoot == String(SERVO_STOP)){
		//resultStr = "OK";
		yaiResponse.p1 = String(STATUS_OK);
		//respCommand = true;
		yaiResponseSvc = servoLink.servoStop(yaiCommand.p1.toInt(), yaiCommand.p3.toInt());
		yaiResponse.p2 = yaiResponseSvc.p2;
		//content = "{\"TIME:\":" + yaiCommand.p2 + ", \"SERVO\":"+responseSvc+"}";
	}
	/*
	if(respCommand){
		jsonResult = "{\""+String(YAI_COMMAND_TYPE_RESULT)+"\"";
		Serial.print(jsonResult);
		jsonResult += ":\""+resultStr+"\", \"CONTENT\":";
	    Serial.print(":\""+resultStr+"\", \"CONTENT\":");
	    jsonResult += content + "}";
	    Serial.println(content + "}");
	}
	*/
	return yaiResponse;
}

void serialController(){
	YaiCommand yaiCommand;
	YaiCommand yaiResCmd;
	yaiCommand = yaiUtil.commandSerialFilter();
	if(yaiCommand.execute){
		yaiResCmd = executeCommand(yaiCommand);
		if(yaiResCmd.p1 == String(STATUS_OK)){
			Serial.println(yaiResCmd.type + "," + yaiResCmd.p1 + "," + yaiResCmd.p2 + "," + yaiResCmd.p3 + "," + yaiResCmd.p4);
		}

	}
}

void setup() {
	Serial.begin(9600);
	Serial.println("Yai servo inicializado");
	Serial.println("Serial port ready");
	threadServoRun.onRun(callBackServoMovement);
	threadServoRun.setInterval(TIME_INTERVAL_SERVO);
	threadController.add(&threadServoRun);
	Serial.println("Thread servo inicializado");
}

void loop() {
 serialController();
 threadController.run();
}
