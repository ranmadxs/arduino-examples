#ifndef YRServoSvc_h
#define YRServoSvc_h

#include <Arduino.h>
#include <Servo.h>
#include "YRLog.h"

// platformio lib search Servo
// platformio lib install 883


static int YR_SERVO_INIT_POSITION = 0;


class YRServoSvc {

public:
	int TIME_INTERVAL_SERVO = 15;

	YRServoSvc() {
	}

	void callBackServoMovement();
	int YRServoSvc::getAngle(int servoId);
	void init(int servoIds[]);

	void attach(int servoId) {
		logger.debug("Servo attach GPIO ["+String(servoId)+"]");
		servos[servoId].attach(servoId);
		servos[servoId].write(YR_SERVO_INIT_POSITION);
		//servosAngle[servoId] = YR_SERVO_INIT_POSITION;
	}

	void detach(int servoId) {
		servos[servoId].detach();
	}

	void setAngle(int servoId, int angle);

	void moveAll(int angle);

protected:
	YRLog logger;
	Servo servos[16];
	//int servosAngle[16];
};

#endif
