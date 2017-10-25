#include <Arduino.h>
#include "YRCommand.h"
#include "YRCommons.h"
#include "YRUtil.h"
#include "YRServoSvc.h"

YRServoSvc yrServoSvc;
YRUtil yaiUtil;


String executeCommand(String masterCommand) {
	String responseExe = String(YAI_COMMAND_TYPE_RESULT);
	String resultStr = String(STATUS_NOK);
	String content = String(YAI_COMMAND_TYPE_NONE);
	String rootCmd[9];
	yaiUtil.getElementRoot(masterCommand, rootCmd);
	String commandRoot = rootCmd[1];
	String actionRoot = rootCmd[2];
	Serial.println("commandRoot=" + commandRoot);
	Serial.println("actionRoot="+actionRoot+"=="+yrServoSvc.SERVO_ACTION_ANGLE);
	if(commandRoot == YR_TYPE_SERVO){
		if (actionRoot == yrServoSvc.SERVO_ACTION_ANGLE) {
			resultStr = String(STATUS_OK);
			content = yrServoSvc.setAngle(rootCmd[3], rootCmd[4].toInt(),
					rootCmd[5].toInt());
		}
	}
	responseExe = responseExe + "," + resultStr + "," + content;

	return responseExe;

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
	Serial.begin(9600);
	Serial.println("***********************");
	Serial.println("Yai Finger V0.0.1-SNAPSHOT");
	Serial.println("***********************");
	//yrServo.setAngle("S3003", 9, 0);
	int servosIds[] = { 9 };
	yrServoSvc.init(servosIds);
	delay(100);
	yrServoSvc.setAngle("S3003", 9, 20);
	delay(500);
	yrServoSvc.setAngle("S3003", 9, 0);
	delay(100);
}

void loop() {
	serialController();
}
