#include <Arduino.h>
#include "YRServoSvc.h"

int YRServoSvc::setAngle(String servoType, int servoId, int angle) {

	int angleServo = servos[servoId].read();
	Serial.print("YRServo::current Angle=");
	Serial.println(angleServo);
	servos[servoId].write(angle);
	Serial.print("YRServo::set Angle=");
	angleServo = servos[servoId].read();
	Serial.println(angleServo);

	return angleServo;
}
