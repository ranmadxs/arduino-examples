#ifndef YRServoSvc_h
#define YRServoSvc_h

#include <Arduino.h>
#include <Servo.h>
#include "YRLog.h"

static String YR_SERVO_TYPE_S3003 = "S3003";
static int YR_SERVO_INIT_POSITION = 0;

class YRServoSvc {

public:

	String SERVO_ACTION_ANGLE = "ANGLE";
	String SERVO_ACTION_ALL = "ALL";

	YRServoSvc() {
	}

	void init(int servoIds[]){
		int i;
		logger.init("YRServoSvc");
		for (i = 0; i < (sizeof(servoIds)/sizeof(int)); i++) {
			attach(servoIds[i]);
		}
	}

	void attach(int servoId) {
		logger.debug("Servo attach GPIO ["+String(servoId)+"]");
		servos[servoId].attach(servoId);
		servos[servoId].write(YR_SERVO_INIT_POSITION);
	}

	void detach(int servoId) {
		servos[servoId].detach();
	}

	String setAngle(String servoType, int servoId, int angle);

protected:
	YRLog logger;
	Servo servos[16];
};

#endif
