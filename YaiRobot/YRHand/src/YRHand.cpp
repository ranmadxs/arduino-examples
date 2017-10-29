#include <Arduino.h>
#include "YRCommand.h"
#include "YRCommons.h"
#include "YRUtil.h"
#include "YRServoSvc.h"
#include "YRLog.h"
#include <Wire.h>

YRServoSvc yrServoSvc;
YRUtil yaiUtil;
YRLog logger;
int arrayServoId[] = { 9 };
String masterCmd = "";
boolean reciveFullI2C = false;
String requestI2C = "";
String answer = "";
int offset = 1;



String executeCommand(String masterCommand) {
	String responseExe = String(YAI_COMMAND_TYPE_RESULT);
	String resultStr = String(STATUS_NOK);
	String content = String(YAI_COMMAND_TYPE_NONE);
	String rootCmd[9];
	yaiUtil.getElementRoot(masterCommand, rootCmd);
	String commandRoot = rootCmd[1];
	String actionRoot = rootCmd[2];
	logger.debug("commandRoot=" + commandRoot);
	logger.debug("actionRoot=" + actionRoot);
	String tipoServo = rootCmd[3];
	if (commandRoot == YR_TYPE_SERVO) {
		if (actionRoot == yrServoSvc.SERVO_ACTION_ANGLE) {
			resultStr = String(STATUS_OK);
			int angulo = rootCmd[5].toInt();
			String idServo = rootCmd[4];
			if (idServo == yrServoSvc.SERVO_ACTION_ALL) {
				content = yrServoSvc.SERVO_ACTION_ALL +","+ String(angulo);
				for (int i = 0; i < (sizeof(arrayServoId)/sizeof(int)); i++) {
					yrServoSvc.setAngle(tipoServo, arrayServoId[i], angulo);
				}
			} else {
				content = idServo + "," + yrServoSvc.setAngle(tipoServo, idServo.toInt(),
						angulo);
			}
		}
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
	YRCommand yrCommand;
	yrCommand = yaiUtil.commandSerialFilter();
	if (yrCommand.execute) {
		String respSerialCmd = executeCommand(yrCommand.message);
		if (yrCommand.print) {
			Serial.println(">> [SERIAL] " + yrCommand.message);
			Serial.println("<< [SERIAL] " + respSerialCmd);
		}
	}
}

void setup() {
	Wire.begin(I2C_CLIENT_YR_HAND);
	Wire.onRequest(requestEvent); // data request to slave
	Wire.onReceive(receiveEvent); // data slave received
	Serial.begin(9600);
	logger.init("YRHand");
	Serial.println("***************************");
	Serial.println("Yai Hand V0.0.1-SNAPSHOT");
	Serial.println("---------------------------");
	logger.info("I2C ["+String(I2C_CLIENT_YR_HAND)+"] ready!  32 Bytes");
	Serial.println("---------------------------");
	yrServoSvc.init(arrayServoId);
	Serial.println("***************************");
}

void loop() {
	serialController();
	if (reciveFullI2C) {
		logger.info(">> [I2C] " + masterCmd);
		reciveFullI2C = false;
		masterCmd.replace("#", "");
		answer = executeCommand(masterCmd);
		logger.info("<< [I2C] " + answer);
		masterCmd = "";
	}
}
