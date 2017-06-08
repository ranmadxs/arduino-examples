#ifndef YaiCommunicator_h
#define YaiCommunicato_h

#include <Arduino.h>
#include "YaiCommons.h"

#define MAX_I2C_COMAND 32
#define MAX_I2C_CONTENT 26

int I2C_MASTER_SDA_PIN = 4;
int I2C_MASTER_SCL_PIN = 5;

class YaiBufferCommand {
public:
	String type; //3Bytes
	int part;  //1Byte
	int total; //1Byte
	String content; //26Byte
	String status;

	void print(){
		Serial.print("{\"type\":\"");
		Serial.print(type);
		Serial.print("\", \"part\":");
		Serial.print(part);
		Serial.print(", \"total\":");
		Serial.print(total);
		Serial.print(", \"content\":\"");
		Serial.print(content+"\"");
		Serial.println("}");
	}
};

class YaiCommunicator {
public:
	YaiCommunicator() {
		bufferI2CInit();
	}

	YaiBufferCommand receiveI2CFromMaster() {
		String resp = "";
		YaiBufferCommand yaiI2CCmd;
		while (0 < Wire.available()) {
			char c = Wire.read();
			resp += c;
		}
		if(resp.length() == MAX_I2C_COMAND - 1){
			Serial.println("=========>> " + resp);
			//yaiI2CCmd = buildI2CCommand(resp);
			//Serial.println(yaiI2CCmd.content);
			//bufferingI2C(yaiI2CCmd);

		}
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
		}

		return resp;
	}

	void sendI2CToMaster(String command) {
		String commandPkg = buildI2Cpackage(command, 1, 1);
		char copyStr[MAX_I2C_COMAND];
		commandPkg.toCharArray(copyStr, MAX_I2C_COMAND);
		Wire.write(copyStr, sizeof(copyStr));
	}

	void sendI2CCommand(String command, int clientAddress) {
		int lenCmd = command.length();
		int totalParts = 1;
		if (lenCmd > MAX_I2C_CONTENT) {
			totalParts = 2;
		}
		String cmd1 = command.substring(0, MAX_I2C_CONTENT);
		String request1 = buildI2Cpackage(cmd1, totalParts, 1);
		Serial.println("<< " + request1);
		delay(200);
		sendI2Cpackage(request1, clientAddress);
		if (totalParts > 1) {
			String cmd2 = command.substring(MAX_I2C_CONTENT);
			String request2 = buildI2Cpackage(cmd2, totalParts, 2);
			Serial.println("<< " + request2);
			sendI2Cpackage(request2, clientAddress);
		}
	}

	YaiBufferCommand buildI2CCommand(String command) {
		YaiBufferCommand cmd1;
		cmd1.type = String(YAI_COMMAND_TYPE_I2C);
		cmd1.part =  command.substring(3, 4).toInt();
		cmd1.total = command.substring(4, 5).toInt();
		String contenido = command.substring(5);
		contenido.replace("#", "");
		cmd1.content = contenido;
		return cmd1;
	}

private:

	void bufferingI2C(YaiBufferCommand yaiI2CCommand){
		bufferI2CInit();
		//Serial.println("===============");
		yaiI2CCommand.print();
		//Serial.println("===============");
		if(yaiI2CBuffer.part < yaiI2CCommand.part){
			Serial.print("PART BUFFER: ");
			yaiI2CBuffer.part = yaiI2CCommand.part;
			yaiI2CBuffer.content += yaiI2CCommand.content;
			yaiI2CBuffer.total = yaiI2CCommand.total;
			Serial.println(String(yaiI2CBuffer.part));
			Serial.print("Total: ");
			Serial.println(String(yaiI2CBuffer.total));
		}
		if(yaiI2CBuffer.part == yaiI2CBuffer.total){
			Serial.println("TOTAL BUFFER ");
			yaiI2CBuffer.status = String(STATUS_OK);
		}
	}

	void sendI2Cpackage(String pkg, int clientAddress) {
		Wire.beginTransmission(clientAddress);
		char copyStr[MAX_I2C_COMAND];
		pkg.toCharArray(copyStr, MAX_I2C_COMAND);
		Wire.write(copyStr);
		Wire.endTransmission();
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

protected:
	YaiBufferCommand yaiI2CBuffer;

	void bufferI2CInit(){
		// Si esta full el buffer se limpia
		if(yaiI2CBuffer.part == yaiI2CBuffer.total){
			Serial.println("INIT BUFFER ====");
			yaiI2CBuffer.part = 0;
			yaiI2CBuffer.total = 0;
			yaiI2CBuffer.content = "";
			yaiI2CBuffer.status = STATUS_NOK;
			yaiI2CBuffer.type = String(YAI_COMMAND_TYPE_I2C);
		}
	}
};

#endif