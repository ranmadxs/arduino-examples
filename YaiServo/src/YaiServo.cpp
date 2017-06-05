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
};

String executeCommand(YaiCommand yaiCommand){
	String content = "Command not found";
	String resultStr = "NOK";
	String responseSvc;
	String commandRoot = yaiCommand.command;
	String jsonResult = "{\"RESULT\":\""+resultStr+"\", \"CONTENT\":"+content+"}";
	boolean respCommand = false;
	//Serial.println("Cmd:" + commandRoot);
	if (commandRoot == String(SERVO_ACTION_ANGLE)){
		resultStr = "OK";
		respCommand = true;
		responseSvc = servoLink.servoAngle(yaiCommand.p1.toInt(), yaiCommand.p3.toInt(), yaiCommand.p4.toInt());
		content = "{\"TIME:\":" + yaiCommand.p2 + ", \"SERVO\":"+responseSvc+"}";
	}
	if (commandRoot == String(SERVO_ACTION_CONTINUOUS)){
		resultStr = "OK";
		respCommand = true;
		responseSvc = servoLink.servoMove(yaiCommand.p1.toInt(), yaiCommand.p3.toInt(), yaiCommand.p4.toInt(), yaiCommand.p5.toInt());
		content = "{\"TIME:\":" + yaiCommand.p2 + ", \"SERVO\":"+responseSvc+"}";
	}
	if(commandRoot == String(SERVO_STOP)){
		resultStr = "OK";
		respCommand = true;
		responseSvc = servoLink.servoStop(yaiCommand.p1.toInt(), yaiCommand.p3.toInt());
		content = "{\"TIME:\":" + yaiCommand.p2 + ", \"SERVO\":"+responseSvc+"}";
	}
	if(respCommand){
		jsonResult = "{\"RESULT\"";
		Serial.print(jsonResult);
		jsonResult += ":\""+resultStr+"\", \"CONTENT\":";
	    Serial.print(":\""+resultStr+"\", \"CONTENT\":");
	    jsonResult += content + "}";
	    Serial.println(content + "}");
	}
	return jsonResult;
}

void serialController(){
	YaiCommand yaiCommand;
	yaiCommand = yaiUtil.commandSerialFilter();
	if(yaiCommand.execute){
		executeCommand(yaiCommand);
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
