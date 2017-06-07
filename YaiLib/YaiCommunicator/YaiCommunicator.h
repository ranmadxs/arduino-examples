#ifndef YaiCommunicator_h
#define YaiCommunicato_h

#include <Arduino.h>
#include "YaiCommons.h"

#define MAX_I2C_COMAND 32
#define MAX_I2C_CONTENT 26

class YaiI2CCommand {
public:
	String type; //3Bytes
	int part;  //1Byte
	int total; //1Byte
	String content; //27Byte
};

class YaiCommunicator {
public:
	YaiCommunicator(){};

	String sendI2CCommand(String command){
		int lenCmd = command.length();
		int totalParts = 1;
		if(lenCmd >MAX_I2C_CONTENT){
			totalParts = 2;
		}
		Serial.println("==============================");
		String cmd1 = command.substring(0, MAX_I2C_CONTENT);
		Serial.println(cmd1);
		String response1 = buildI2Cpackage(cmd1, totalParts, 1);
		Serial.println(response1);
		sendI2Cpackage(response1);
		if(totalParts > 1){
			String cmd2 = command.substring(MAX_I2C_CONTENT);
			Serial.println(cmd2);
			String response2 = buildI2Cpackage(cmd2, totalParts, 2);
			Serial.println(response2);
			sendI2Cpackage(response2);
		}
		Serial.println("==============================");
		String resp = "RET";
		return resp;
	}

	YaiI2CCommand buildI2CCommand(String command){
		YaiI2CCommand cmd1;
		cmd1.type = String(YAI_COMMAND_TYPE_I2C);
		cmd1.part = 1;
		cmd1.content = "1234567890123456789012345678";
		return cmd1;
	};
private:

	String sendI2Cpackage(String pkg){
		Wire.beginTransmission(9);
		char copyStr[MAX_I2C_COMAND];
		pkg.toCharArray(copyStr, MAX_I2C_COMAND);
		Wire.write(copyStr);
		Wire.endTransmission();
		String ret = "XD";
		return ret;
	}

	String buildI2Cpackage(String command, int total, int part){
		String respCommand = String(YAI_COMMAND_TYPE_I2C) + String(part) + String(total) +command;
		int difLen = 0;
		  int lenCommand = command.length();
		  int headerLen = MAX_I2C_COMAND - MAX_I2C_CONTENT;
		  if(lenCommand >= MAX_I2C_CONTENT){
			  lenCommand = MAX_I2C_CONTENT;
		  }else{
			  difLen = MAX_I2C_COMAND - lenCommand;
		  }

		 // if(difLen > 0){
		//	  for (int i=lenCommand;i<MAX_I2C_CONTENT;i++) {
		//		  respCommand += '#';
		//	  }
		//  }

		  return respCommand;
	}

protected:

};

#endif
