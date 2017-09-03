#include <Arduino.h> 
#include <Servo.h>

Servo myservo;

int pos = 0;

//pinout
// cafe -> tierra
// rojo -> vcc 5+
// naranjo -> signal

void setup() {
  myservo.attach(6);

}

void loop() {
  myservo.write(180);
  delay(500);
  myservo.write(90);
  delay(500);
  myservo.write(45);
  delay(500);
  myservo.write(0);
  delay(500);
  myservo.write(45);  
  delay(500);
  myservo.write(90);  
  delay(500);  
    
//for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees
//  {                                  // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees
//  {
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
}
