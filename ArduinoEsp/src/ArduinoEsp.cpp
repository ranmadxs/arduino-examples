#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial esp8266(3, 2); // RX | TX
char txt;
void setup() {
	//Serial.begin(9600);
	//esp8266.begin(9600);
	Serial.begin(115200);
	esp8266.begin(115200);
	Serial.println("ArduinoEsp example");
}
void loop() {
	if (Serial.available()) {
		txt = Serial.read();
		esp8266.print(txt);
	}
	if (esp8266.available()) {
		txt = esp8266.read();
		Serial.print(txt);
	}
}
