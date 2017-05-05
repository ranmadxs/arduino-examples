#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SD.h>

const char* ssid = "VTR-YAI-5Ghz";
const char* password = "Pana8bc1108";

File myFile;
int i;
int CS_PIN = 4;
int READ = 111;
int WRITE = 222;

ESP8266WebServer server(80);

void handleRoot() {
  Serial.println(">> >> handleRoot de archivo html/pagina.htm");
  myFile = SD.open("html/pagina.htm");
  String SD_Read = "";
  char ltr;
  if (myFile) {
      while (myFile.available()) {
    	  ltr = myFile.read();
    	  SD_Read += ltr;
      }
  }else {
      Serial.println("Error al abrir el archivo handleRoot");
  }


  //server.send(myFile);
  myFile.close();
  server.send(200, "text/html", SD_Read);
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void){
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  Serial.print("Iniciando SD ...");
  if (!SD.begin(CS_PIN)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
  i = 0;
}

void loop(void){
  server.handleClient();
  serialController();
}

void serialController(){
  String comando = "";
  String compara = "RE";
  if (Serial.available() >0) {
    comando = Serial.readString();
    Serial.print("<<" + comando);
    Serial.println(">>Lectura de archivo html/pagina.htm");
    myFile = SD.open("html/pagina.htm");
    if (myFile) {
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        myFile.close(); //cerramos el archivo
      } else {
        Serial.println("Error al abrir el archivo");
      }
    
  }

}
