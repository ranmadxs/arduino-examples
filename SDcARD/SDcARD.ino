#include <SD.h>

File myFile;
int i;
void setup()
{
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
  i = 0;
}

void loop() {
  myFile = SD.open("datalog.txt", FILE_WRITE);//abrimos  el archivo
  i++;
  /*
  if (myFile) {
    Serial.println("Escribiendo SD: ");
    myFile.print("Tiempo(ms)=");
    myFile.print(String(millis()) + ", ");
    myFile.print("Contador (i)=");
    myFile.println(String(i));
    myFile.close(); //cerramos el archivo
  }else {
    Serial.println("Error al abrir el archivo");
  }
  */
  delay(100);
}
