#include <Arduino.h>
#include "YRServoSvc.h"

int YRServoSvc::getAngle(int servoId){
	return servos[servoId].read();
}

void YRServoSvc::setAngle(int servoId, int angle) {
	//servosAngle[servoId] = angle;
	servos[servoId].write(angle);
}

void YRServoSvc::moveAll(int angle) {
	logger.info("move");
	for (int i = 0; i < (sizeof(servos)/sizeof(int)); i++) {
		//servos[i].write(servosAngle[i]);
		servos[i].write(angle);
	}
}

void YRServoSvc::init(int servoIds[]){
	int i;
	logger.init("YRServoSvc");
	for (i = 0; i < (sizeof(servoIds)/sizeof(int)); i++) {
		attach(servoIds[i]);
	}
}
