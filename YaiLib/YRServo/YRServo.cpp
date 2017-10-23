#include <Arduino.h>
#include "YRServo.h"

int YRServo::setAngle(String servoType, int servoId, int angle) {

	Serial.print("YRServo::set Angle=");
	Serial.println(angle);

	Servo servoObj;
	servoObj.attach(servoId);
	servoObj.write(angle);
	int angleOut = servoObj.read();
	servoObj.detach();

	return angleOut;
}
