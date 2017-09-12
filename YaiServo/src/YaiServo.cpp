#include <Arduino.h>
#include <Wire.h>
#include "ServoLink.h"
#include "YaiCommons.h"
#include <string.h>
#include <Thread.h>
#include <ThreadController.h>

#define ANSWERSIZE 32

String answer = "";
ServoLink servoLink;
YaiUtil yaiUtil;

String masterCmd = "";
boolean reciveFullI2C = false;
String requestI2C = "";

int TIME_INTERVAL_SERVO = 15;
Thread threadServoRun;
ThreadController threadController;

int offset = 1;

void callBackServoMovement() {
	servoLink.callBackMovement();
}

String executeCommand(String masterCommand) {
	String responseExe = String(YAI_COMMAND_TYPE_RESULT);
	String resultStr = String(STATUS_NOK);
	String content = String(YAI_COMMAND_TYPE_NONE);
	String rootCmd[9];
	yaiUtil.getElementRoot(masterCommand, rootCmd);
	String commandRoot = rootCmd[1];
	if (commandRoot == String(SERVO_ACTION_ANGLE)) {
		resultStr = String(STATUS_OK);
		content = servoLink.servoAngle(rootCmd[2].toInt(), rootCmd[4].toInt(),
				rootCmd[5].toInt());
	}
	if (commandRoot == String(SERVO_ACTION_CONTINUOUS)) {
		resultStr = String(STATUS_OK);
		//respCommand = true;
		content = servoLink.servoMove(rootCmd[2].toInt(), rootCmd[4].toInt(),
				rootCmd[5].toInt(), rootCmd[6].toInt());
	}
	if (commandRoot == String(SERVO_STOP)) {
		resultStr = String(STATUS_OK);
		//respCommand = true;
		content = servoLink.servoStop(rootCmd[2].toInt(), rootCmd[4].toInt());
	}

	responseExe = responseExe + "," + resultStr + "," + content;

	return responseExe;
}

void receiveEvent(int countToRead) {
	/*
	 YaiBufferCommand yaiBuffer = yaiCommunicator.receiveEvent(masterCmd);
	 masterCmd = yaiBuffer.content;
	 reciveFullI2C = yaiBuffer.recibeFull;
	 */

	requestI2C = "";
	while (0 < Wire.available()) {
		char c = Wire.read();
		requestI2C += c;
	}

	int part = requestI2C.substring(3 + offset, 4 + offset).toInt();
	int total = requestI2C.substring(4 + offset, 5 + offset).toInt();
	masterCmd = masterCmd + requestI2C.substring(5 + offset);
	//Serial.print(">> ");
	//Serial.println(masterCmd);
	if (part == total && masterCmd.length() >= ANSWERSIZE) {
		reciveFullI2C = true;

	}

}

void requestEvent() {

	int lenAnsw = answer.length();
	int difLen = 0;

	if (lenAnsw >= ANSWERSIZE) {
		lenAnsw = ANSWERSIZE;
	} else {
		difLen = ANSWERSIZE - lenAnsw;
	}

	byte response[ANSWERSIZE];
	for (byte i = 0; i < lenAnsw; i++) {
		response[i] = (byte) answer.charAt(i);
	}
	if (difLen > 0) {
		for (byte i = lenAnsw; i < ANSWERSIZE; i++) {
			response[i] = 0x23;
		}
	}
	Wire.write(response, sizeof(response));

	//yaiCommunicator.requestEvent(answer);
}

void serialController() {
	YaiCommand yaiCommand;
	YaiCommand yaiResCmd;
	yaiCommand = yaiUtil.commandSerialFilter();
	if (yaiCommand.execute) {
		String respSerialCmd = executeCommand(yaiCommand.message);
		if (yaiCommand.print) {
			Serial.println("<< [SERIAL] " + respSerialCmd);
		}
	}
}

void setup() {
	Wire.begin(8);
	Wire.onRequest(requestEvent); // data request to slave
	Wire.onReceive(receiveEvent); // data slave received
	Serial.begin(9600);
	Serial.println("***********************");
	servoLink.init();
	Serial.println("Yai servo inicializado V0.0.4-SNAPSHOT");
	Serial.println("***********************");
	Serial.println("Serial port ready");
	threadServoRun.onRun(callBackServoMovement);
	threadServoRun.setInterval(TIME_INTERVAL_SERVO);
	threadController.add(&threadServoRun);
	Serial.println("Thread servo inicializado");
	Serial.println("I2C ready!  32 Bytes");
}

void loop() {
	serialController();
	threadController.run();
	if (reciveFullI2C) {
		Serial.println(">> " + masterCmd);
		reciveFullI2C = false;
		masterCmd.replace("#", "");
		answer = executeCommand(masterCmd);
		Serial.println("<< [I2C] " + answer);
		masterCmd = "";
	}
}
