#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial esp8266(3, 2); // RX | TX
char txt;
#define DEBUG false
int connectionId;

String sendData(String command, const int timeout, boolean debug) {
	String response = "";
	esp8266.println(command); // send the read character to the esp8266
	long int time = millis();

	while ((time + timeout) > millis()) {
		while (esp8266.available()) {
			char c = esp8266.read(); // read the next character.
			response += c;
		}
	}
	if (debug) {
		Serial.print(response);
	}
	return response;
}

void espSend(String d) {
	String cipSend = " AT+CIPSEND=";
	cipSend += connectionId;
	cipSend += ",";
	cipSend += d.length();
	sendData(cipSend, 1000, DEBUG);
	sendData(d, 1000, DEBUG);
}

void setup() {
	Serial.begin(9600);
	esp8266.begin(9600);
	Serial.println("ArduinoEsp WEB example");
	String resp = sendData("AT+CIFSR", 2000, DEBUG);
	Serial.println(resp);
	sendData("AT+CIPMUX=1", 2000, DEBUG);
	sendData("AT+CIPSERVER=1,80", 2000, DEBUG);
}
void loop() {
	//if (Serial.available()) {
	//	String txtSerial = Serial.readStringUntil('\n');
	//	esp8266.print(txtSerial);
	//}
	if (esp8266.available()) {
		//txt = esp8266.read();
		//Serial.print(txt);
		if (esp8266.find("+IPD,")) {
		     delay(1000);

		     int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns
		                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48

		     String webpage = "<h1>Hello</h1>&lth2>World!</h2><button>LED1</button>";

		     String cipSend = "AT+CIPSEND=";
		     cipSend += connectionId;
		     cipSend += ",";
		     cipSend +=webpage.length();
		     cipSend +="\r\n";

		     sendData(cipSend,1000,DEBUG);
		     sendData(webpage,1000,DEBUG);

		     webpage="<button>LED2</button>";

		     cipSend = "AT+CIPSEND=";
		     cipSend += connectionId;
		     cipSend += ",";
		     cipSend +=webpage.length();
		     cipSend +="\r\n";

		     sendData(cipSend,1000,DEBUG);
		     sendData(webpage,1000,DEBUG);

		     String closeCommand = "AT+CIPCLOSE=";
		     closeCommand+=connectionId; // append connection id
		     closeCommand+="\r\n";

		     sendData(closeCommand,3000,DEBUG);
		}
	}
}
