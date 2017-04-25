#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include "YaiOS.h"

const int totalWifi = 3;
const int retryWifi = 15;

char* arrayWifi[totalWifi][2] = {
  {"yai", "1101000000"},
  {"VTR-YAI-5Ghz", "Pana8bc1108"},
  {"GalaxyJ1", "1101000000"}
};

YaiOS yaiOS;

ESP8266WebServer server(80);

void handleRoot() {
  String htmlSrc;
  htmlSrc = yaiOS.getIndex();
  server.send ( 200, "text/html", htmlSrc );
}

void handleJS() {
  String htmlSrc;
  htmlSrc = yaiOS.getJS();
  server.send ( 200, "application/javascript", htmlSrc );
}

void handleAPI(){
	  String htmlSrc;
	  htmlSrc = yaiOS.getAPI();
	  server.send ( 200, "text/html", htmlSrc );
}

void handleRoverJoystick(){
    String htmlSrc;
    htmlSrc = yaiOS.getRoverJoystick();
    server.send ( 200, "text/html", htmlSrc );
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
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(PinOUTA, OUTPUT);
  pinMode(PinOUTB, OUTPUT);
  pinMode(PinOUTC, OUTPUT);
  pinMode(PinOUTD, OUTPUT);
  pinMode(PinLaser, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  //Serial.begin(115200);
  Serial.begin(9600);
  Serial.println("");

  char* ssid;
  char* password;

//  while (WiFi.status() != WL_CONNECTED) {
  for (int j = 0; j<totalWifi; j++){
	  Serial.print("Conectando a " + String(arrayWifi[j][0]) + " ");
      ssid = arrayWifi[j][0];
      password = arrayWifi[j][1];
      WiFi.begin(ssid, password);
      for (int k = 0; k < retryWifi; k++){
    	  if(WiFi.status() == WL_CONNECTED){
    		  k = retryWifi;
    		  j = totalWifi;
    		  Serial.print(" Conectado!!!");
    	  }else{
    		  delay(500);
    		  Serial.print(".");
    	  }
      }
      Serial.println("");
  }
//  }
  Serial.println("");
  Serial.print("Connected to: ");
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

  server.on("/yai.js", handleJS);

  server.on("/roverJoystick", handleRoverJoystick);

  server.on("/cmd", [](){
    String message = "";
    String jsonCommand = "{";
    for (uint8_t i=0; i<server.args(); i++){
      jsonCommand += "\""+server.argName(i) + "\":\"" + server.arg(i)+"\"";
      if(i + 1 < server.args()){
        jsonCommand += ", ";
      }
    }    
    jsonCommand += "}";
    message += " << " + jsonCommand;
    String responseMsg = yaiOS.executeCommand(jsonCommand);        
    message += "\n \n >> " + responseMsg;
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
