#ifndef YRServo_h
#define YRServo_h

#include <Arduino.h>
#include <Servo.h>

static String YR_SERVO_TYPE_S3003 = "S3003";
static int YR_SERVO_INIT_POSITION = 0;

class YRServo {

public:

	YRServo() {
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

	int setAngle(String servoType, int servoId, int angle);

protected:

	Servo servos[16];
};

#endif
