#include <Arduino.h>
#include <Wire.h>
#include "YaiCommons.h"
#include "ObstacleLink.h"
#include "RoverLink.h"
//#include "YaiCommunicator.h"

#define ANSWERSIZE 32

String answer = "";
ObstacleLink hcsr;
RoverLink roverLn;
YaiUtil yaiUtil;
String masterCmd = "";
boolean reciveFullI2C = false;
String requestI2C = "";
//YaiCommunicator yaiCommunicator;
// este valor se debe setear en cero para el nodemcu para orange pi en 1
int offset = 1;

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

String execute(String masterCommand) {
	String responseExe = String(YAI_COMMAND_TYPE_RESULT);
	String resultStr = String(STATUS_NOK);
	String content = String(YAI_COMMAND_TYPE_NONE);
	String rootCmd[9];
	yaiUtil.getElementRoot(masterCommand, rootCmd);
	String commandRoot = rootCmd[1];
	if (commandRoot == String(ROVER_STOP)) {
		resultStr = String(STATUS_OK);
		roverLn.motorStop(rootCmd[2].toInt());
	}
	if (commandRoot == String(LASER_ACTION)) {
		resultStr = String(STATUS_OK);
		boolean activar = false;
		content = "false";
		if (rootCmd[2].equalsIgnoreCase("true")) {
			activar = true;
			content = "true";
		}
		roverLn.laser(activar);
	}

	if (commandRoot == String(ROVER_MOVE_MANUAL_BODY)) {
		resultStr = String(STATUS_OK);
		content = roverLn.motorMove(rootCmd[2], rootCmd[5]);
	}

	if (commandRoot == String(OBSTACLE_READER)) {
		resultStr = String(STATUS_OK);
		String dist = hcsr.distancia(rootCmd[2].toInt(), rootCmd[3].toInt());
		content = dist;
	}

	responseExe = responseExe + "," + resultStr + "," + content;

	return responseExe;
}

void serialController() {
	YaiCommand yaiCommand;
	YaiCommand yaiResCmd;
	yaiCommand = yaiUtil.commandSerialFilter();
	if (yaiCommand.execute) {
		String respSerialCmd = execute(yaiCommand.message);
		if (yaiCommand.print) {
			Serial.println("<< [SERIAL] " +respSerialCmd);
		}
	}
}

void setup() {
	Wire.begin(9);
	Wire.onRequest(requestEvent); // data request to slave
	Wire.onReceive(receiveEvent); // data slave received
	Serial.begin(9600);
	Serial.println("***********************");
	Serial.println("Yai motor inicializado v0.0.1-SNAPSHOT");
	Serial.println("***********************");
	Serial.println("Serial port ready");
	Serial.println("I2C ready!  32 Bytes");
}

void loop() {

	if (reciveFullI2C) {
		Serial.println(">> " + masterCmd);
		reciveFullI2C = false;
		masterCmd.replace("#", "");
		answer = execute(masterCmd);
		Serial.println("<< [I2C] " + answer);
		masterCmd = "";
	}
	serialController();
}
