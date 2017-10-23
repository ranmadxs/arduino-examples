#include <Arduino.h>
#include "YRServo.h"

YRServo yrServo;

void setup() {
	Serial.begin(9600);
	Serial.println("***********************");
	Serial.println("Yai Finger V0.0.1-SNAPSHOT");
	Serial.println("***********************");
	//yrServo.setAngle("S3003", 9, 0);
	int servosIds[] = {9};
	yrServo.init(servosIds);
	delay(3000);
	yrServo.setAngle("S3003", 9, 90);
	delay(3000);
}

void loop() {

	//yrServo.setAngle("S3003", 9, 90);
	delay(3000);
	//yrServo.setAngle("S3003", 9, 0);
	delay(3000);
}
