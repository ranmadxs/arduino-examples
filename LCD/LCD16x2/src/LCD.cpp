//Sample using LiquidCrystal library
#include <LiquidCrystal.h>
#include <Arduino.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

String ejemploResp = "{\"RESULT\":\"OK\", \"CONTENT\":{\"IP\":\"192.168.0.23\", \"MAC\":\"5C:CF:7F:13:41:DA\"}}";
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  String strLine;
  Serial.println("LCD Ready");
  lcd.setCursor(0,0);
  strLine = ejemploResp.substring(0, 16);
  lcd.print(strLine);
  Serial.println(strLine);
  lcd.setCursor(0,1);
  strLine = ejemploResp.substring(16, 32);
  Serial.println(strLine);
  lcd.print(strLine);
}

void loop() {
	String serialIn;
	if (Serial.available() >0) {
		serialIn = Serial.readStringUntil('\n');
		if (serialIn.length() >0){

		}
	}
}
