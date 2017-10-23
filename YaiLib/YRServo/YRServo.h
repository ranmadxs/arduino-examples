#ifndef YRServo_h
#define YRServo_h

#include <Arduino.h>
#include <Servo.h>

static String YR_SERVO_TYPE_S3003 = "S3003";

class YRServo {

public:

	YRServo(){};

	int setAngle(String servoType, int servoId, int angle);
};

#endif
