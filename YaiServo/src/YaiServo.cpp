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

String executeCommand(String masterCommand){
	String responseExe = String(YAI_COMMAND_TYPE_RESULT);
	String resultStr = String(STATUS_NOK);
	String content = String(YAI_COMMAND_TYPE_NONE);
	String rootCmd[9];
	yaiUtil.getElementRoot(masterCommand, rootCmd);
	String commandRoot = rootCmd[1];
	if (commandRoot == String(SERVO_ACTION_ANGLE)){
		resultStr = String(STATUS_OK);
		content = servoLink.servoAngle(rootCmd[2].toInt(), rootCmd[4].toInt(), rootCmd[5].toInt());
	}
	if (commandRoot == String(SERVO_ACTION_CONTINUOUS)){
		resultStr = String(STATUS_OK);
		//respCommand = true;
		content = servoLink.servoMove(rootCmd[2].toInt(), rootCmd[4].toInt(), rootCmd[5].toInt(), rootCmd[6].toInt());
	}
	if(commandRoot == String(SERVO_STOP)){
		resultStr = String(STATUS_OK);
		//respCommand = true;
		content = servoLink.servoStop(rootCmd[2].toInt(), rootCmd[4].toInt());
	}

	responseExe = responseExe + "," + resultStr + "," + content;

	return responseExe;
}

void serialController(){
	YaiCommand yaiCommand;
	YaiCommand yaiResCmd;
	yaiCommand = yaiUtil.commandSerialFilter();
	if(yaiCommand.execute){
		String respSerialCmd = executeCommand(yaiCommand.message);
		if (yaiCommand.print) {
			Serial.println("<< [SERIAL]" +respSerialCmd);
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
