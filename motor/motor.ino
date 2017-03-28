int PinIN1 = 7;
int PinIN2 = 6;

void setup() {
  // inicializar la comunicación serial a 9600 bits por segundo:
  Serial.begin(9600);
  // configuramos los pines como salida
  pinMode(PinIN1, OUTPUT);
  pinMode(PinIN2, OUTPUT);
}

void loop() {
  
  MotorHorario();
  Serial.println("Giro del Motor en sentido horario");
  delay(500);
  
  MotorAntihorario();
  Serial.println("Giro del Motor en sentido antihorario");
  delay(500);
  
  MotorStop();
  Serial.println("Motor Detenido");
  delay(2000);
  
}

void MotorHorario()
{
  digitalWrite (PinIN1, HIGH);
  digitalWrite (PinIN2, LOW);
}
void MotorAntihorario()
{
  digitalWrite (PinIN1, LOW);
  digitalWrite (PinIN2, HIGH);
}

void MotorStop()
{
  digitalWrite (PinIN1, LOW);
  digitalWrite (PinIN2, LOW);
}
