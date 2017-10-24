#include <Arduino.h>
#include "YRCommand.h"
#include "YRCommons.h"
#include "YRUtil.h"
#include "YRServoSvc.h"

YRServoSvc yrServoSvc;
YRUtil yaiUtil;



void serialController() {
	YRCommand yrCommand;
	yrCommand = yaiUtil.commandSerialFilter();
	if (yrCommand.execute) {
		//String respSerialCmd = executeCommand(yrCommand.message);
		if (yrCommand.print) {
			Serial.println(">> [SERIAL] " + yrCommand.message);
			//Serial.println("<< [SERIAL] " + respSerialCmd);
		}
	}
}

void setup() {
	Serial.begin(9600);
	Serial.println("***********************");
	Serial.println("Yai Finger V0.0.1-SNAPSHOT");
	Serial.println("***********************");
	//yrServo.setAngle("S3003", 9, 0);
	int servosIds[] = {9};
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
