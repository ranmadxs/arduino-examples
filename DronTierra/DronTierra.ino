#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include "RoverLink.h"

//Derecha
static int PinOUTA   = 5; // (D1)
static int PinOUTB   = 4; // (D2)

//Izquierda
static int PinOUTC   = 0; // (D3)
static int PinOUTD   = 2; // (D4)

const char* ssid = "yai";
const char* password = "1101000000";

//const char* ssid = "VTR-YAI-5Ghz";
//const char* password = "Pana8bc1108";

String input = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
String ipESP = "";
int count= 0;
RoverLink roverLn;

DynamicJsonBuffer jsonBuffer;

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  String temp;
  temp = roverLn.getIndex();
  digitalWrite(led, 1);
  //server.send(200, "text/plain", "hello from esp8266!");
  server.send ( 200, "text/html", temp );
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
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
  digitalWrite(led, 0);
}

void setup(void){  
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(PinOUTA, OUTPUT);
  pinMode(PinOUTB, OUTPUT);
  pinMode(PinOUTC, OUTPUT);
  pinMode(PinOUTD, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(led, 1);
  Serial.begin(115200);
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

  server.on("/move", [](){
    
    digitalWrite(LED_BUILTIN, LOW);        
    if(server.args()>0){
      if(server.argName(0) == "CMD"){
        server.send(200, "text/plain", "MOVE >> " + server.arg(0)); 
        if(server.arg(0) == "FORWARD"){
          MotorAntihorario(PinOUTA, PinOUTB);
          MotorAntihorario(PinOUTC, PinOUTD);
        }
        if(server.arg(0) == "BACK"){
          MotorHorario(PinOUTA, PinOUTB);
          MotorHorario(PinOUTC, PinOUTD);          
        }        
        if(server.arg(0) == "LEFT"){
          MotorAntihorario(PinOUTA, PinOUTB);
          digitalWrite (PinOUTC, LOW);
          digitalWrite (PinOUTD, LOW);     
        }        
        if(server.arg(0) == "RIGHT"){
          MotorAntihorario(PinOUTC, PinOUTD);
          digitalWrite (PinOUTA, LOW);
          digitalWrite (PinOUTB, LOW);     
        }        
      }
    }
  });

  server.on("/stop", [](){
    MotorStop();
    digitalWrite(LED_BUILTIN, HIGH);    
    String message = "LED OFF \n\n";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    JsonObject& root = jsonBuffer.parseObject(input);
    String sensor = root["sensor"];
    String output;
    root.printTo(output);
    Serial.print(output);
    Serial.print("\n");
    for (uint8_t i=0; i<server.args(); i++){
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }    
    server.send(200, "text/plain", message);
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  count = 1;
}

void loop(void){
  server.handleClient();
  if (count == 1){
    ipESP = WiFi.localIP().toString();
    Serial.println("HTTP server listen on ip "  + ipESP);
    count = 2;
  }
}

void MotorHorario(int pin1, int pin2)
{
  digitalWrite (pin1, HIGH);
  digitalWrite (pin2, LOW);
}
void MotorAntihorario(int pin1, int pin2)
{
  digitalWrite (pin1, LOW);
  digitalWrite (pin2, HIGH);
}

void MotorStop()
{
  digitalWrite (PinOUTA, LOW);
  digitalWrite (PinOUTB, LOW);
  digitalWrite (PinOUTC, LOW);
  digitalWrite (PinOUTD, LOW);
}
