#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <Wire.h>
#include "YaiOS.h"
#include "YaiCommunicator.h"

/*
 * Main.cpp
 *

 *  Created on: 23-05-2017
 *      Author: esanchez
 */

const byte DNS_PORT = 53;
IPAddress apLocalIp(192, 168, 50, 1);
IPAddress apSubnetMask(255, 255, 255, 0);
DNSServer dnsServer;
boolean connectedWifi = false;
const int totalWifi = 3;
const int retryWifi = 17;
#define apSsid "YaiDNSServer"

char* arrayWifi[totalWifi][2] = {
		{ "yai", "1101000000" },
		{ "VTR-YAI-5Ghz", "Pana8bc1108" },
		{ "GalaxyJ1", "1101000000" } };

YaiOS yaiOS;
YaiUtil yaiUtil;
YaiCommunicator yaiCommunicator;

YaiCommand commandFactoryExecute(YaiCommand yaiCommand){
	YaiCommand yaiResCmd;
	if (yaiCommand.execute) {
		if(yaiCommand.print){
			Serial.print("<< ");  //-> Esto se transforma en log debug
			Serial.println(yaiCommand.message);
		}
		yaiResCmd = yaiOS.executeCommand(yaiCommand);
		yaiResCmd = yaiCommunicator.propagateCommand(yaiResCmd);
	}
	return yaiResCmd;
}

void serialController() {
	YaiCommand yaiResCmd;
	YaiCommand yaiCommand;
	yaiCommand = yaiUtil.commandSerialFilter();
	yaiResCmd = commandFactoryExecute(yaiCommand);
	if(yaiResCmd.type == String(YAI_COMMAND_TYPE_RESULT)){
		Serial.print(">> ");
		Serial.println(yaiResCmd.json);
	}
}

ESP8266WebServer server(80);

void handleRoot() {
	String htmlSrc;
	htmlSrc = yaiOS.getIndex();
	server.send(200, "text/html", htmlSrc);
}

void handleAPI() {
	String htmlSrc;
	htmlSrc = yaiOS.getAPI();
	server.send(200, "text/html", htmlSrc);
}

void handleAPIServo() {
	String htmlSrc;
	htmlSrc = yaiOS.getAPIServo();
	server.send(200, "text/html", htmlSrc);
}

void handleRoverJoystick() {
	String htmlSrc;
	htmlSrc = yaiOS.getRoverJoystick();
	server.send(200, "text/html", htmlSrc);
}

void handleNotFound() {
	String content_type = "text/plain";
	String message = "File Not Found\n\n";
	int codeStatus = 404;
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += (server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";
	for (uint8_t i = 0; i < server.args(); i++) {
		message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
	}

	YaiParseFile yaiFile = yaiOS.baseSDTemplate(server.uri());
	if (yaiFile.fileExist) {
		message = yaiFile.content;
		content_type = yaiFile.contentType;
		codeStatus = yaiFile.codeStatus;
	}
	server.send(codeStatus, content_type, message);
}

void setup(void) {

	//Serial.begin(115200);
	Serial.begin(9600);
	WiFi.mode(WIFI_AP_STA);
	Serial.println("");
	Serial.println(" ##########################################");
	Serial.println(" ################ YaiRover ################");
	Serial.println(" ##########################################");
	yaiOS.initSD();
	yaiOS.logInfo("SD card connected");
	Wire.begin(I2C_MASTER_SDA_PIN, I2C_MASTER_SCL_PIN);
	Wire.setClockStretchLimit(15000);
	String masterWireLog = "I2C MasterBus " + String(MAX_I2C_COMAND)
			+ " Bytes ready!";
	Serial.println(masterWireLog);
	yaiOS.logInfo(masterWireLog);
	boolean resWire = yaiCommunicator.scannI2CClient(I2C_CLIENT_YAI_MOTOR);
	if (resWire) {
		yaiOS.logDebug(
				"I2C [OK] connected to Yai Motor on address 0x0"
						+ String(I2C_CLIENT_YAI_MOTOR));
	} else {
		yaiOS.logWarn(
				"I2C Not connected to Yai Motor on address 0x0"
						+ String(I2C_CLIENT_YAI_MOTOR));
	}
	resWire = yaiCommunicator.scannI2CClient(I2C_CLIENT_YAI_SERVO);
	if (resWire) {
		yaiOS.logDebug(
				"I2C [OK] connected to Yai Servo on address 0x0"
						+ String(I2C_CLIENT_YAI_SERVO));
	} else {
		yaiOS.logWarn(
				"I2C Not connected to Yai Servo on address 0x0"
						+ String(I2C_CLIENT_YAI_SERVO));
	}

	char* ssid;
	char* password;

	for (int j = 0; j < totalWifi; j++) {
		Serial.print("Conectando a " + String(arrayWifi[j][0]) + " ");
		ssid = arrayWifi[j][0];
		password = arrayWifi[j][1];
		WiFi.begin(ssid, password);
		for (int k = 0; k < retryWifi; k++) {
			if (WiFi.status() == WL_CONNECTED) {
				k = retryWifi;
				j = totalWifi;
				connectedWifi = true;
				Serial.print(" Conectado!!!");
			} else {
				delay(500);
				Serial.print(".");
			}
		}
		Serial.println("");
	}
	String yaiIP = WiFi.localIP().toString();
	if (!connectedWifi) {
		ssid = "None";
	}

    WiFi.softAPConfig(apLocalIp, apLocalIp, apSubnetMask);
    WiFi.softAP(apSsid);
	dnsServer.setTTL(300);
	dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
	dnsServer.start(DNS_PORT, "yairover.ddns.com", apLocalIp);
	Serial.println("DNS Server OK ip:" + apLocalIp.toString() );
	Serial.println("ssid:" + String(apSsid));
	yaiOS.setServerIP(apLocalIp.toString());
	yaiOS.setServerSsid(String(apSsid));

	Serial.print("Connected to: ");
	Serial.println(ssid);
	yaiOS.logInfo("Connected to: " + String(ssid));
	Serial.print("IP address: ");
	Serial.println(yaiIP);
	yaiOS.setClientIP(yaiIP);
	yaiOS.setMac(WiFi.macAddress());
	if (MDNS.begin("esp8266")) {
		Serial.println("MDNS responder started");
	}
	MDNS.addService("http", "tcp", 80);
	yaiOS.logInfo("IP: " + yaiOS.getClientIP());

	server.on("/", handleRoot);
	server.on("/api", handleAPI);
	server.on("/apiServo", handleAPIServo);
	server.on("/roverJoystick", handleRoverJoystick);
	server.on("/cmd",
			[]() {
				String message = "";
				String jsonCommand = "";
				for (uint8_t i=0; i<server.args(); i++) {
					jsonCommand += server.arg(i);
					if(i + 1 < server.args()) {
						jsonCommand += ",";
					}
				}
				message += " << " + jsonCommand;
				YaiCommand yaiCommand;
				yaiCommand.type = String(YAI_COMMAND_TYPE_SERIAL);
				yaiCommand.message = jsonCommand;
				yaiUtil.string2YaiCommand(yaiCommand);
				YaiCommand yaiCmdResp = commandFactoryExecute(yaiCommand);
				String responseMsg = yaiCmdResp.json;
				message += "\n" + responseMsg;
				server.sendHeader("Access-Control-Allow-Origin", "*");
				server.sendHeader("Access-Control-Allow-Methods", "POST,GET,OPTIONS");
				server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");

				server.send(200, "text/plain", message);
			});

	server.on("/pipelineCmd", [] {
		String message = "{\""+String(YAI_COMMAND_TYPE_RESULT)+"\":\"OK\"";
		int totalCmds = 0;
		String responseMsg = "\"EXECUTE\":0";
		if(server.args() > 0) {
			String pipeline[server.args()];
			for (uint8_t i=0; i<server.args(); i++) {
				pipeline[i] = server.arg(i);
				totalCmds++;
			}
			responseMsg = yaiOS.executeCommand(pipeline, totalCmds);
		}
		message += ", \"PIPELINE\":{\"TOTAL_IN\":"+String(totalCmds);
		message += ", " + responseMsg + "}";
		server.send(200, "text/plain", message);
	});

	server.onNotFound(handleNotFound);

	server.begin();
	Serial.println("HTTP server started");
	yaiOS.logInfo("HTTP server started");
}

void loop(void) {
	//if (!connectedWifi) {
		dnsServer.processNextRequest();
	//}
	server.handleClient();
	serialController();
}
