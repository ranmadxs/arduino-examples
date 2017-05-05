/*
 6-13-2011
 Spark Fun Electronics 2011
 Nathan Seidle
 
 This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 4 digit 7 segment display:
 http://www.sparkfun.com/products/9483
 Datasheet: 
 http://www.sparkfun.com/datasheets/Components/LED/7-Segment/YSD-439AR6B-35.pdf

 This is an example of how to drive a 7 segment LED display from an ATmega without the use of current limiting resistors.
 This technique is very common but requires some knowledge of electronics - you do run the risk of dumping too 
 much current through the segments and burning out parts of the display. If you use the stock code you should be ok, but 
 be careful editing the brightness values.
 
 This code should work with all colors (red, blue, yellow, green) but the brightness will vary from one color to the next
 because the forward voltage drop of each color is different. This code was written and calibrated for the red color.

 This code will work with most Arduinos but you may want to re-route some of the pins.

 7 segments
 4 digits
 1 colon
 =
 12 pins required for full control 
 
 */
#include <Arduino.h>
void setup(){
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(13, LOW);
  digitalWrite(10, LOW);
}

void loop(){
  String command = "";
  while(!Serial.available()) {}
  while (Serial.available()) {
    if (Serial.available() >0) {
      command = Serial.readString();     
    }
  }
  
  if (command.length() >0){
    Serial.print("Arduino received: ");  
    Serial.println(command);
    if(command == "YL69"){
      Serial.print("[");
      lectorYL69(A0, 2);
      Serial.print(", ");
      lectorYL69(A1, 3);
      Serial.print(", ");
      lectorYL69(A2, 4);
      Serial.print("]");      
    }
    if(command == "LED_RED"){
      digitalWrite(13, HIGH);
    }
    if(command == "LED_GREEN"){
      digitalWrite(10, HIGH);
    }
    if(command == "LIGHT_OFF"){
      digitalWrite(10, LOW);
      digitalWrite(13, LOW);
    }    
  }

  delay(500);
}

void lectorYL69(int apin, int dpin){
  //Serial.println("Init YL69");
  int aout = analogRead(apin);
  String dout, desc;
  Serial.print("{\"ao\":");
  Serial.print(aout, DEC);
  if(digitalRead(dpin)==LOW){
    dout = "0";
    desc = "HUMEDO";
  }else{
    dout = "1";
    desc = "SECO";
  }
  Serial.print(", \"do\":"+dout+", \"desc\":\""+desc+"\", \"apin\":"+apin+", \"dpin\":"+dpin+"}");  
}

// (-100/1023) * medida + 100
