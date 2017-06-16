#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>

ESP8266WebServer webServer(80);

#define WIFI_STATION_SSID 	"VTR-YAI-5Ghz"
#define WIFI_STATION_KEY 	"Pana8bc1108"
#define WIFI_AP_SSID		"ESP_WIFI"
#define MDNS_NAME 			"XDD"

void setup()
{
    Serial.begin(9600);

    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(WIFI_STATION_SSID, WIFI_STATION_KEY);
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }

    IPAddress apLocalIp(192, 168, 50, 1);
    IPAddress apSubnetMask(255, 255, 255, 0);
    WiFi.softAPConfig(apLocalIp, apLocalIp, apSubnetMask);
    WiFi.softAP(WIFI_AP_SSID);

    // Setup OTA, SPIFFS, webServer ...

    webServer.onNotFound([](){
        webServer.send(404, "text/plain", "File not found!");
    });
    webServer.begin();
    Serial.println("Ready webServer");
    Serial.println("Client ip:" + WiFi.localIP().toString());
    Serial.println("Server ip:" + apLocalIp.toString());

    MDNS.begin(MDNS_NAME); // Return value was allways true while my tests
    MDNS.addService("http", "tcp", 80);
}

void loop()
{
    webServer.handleClient();
}
