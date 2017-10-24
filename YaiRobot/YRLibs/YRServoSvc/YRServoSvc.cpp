#include <Arduino.h>
#include "YRServoSvc.h"

String YRServoSvc::setAngle(String servoType, int servoId, int angle) {

	int angleServo = servos[servoId].read();
	String resp = String(angleServo)+","+String(angle);
	servos[servoId].write(angle);
	Serial.print("Resp:::");
	angleServo = servos[servoId].read();
	Serial.println(resp);
	return resp;
}
