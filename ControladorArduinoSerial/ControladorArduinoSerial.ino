// Controlador Serial Arduino
#include <Print.h>
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
      char c = Serial.read();
      command += c;        
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
