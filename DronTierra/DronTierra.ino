#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
//#include "RoverLink.h"
#include "YaiOS.h"

//const char* ssid = "yai";
//const char* password = "1101000000";

const char* ssid = "VTR-YAI-5Ghz";
const char* password = "Pana8bc1108";

YaiOS yaiOS;

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  String htmlSrc;
  htmlSrc = yaiOS.getIndex();
  digitalWrite(led, 1);
  server.send ( 200, "text/html", htmlSrc );
  digitalWrite(led, 0);
}

void handleJS() {
  String htmlSrc;
  htmlSrc = yaiOS.getJS();
  digitalWrite(led, 1);
  server.send ( 200, "text/html", htmlSrc );
  digitalWrite(led, 0);  
}

void handleAPI(){
	  String htmlSrc;
	  htmlSrc = yaiOS.getAPI();
	  digitalWrite(led, 1);
	  server.send ( 200, "text/html", htmlSrc );
	  digitalWrite(led, 0);
}

void handleRoverJoystick(){
    String htmlSrc;
    htmlSrc = yaiOS.getRoverJoystick();
    digitalWrite(led, 1);    
    server.send ( 200, "text/html", htmlSrc );
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
  Serial.print("Connected to");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  yaiOS.setClientIP(WiFi.localIP().toString());
  yaiOS.setMac(WiFi.macAddress());
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/api", handleAPI);

  server.on("/jquery", handleJS);

  server.on("/roverJoystick", handleRoverJoystick);

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
    for (uint8_t i=0; i<server.args(); i++){
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }    
    server.send(200, "text/plain", message);
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");  
}

void loop(void){
  server.handleClient();
  serialController();
}

void serialController(){
  String serialIn = "";
  int command = 0;
  if (Serial.available() >0) {
    serialIn = Serial.readString();    
    if (serialIn.length() >0){
      yaiOS.executeCommand(serialIn);
    }
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
