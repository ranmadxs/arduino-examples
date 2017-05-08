#include "YaiOS.h"

//https://www.w3schools.com/code/tryit.asp?filename=FFEFW96IDRHC
//https://saeedalipoor.github.io/icono/
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm
String YaiOS::getAPI(){
	return baseDocYai("html/api.htm");
}

//https://www.w3schools.com/code/tryit.asp?filename=FF03D1LDUA4N
//https://saeedalipoor.github.io/icono/
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm
String YaiOS::getAPIServo(){
	return baseDocYai("html/servo.htm");
}

String YaiOS::baseDocYai(String fileName){
	  int totalParamsPass = 1;
	  YaiParam paramsYai[totalParamsPass];
	  YaiParam yaiParam1, yaiParam2, yaiParam3, yaiParam4;
	  yaiParam1.YaiParamInit("clientIp", getClientIP());
	  yaiParam1.YaiParamInit("ROVER_STOP", String(ROVER_STOP));
	  yaiParam1.YaiParamInit("ROVER_MOVE_MANUAL_BODY", String(ROVER_MOVE_MANUAL_BODY));
	  yaiParam1.YaiParamInit("LASER_ACTION", String(LASER_ACTION));

	  paramsYai[0] = yaiParam1;
	  paramsYai[1] = yaiParam2;
	  paramsYai[2] = yaiParam3;
	  paramsYai[3] = yaiParam4;

	  String indexHtml = parseSDFile(fileName, paramsYai, totalParamsPass);
	  return indexHtml;
}

String YaiOS::getYoistickJS(){
	return baseDocYai("js/yoistick.js");
}
