long tiempo;
int disparador = 9;   // triger
int entrada = 8;      // echo
float distancia;

void setup()
{
  pinMode(disparador, OUTPUT);
  pinMode(entrada, INPUT);
  
  //pinMode(9, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
  //pinMode(8, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/

  Serial.begin(9600);
}


void loop()
{
  // lanzamos un pequeño pulso para activar el sensor
  digitalWrite(disparador, HIGH);
  delayMicroseconds(10);
  digitalWrite(disparador, LOW);
  
  // medimos el pulso de respuesta
  tiempo = (pulseIn(entrada, HIGH)/2); // dividido por 2 por que es el 
                                       // tiempo que el sonido tarda
                                       // en ir y en volver
  // ahora calcularemos la distancia en cm
  // sabiendo que el espacio es igual a la velocidad por el tiempo
  // y que la velocidad del sonido es de 343m/s y que el tiempo lo 
  // tenemos en millonesimas de segundo
  distancia = float(tiempo * 0.0343);
  
  // y lo mostramos por el puerto serie una vez por segundo
  Serial.println(distancia);
  delay(1000);
}
