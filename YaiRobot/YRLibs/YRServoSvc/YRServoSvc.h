#ifndef YRServoSvc_h
#define YRServoSvc_h

#include <Arduino.h>
#include <Servo.h>

static String YR_SERVO_TYPE_S3003 = "S3003";
static int YR_SERVO_INIT_POSITION = 0;

class YRServoSvc {

public:

	String SERVO_ACTION_ANGLE = "ANGLE";

	YRServoSvc() {
	}

	void init(int servoIds[]){
		int i;
		for (i = 0; i < (sizeof(servoIds)/sizeof(int)); i++) {
			attach(servoIds[i]);
		}

	}

	void attach(int servoId) {
		Serial.print("Servo attach:");
		Serial.println(servoId);
		servos[servoId].attach(servoId);
		servos[servoId].write(YR_SERVO_INIT_POSITION);
	}

	void detach(int servoId) {
		servos[servoId].detach();
	}

	String setAngle(String servoType, int servoId, int angle);

protected:

	Servo servos[16];
};

#endif
