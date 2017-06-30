#include <Arduino.h> 
#include "ServoLink.h"

//default speed = 15
// creo dos thread uno que haga move simepre que no este stop y el otro que haga el stop.
YaiCommand ServoLink::servoMove(int servoType, int servoDirection,
		int servoMovement, int speedDeplay) {
	String result = "";
	YaiCommand respYai;
	ServoLink::setServoType(servoType, servoDirection);
	ServoLink::setSpeedDelay(servoDirection, speedDeplay);
	int pos;
	String direction = "None";
	if (SERVO_DIRECTION_HORIZONTAL == servoDirection) {
		direction = "HORI";
		directionFlagH = true;
		movementServoH = servoMovement;
	}
	if (SERVO_DIRECTION_VERTICAL == servoDirection) {
		direction = "VERT";
		directionFlagV = true;
		movementServoV = servoMovement;
	}
	respYai.p2 = direction;
	//return "{\"ACTION\":\"MOVE\", \"DIRECTION\":\"" + direction + "\"}";
	return respYai;
}

YaiCommand ServoLink::servoStop(int servoType, int servoDirection) {
	YaiCommand respYai;

	ServoLink::setServoType(servoType, servoDirection);
	String directionName = "None";
	if (SERVO_DIRECTION_HORIZONTAL == servoDirection) {
		directionName = "\"HORIZONTAL\"";
		directionFlagH = false;
	}
	if (SERVO_DIRECTION_VERTICAL == servoDirection) {
		directionName = "\"VERTICAL\"";
		directionFlagV = false;
	}
	if (SERVO_DIRECTION_ALL == servoDirection) {
		directionName = "ALL";
		directionFlagV = false;
		directionFlagH = false;
	}
	respYai.p2 = directionName;
	//return "{\"ACTION\":\"STOP\", \"DIRECTION\":" + directionName + "}";
	return respYai;
}

/**
 * p2: directionName
 * p3: angle
 */
YaiCommand ServoLink::servoAngle(int servoType, int servoDirection, int angle) {

	YaiCommand respYai;

	ServoLink::setServoType(servoType, servoDirection);
	int maxAngle = ServoLink::getMaxAngle(servoType);
	String directionName = "None";
	if (angle > maxAngle) {
		angle = maxAngle;
	}
	if (SERVO_DIRECTION_ALL == servoDirection) {
		directionName = "ALL";
		ServoLink::setPosition(SERVO_DIRECTION_HORIZONTAL, angle);
		ServoLink::write(SERVO_DIRECTION_HORIZONTAL, angle);
		ServoLink::setPosition(SERVO_DIRECTION_VERTICAL, angle);
		ServoLink::write(SERVO_DIRECTION_VERTICAL, angle);
		//directionName += "\""
		//		+ ServoLink::write(SERVO_DIRECTION_HORIZONTAL, angle) + "\", ";
		//directionName += "\""
		//		+ ServoLink::write(SERVO_DIRECTION_VERTICAL, angle) + "\"";
		//directionName += "]";
	} else {
		ServoLink::setPosition(servoDirection, angle);
		//directionName = "\"" + ServoLink::write(servoDirection, angle) + "\"";
		directionName = ServoLink::write(servoDirection, angle);
	}
	respYai.p2 = directionName;
	respYai.p3 = String(angle);
	//String result = "{ \"DIRECTION\":" + directionName + ", \"ANGLE:\":"
	//		+ String(angle) + "}";
	return respYai;

}

