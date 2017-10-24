#include <Arduino.h>
#include "YRCommons.h"
#include "YRServoSvc.h"
#include "YRCommand.h"

YRServoSvc yrServoSvc;

void serialController() {

	YRCommand yrCommand;

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
