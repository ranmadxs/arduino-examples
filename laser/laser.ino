int sensorPin = A0;
int sensorValue = 0;

void setup ()
{
   pinMode (2, OUTPUT); // define the digital output interface 13 feet
   Serial.begin(9600);
}
void loop () {
   digitalWrite (2, HIGH); // open the laser head
   delay (20);
   sensorValue = analogRead(sensorPin);
   float voltage= sensorValue * (5.0 / 1023.0);
   Serial.println(voltage);
   delay (500); // delay one second
   digitalWrite (2, LOW); // turn off the laser head
   delay (500); // delay one second
}
