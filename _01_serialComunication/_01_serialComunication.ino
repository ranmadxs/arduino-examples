// Serial test script

int setPoint = 55;
String readString;

void setup()
{
  pinMode(13 , OUTPUT);
  Serial.begin(9600);  // initialize serial communications at 9600 bps
  digitalWrite(13, LOW);
}

void loop()
{
  String command = "";
  while(!Serial.available()) {}
  while (Serial.available()) {
    if (Serial.available() >0) {
      Serial.print("Arduino received: ");  
      command = Serial.readString();
      Serial.println(command);           
    }
  }

  if (command.toInt() == 1){
    Serial.print("WIIIIIIIIIIIIIIIIII");
    digitalWrite(13, HIGH);
  }else{
    digitalWrite(13, LOW);
  }
  Serial.flush();

  delay(500);
}
