#include <Arduino.h>
#include "YRLog.h"
#include "YRServoSvc.h"
#include <Thread.h>
#include <ThreadController.h>

const int PIN_GREEN_POWER = 5;
const int PIN_RED_WORKING = 6;
const int PIN_TOUCH_SENSOR = 7;
const int PIN_SERVO_CRANE = 9;
const int PIN_INTERRUPT = 9;

int lastState = LOW;      // the previous state from the input pin
int currentState;         // the current reading from the input pin

YRLog logger;
YRServoSvc yrServoSvc;
int arrayServoId[] = { PIN_SERVO_CRANE };
int servoInitPos = 130;
int servoEndPos = 0;

int currentAngle = 0;
int newAngle = 0;

// platformio lib search Thread
// platformio lib install 440

Thread threadServoRun;
ThreadController threadController;

void callBackServoMovement() {
  logger.info("XD");
    currentAngle = yrServoSvc.getAngle(PIN_SERVO_CRANE);
    if (currentAngle < newAngle) {
      for(int pos = currentAngle; pos < newAngle; pos += 5) {
        yrServoSvc.setAngle( PIN_SERVO_CRANE, pos);
        delay(30);
      }
    }
}

void setup() {
  Serial.begin(9600);
  logger.init("main.cpp");
  pinMode(PIN_GREEN_POWER, OUTPUT);
  pinMode(PIN_RED_WORKING, OUTPUT);
  digitalWrite(PIN_GREEN_POWER, HIGH);
  digitalWrite(PIN_RED_WORKING, LOW);
  pinMode(PIN_TOUCH_SENSOR, INPUT);  
  Serial.println("**************************************");
  Serial.println("****  Control Tower [0.1.3-alpha] ****");
 	yrServoSvc.init(arrayServoId);
	threadServoRun.onRun(callBackServoMovement);
	threadServoRun.setInterval(yrServoSvc.TIME_INTERVAL_SERVO);
	threadController.add(&threadServoRun);     
  Serial.println("**************************************");  
}

void loop() {
  currentState = digitalRead(PIN_TOUCH_SENSOR);

  if(lastState == LOW && currentState == HIGH){
    logger.debug("Touch Sensor [OFF] -> [ON]");
    yrServoSvc.setAngle( PIN_SERVO_CRANE, servoEndPos);
  }
  if(lastState == HIGH && currentState == LOW){
    logger.debug("Touch Sensor [ON] -> [OFF]");
    yrServoSvc.setAngle(PIN_SERVO_CRANE, servoInitPos);
  }
  if(currentState == HIGH){
    digitalWrite(PIN_RED_WORKING, HIGH);
  } else {
    
    digitalWrite(PIN_RED_WORKING, LOW);
  }

  // save the the last state
  lastState = currentState;
}
