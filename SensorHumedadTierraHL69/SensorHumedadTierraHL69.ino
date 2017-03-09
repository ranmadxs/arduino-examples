//Sensor Humedad Tierra HL-69

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 int ao0 = analogRead(A0);
 String do2;
 String desc;
 Serial.print("{'ao':");
 Serial.print(ao0, DEC);
 if(digitalRead(2)==LOW){
   do2 = "0";
   desc = "HUMEDO";
 }else{
   do2 = "1";
   desc = "SECO";
 }
 Serial.println(", 'do':"+do2+", 'desc':'"+desc+"'}");
 //Serial.println("{'ao':"+ao0+", 'do':"+do2+", 'desc':'"+desc+"'}");
 delay(500);
 
}
