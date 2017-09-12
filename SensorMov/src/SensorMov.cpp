#include <Arduino.h> 

/*	Implementación básica de un sensor de movimiento (PIR) */
const int sensorPin = 2;
int State = 0;

void setup() {
	pinMode(sensorPin, INPUT); 
	Serial.begin(9600);
}
void loop(){
	State = digitalRead(sensorPin);
	if (State == HIGH) { 
		Serial.print("State:");
		Serial.println(State);
	} 
	else {
		Serial.print("State:");
		Serial.println(State);
	}
	Serial.println(State);
	delay(500);
}