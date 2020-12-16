#include <Arduino.h>
#include <Servo.h>
 
Servo myservo;  // crea el objeto servo
 
int vel = 0;    // velocidad del servo
 
void setup() {
   myservo.attach(9);  // vincula el servo al pin digital 9
   Serial.begin(9600);
}
 
void loop() {
   //servo parado (equivalente a angulo 90º)
   vel = 90;
   Serial.println("En 90 a ver que tal va esto");
   myservo.write(vel);              
   delay(2500);    

   vel = 0;
   Serial.println("En 90 a ver que tal va esto");
   myservo.write(vel);              
   delay(2500);

   //servo 100% CW (equivalente a angulo 180º)
   //vel = 180;
   //Serial.println("En 180");
   //myservo.write(vel);              
   //delay(1500); 
 
   //servo 100% CCW (equivalente a angulo 0º)
   //vel = 0;
   //Serial.println("En 0");
   //myservo.write(vel);              
   //delay(1500); 
}