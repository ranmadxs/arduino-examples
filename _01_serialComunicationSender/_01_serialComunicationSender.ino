// Serial test script

int i = 0;
String readString;

void setup()
{
  pinMode(13 , OUTPUT);
  Serial.begin(9600);  // initialize serial communications at 9600 bps
  digitalWrite(13, LOW);
}

void loop()
{  
  if ( i == 1 ){
    Serial.print("1");  
    i = 0;
  }else{
    Serial.print("2");  
    i = 1;
  }
  delay(1500);
}
