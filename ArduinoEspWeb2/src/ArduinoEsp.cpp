#include <Arduino.h>
#include <SoftwareSerial.h>

#define DEBUG true
int connectionId;
SoftwareSerial Serial1(3, 2); // RX | TX

//////////////gets the data from esp and displays in serial monitor///////////////////////
String sendData(String command, const int timeout, boolean debug) {
	String response = "";
	Serial1.print(command);
	long int time = millis();
	while ((time + timeout) > millis()) {
		while (Serial1.available()) {
			char c = Serial1.read(); // read the next character.
			response += c;
		}
	}

	if (debug) {
		Serial.print(response); //displays the esp response messages in arduino Serial monitor
	}
	return response;
}

//////////////////////////////sends data from ESP to webpage///////////////////////////

void espsend(String d) {
	String cipSend = " AT+CIPSEND=";
	cipSend += connectionId;
	cipSend += ",";
	cipSend += d.length();
	cipSend += "\r\n";
	sendData(cipSend, 1000, DEBUG);
	sendData(d, 1000, DEBUG);
}


void setup() {
	Serial.begin(115200);    ///////For Serial monitor
	Serial1.begin(115200); ///////ESP Baud rate
	pinMode(11, OUTPUT);    /////used if connecting a LED to pin 11
	digitalWrite(11, LOW);

	//sendData("AT+RST\r\n", 2000, DEBUG); // reset module
	//sendData("AT+CWMODE=2\r\n", 1000, DEBUG); // configure as access point
	sendData("AT+CIPMUX=1\r\n", 2000, DEBUG);
	sendData("AT+CIPSERVER=1,80\r\n", 2000, DEBUG);
	sendData("AT+CIFSR\r\n", 2000, DEBUG);
	sendData("AT+GMR\r\n", 2000, DEBUG);
}

float sensetemp() ///////function to sense temperature.
{
	int val = analogRead(A0);
	float mv = (val / 1024.0) * 5000;
	float celcius = mv / 10;
	return (celcius);
}

void loop() {
	if (Serial1.available()) {
		if(Serial1.find("+IPD,"))
		    {
		     delay(1000);

		     int connectionId = Serial1.read()-48; // subtract 48 because the read() function returns
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
