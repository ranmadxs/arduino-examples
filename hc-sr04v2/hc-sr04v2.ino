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
  digitalWrite(disparador,LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
  digitalWrite(disparador, HIGH); /* envío del pulso ultrasónico*/
  delayMicroseconds(10);
  tiempo=pulseIn(entrada, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
  del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
  deja de hacerlo, LOW, la longitud del pulso entrante*/
  distancia= int(0.017*tiempo); /*fórmula para calcular la distancia obteniendo un valor entero*/
  /*Monitorización en centímetros por el monitor serial*/
  Serial.println("Distancia ");
  Serial.println(distancia);
  Serial.println(" cm");
  delay(1000);
}
