#include <Arduino.h> 
#include <Servo.h>

int pin = 9;
int stop_position = 95;
int velocity = 20;

Servo servo;

void setup() {
  servo.attach(pin);
  servo.write(40);
  delay(1000);
}

void loop() {
  //servo.write(90);
  //delay(1000);
  //servo.write(0);
  //delay(1000);
  //servo.detach();

	//servo.writeMicroseconds(1500);
	//delay(400);
	//servo.writeMicroseconds(1200);

	//servo.attach(pin);
	//servo.writeMicroseconds(1800);
	//delay(400);
	//servo.writeMicroseconds(200);
	//delay(400);
	//servo.detach();
	//delay(2000);
	//servo.attach(pin);
}
