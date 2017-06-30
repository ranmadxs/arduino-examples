#ifndef YaiCommunicator_h
#define YaiCommunicator_h

#include <Arduino.h>
#include "YaiCommons.h"

#define MAX_I2C_COMAND 32
#define MAX_I2C_CONTENT 26

static int I2C_MASTER_SDA_PIN = 4;
static int I2C_MASTER_SCL_PIN = 5;

static int I2C_CLIENT_YAI_SERVO = 8;
static int I2C_CLIENT_YAI_MOTOR = 9;

//#ifndef YaiBufferCommand_h
//#define YaiBufferCommand_h

class YaiBufferCommand {
public:
	String type; //3Bytes
	int part;  //1Byte
	int total; //1Byte
	String content; //26Byte
	String status;
	String partContent;
	boolean recibeFull;
};

//#endif

class YaiCommunicator {
public:
	YaiCommunicator() {
		//bufferI2CInit();
		yaiMotorReady = false;
		yaiServoReady = false;
	}

	void requestEvent(String msgReq){
		int lenAnsw = msgReq.length();
		int difLen = 0;

		if (lenAnsw >= MAX_I2C_COMAND) {
			lenAnsw = MAX_I2C_COMAND;
		} else {
			difLen = MAX_I2C_COMAND - lenAnsw;
		}

		byte response[MAX_I2C_COMAND];
		for (byte i = 0; i < lenAnsw; i++) {
			response[i] = (byte) msgReq.charAt(i);
		}
		if (difLen > 0) {
			for (byte i = lenAnsw; i < MAX_I2C_COMAND; i++) {
				response[i] = 0x23;
			}
		}
		Wire.write(response, sizeof(response));
	}

	YaiBufferCommand receiveEvent(String masterCmd){
		YaiBufferCommand yaiBufferCmd;

		String requestI2C = "";
		while (0 < Wire.available()) {
			char c = Wire.read();
			requestI2C += c;
		}

		int part = requestI2C.substring(3, 4).toInt();
		int total = requestI2C.substring(4, 5).toInt();
		masterCmd = masterCmd + requestI2C.substring(5);
		yaiBufferCmd.recibeFull = false;

		if (part == total) {
			yaiBufferCmd.recibeFull = true;
			masterCmd.replace("#", "");
		}

		yaiBufferCmd.part = part;
		yaiBufferCmd.total = total;
		yaiBufferCmd.content = masterCmd;
		return yaiBufferCmd;
	}

	boolean scannI2CClient(int clientAddress) {
		boolean res = false;
		Wire.beginTransmission(clientAddress);
		byte error = Wire.endTransmission();
		if (error == 0) {
			if (clientAddress == I2C_CLIENT_YAI_MOTOR) {
				yaiMotorReady = true;
				Serial.println(
						"Yai Motor on address 0x0" + String(clientAddress)
								+ " connected");
			}
			if (clientAddress == I2C_CLIENT_YAI_SERVO) {
				yaiServoReady = true;
				Serial.println(
						"Yai Servo on address 0x0" + String(clientAddress)
								+ " connected");
			}
			res = true;
		} else {
			Serial.println(
					"No client found on address 0x0" + String(clientAddress));
			res = false;
		}
		return res;
	}

	YaiCommand propagateCommand(YaiCommand yaiCommand) {
		String response;
		YaiCommand yaiRsp;
		yaiRsp.p1 = String(STATUS_NOK);
		yaiRsp.type = yaiCommand.type;
		yaiRsp.message = "\""+ String(YAI_COMMAND_TYPE_NONE) + "\"";
		if (yaiCommand.type == String(YAI_COMMAND_TYPE_SERIAL)) {
			Serial.print("SERIAL >> ");
			yaiRsp.p1 = String(STATUS_OK);
			Serial.println(yaiCommand.message);
			yaiRsp.type = String(YAI_COMMAND_TYPE_RESULT);
		}
		if (yaiCommand.type == String(YAI_COMMAND_TYPE_I2C)) {
			yaiRsp.p1 = String(STATUS_OK);
			yaiRsp.type = String(YAI_COMMAND_TYPE_RESULT);

			String cmdRec = sendI2CCommand(yaiCommand.message, yaiCommand.address);
			Serial.print("(" + String(cmdRec.length()) + " num chars) :: ");
			Serial.println(cmdRec);
			String respuestaLimpia = cmdRec.substring(5);
			respuestaLimpia.replace("#", "");
			yaiRsp.message = respuestaLimpia;
			//yaiRsp.message = respuestaLimpia;
		}
		return yaiRsp;
	}

	YaiBufferCommand receiveI2CFromMaster() {
		String resp = "";
		YaiBufferCommand yaiI2CCmd;
		while (0 < Wire.available()) {
			char c = Wire.read();
			resp += c;
		}
		Serial.println("-------------------");
		Serial.println(resp);
		Serial.println("-------------------");
		if (resp.length() == MAX_I2C_COMAND - 1) {
			yaiI2CCmd = buildI2CCommand(resp);
			//Serial.println(yaiI2CCmd.content);
			bufferingI2C(yaiI2CCmd);
		}
		//Serial.println("=========>> " + resp);
		yaiI2CBuffer.partContent = resp;
		return yaiI2CBuffer;
	}

	String receiveCommand(int clientAddress) {
		String resp = "";
		Wire.requestFrom(clientAddress, MAX_I2C_COMAND);
		String response = "";
		int countChars = 0;
		while (0 < Wire.available()) {
			char b = Wire.read();
			resp += b;
			countChars++;
			//delay(50);
		}

		return resp;
	}

	String sendI2CCommand(String command, int clientAddress) {
		String cmdRec = "";
		int lenCmd = command.length();
		int totalParts = 1;
		if (lenCmd > MAX_I2C_CONTENT) {
			totalParts = 2;
		}
		String cmd1 = command.substring(0, MAX_I2C_CONTENT);
		String request1 = buildI2Cpackage(cmd1, totalParts, 1);
		sendI2Cpackage(request1, clientAddress);
		delay(150);
		cmdRec = receiveCommand(clientAddress);
		//Serial.println(" === " + cmdRec);
		if (totalParts > 1) {
			String cmd2 = command.substring(MAX_I2C_CONTENT);
			String request2 = buildI2Cpackage(cmd2, totalParts, 2);
			//Serial.println("<< " + request2);
			sendI2Cpackage(request2, clientAddress);
			delay(200);
			cmdRec = receiveCommand(clientAddress);
			//Serial.println(" === " + cmdRec);
		}
		return cmdRec;
	}

	void sendI2CToMaster(String command) {
		String commandPkg = buildI2Cpackage(command, 1, 1);
		char copyStr[MAX_I2C_COMAND];
		commandPkg.toCharArray(copyStr, MAX_I2C_COMAND);
		Wire.write(copyStr, sizeof(copyStr));
	}

	YaiBufferCommand buildI2CCommand(String command) {
		YaiBufferCommand cmd1;
		cmd1.type = String(YAI_COMMAND_TYPE_I2C);
		cmd1.part = command.substring(3, 4).toInt();
		cmd1.total = command.substring(4, 5).toInt();
		String contenido = command.substring(5);
		contenido.replace("#", "");
		cmd1.content = contenido;
		return cmd1;
	}

	String buildI2Cpackage(String command, int total, int part) {
		String respCommand = String(YAI_COMMAND_TYPE_I2C) + String(part)
				+ String(total) + command;
		int difLen = 0;
		int lenCommand = command.length();
		int headerLen = MAX_I2C_COMAND - MAX_I2C_CONTENT;
		if (lenCommand >= MAX_I2C_CONTENT) {
			lenCommand = MAX_I2C_CONTENT;
		} else {
			difLen = MAX_I2C_COMAND - lenCommand;
		}

		if (difLen > 0) {
			for (int i = lenCommand; i < MAX_I2C_CONTENT; i++) {
				respCommand += '#';
			}
		}

		return respCommand;
	}

	void sendI2Cpackage(String pkg, int clientAddress) {
		Wire.beginTransmission(clientAddress);
		char copyStr[MAX_I2C_COMAND];
		pkg.toCharArray(copyStr, MAX_I2C_COMAND);
		Wire.write(copyStr);
		//Wire.flush();
		int wireRes = Wire.endTransmission();
		Serial.println("wireRes::" + String(wireRes));
	}

private:

	void bufferingI2C(YaiBufferCommand yaiI2CCommand) {
		bufferI2CInit();
		//Serial.println("===============");
		//yaiI2CCommand.print();
		//Serial.println("===============");
		//Serial.print("yaiI2CCommand.content2:::");
		//Serial.println(yaiI2CCommand.content);
		if (yaiI2CBuffer.part < yaiI2CCommand.part) {
			//Serial.print("PART BUFFER: ");
			yaiI2CBuffer.part = yaiI2CCommand.part;
			yaiI2CBuffer.content = yaiI2CBuffer.content + yaiI2CCommand.content;
			yaiI2CBuffer.total = yaiI2CCommand.total;
			//Serial.println(String(yaiI2CBuffer.part));
			//Serial.print("Total: ");
			//Serial.println(String(yaiI2CBuffer.total));
		}
		if (yaiI2CBuffer.part == yaiI2CBuffer.total) {
			//Serial.println("TOTAL BUFFER ");
			yaiI2CBuffer.status = String(STATUS_OK);
		}
		//Serial.print("yaiI2CBuffer.content:::::");
		//Serial.println(yaiI2CBuffer.content);
	}

protected:
	YaiBufferCommand yaiI2CBuffer;
	boolean yaiMotorReady;
	boolean yaiServoReady;

	void bufferI2CInit() {
		// Si esta full el buffer se limpia
		if (yaiI2CBuffer.part == yaiI2CBuffer.total) {
			//Serial.println("INIT BUFFER ====");
			yaiI2CBuffer.part = 0;
			yaiI2CBuffer.total = 0;
			yaiI2CBuffer.content = "";
			yaiI2CBuffer.status = STATUS_NOK;
			yaiI2CBuffer.type = String(YAI_COMMAND_TYPE_I2C);
		}
	}
};

#endif
