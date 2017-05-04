#include <SD.h>

File myFile;
int i;
int CS_PIN = 4;
int READ = 111;
int WRITE = 222;

void setup()
{  
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");
  if (!SD.begin(CS_PIN)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
  i = 0;
}

void loop() {
  i++;
  serialController();
  delay(15);
}

void serialController(){
  String comando = "";
  String compara = "RE";
  if (Serial.available() >0) {
    comando = Serial.readString();    
    Serial.print("<<" + comando);
    int cmd = comando.toInt();
    if(cmd == READ){
      Serial.println(">>Lectura de archivo ejemplo.txt");
      myFile = SD.open("in/ejemplo.txt");
      if (myFile) {        
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        myFile.close(); //cerramos el archivo
      } else {
        Serial.println("Error al abrir el archivo");
      }
    }
    if(cmd == WRITE){
      SD.mkdir("out2"); 
      Serial.print(">>Escritura de archivo ejemplo6.txt");  
      myFile = SD.open("out2/ejemplo6.txt", FILE_WRITE);
      myFile.println("Escritura de ejemplo6 i=" + String(i));
      myFile.close();
    }
    Serial.println("");
  }
  
}
