int digit1 = 11; //PWM Display pin 1
int digit2 = 10; //PWM Display pin 2
int digit3 = 9; //PWM Display pin 6
int digit4 = 6; //PWM Display pin 8

//Pin mapping from Arduino to the ATmega DIP28 if you need it
//http://www.arduino.cc/en/Hacking/PinMapping
int segA = A1; //Display pin 14
int segB = 3; //Display pin 16
int segC = 4; //Display pin 13
int segD = 5; //Display pin 3
int segE = A0; //Display pin 5
int segF = 7; //Display pin 11
int segG = 8; //Display pin 15

#define DISPLAY_BRIGHTNESS  500

void setup() {
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  
  pinMode(13, OUTPUT);

}

void loop() {
#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH
#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW

// Ponemos un 7 en el digito 3
  digitalWrite(digit3, DIGIT_ON);
  
  digitalWrite(segA, SEGMENT_ON);
  digitalWrite(segB, SEGMENT_ON);
  digitalWrite(segC, SEGMENT_ON);
  digitalWrite(segD, SEGMENT_OFF);
  digitalWrite(segE, SEGMENT_OFF);
  digitalWrite(segF, SEGMENT_OFF);
  digitalWrite(segG, SEGMENT_OFF);
  
  delayMicroseconds(DISPLAY_BRIGHTNESS);

  digitalWrite(digit1, DIGIT_OFF);
  digitalWrite(digit2, DIGIT_OFF);
  digitalWrite(digit3, DIGIT_OFF);
  digitalWrite(digit4, DIGIT_OFF);
  
  digitalWrite(segB, SEGMENT_OFF);
  digitalWrite(segC, SEGMENT_OFF);
  digitalWrite(segD, SEGMENT_OFF);
  digitalWrite(segE, SEGMENT_OFF);
  digitalWrite(segF, SEGMENT_OFF);
  digitalWrite(segG, SEGMENT_OFF);

  // Ponemos un cero en el digito 1
  digitalWrite(digit1, DIGIT_ON);
  
  digitalWrite(segA, SEGMENT_ON);
  digitalWrite(segB, SEGMENT_ON);
  digitalWrite(segC, SEGMENT_ON);
  digitalWrite(segD, SEGMENT_ON);
  digitalWrite(segE, SEGMENT_ON);
  digitalWrite(segF, SEGMENT_ON);
  digitalWrite(segG, SEGMENT_OFF);

  delayMicroseconds(DISPLAY_BRIGHTNESS);

  digitalWrite(digit1, DIGIT_OFF);
  digitalWrite(digit2, DIGIT_OFF);
  digitalWrite(digit3, DIGIT_OFF);
  digitalWrite(digit4, DIGIT_OFF);
  
  digitalWrite(segB, SEGMENT_OFF);
  digitalWrite(segC, SEGMENT_OFF);
  digitalWrite(segD, SEGMENT_OFF);
  digitalWrite(segE, SEGMENT_OFF);
  digitalWrite(segF, SEGMENT_OFF);
  digitalWrite(segG, SEGMENT_OFF);

  delayMicroseconds(DISPLAY_BRIGHTNESS);
}
