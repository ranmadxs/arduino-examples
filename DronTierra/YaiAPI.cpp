#include "YaiOS.h"

//https://www.w3schools.com/code/tryit.asp?filename=FFEFW96IDRHC
//https://saeedalipoor.github.io/icono/
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm
String YaiOS::getAPI(){
	return baseDocYai("html/api.htm");
}

//https://www.w3schools.com/code/tryit.asp?filename=FFEO7P26WP4M
//https://saeedalipoor.github.io/icono/
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm
String YaiOS::getAPIServo(){
	return baseDocYai("html/servo.htm");
}

// https://www.w3schools.com/code/tryit.asp?filename=FFEVLFSD602O
//https://codepen.io/sampeniak/pen/Imhpy
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm
// Reversa sed s'/.$//' roverDoc.htm > roverDocv2.htm

String YaiOS::getRoverJoystick(){
	return baseDocYai("html/yoistick.htm");
}

String YaiOS::getYoistickJS(){
	return baseDocYai("js/yoistick.js");
}

String YaiOS::baseDocYai(String fileName){
	  int totalParamsPass = 10;
	  YaiParam paramsYai[totalParamsPass];
	  YaiParam yaiParam;
	  yaiParam.nombre = "clientIp";
	  yaiParam.valor = getClientIP();
	  paramsYai[0] = yaiParam;
	  yaiParam.nombre = "ROVER_STOP";
	  yaiParam.valor = String(ROVER_STOP);
	  paramsYai[1] = yaiParam;
	  yaiParam.nombre = "ROVER_MOVE_MANUAL_BODY";
	  yaiParam.valor = String(ROVER_MOVE_MANUAL_BODY);
	  paramsYai[2] = yaiParam;
	  yaiParam.nombre = "LASER_ACTION";
	  yaiParam.valor = String(LASER_ACTION);
	  paramsYai[3] = yaiParam;
	  yaiParam.nombre = "SERVO_TYPE_SG90";
	  yaiParam.valor = String(SERVO_TYPE_SG90);
	  paramsYai[4] = yaiParam;
	  yaiParam.nombre = "ROVER_BODY_MOVE_TYPE_LEFT";
	  yaiParam.valor = String(ROVER_BODY_MOVE_TYPE_LEFT);
	  paramsYai[5] = yaiParam;
	  yaiParam.nombre = "ROVER_BODY_MOVE_TYPE_RIGHT";
	  yaiParam.valor = String(ROVER_BODY_MOVE_TYPE_RIGHT);
	  paramsYai[6] = yaiParam;
	  yaiParam.nombre = "ROVER_BODY_MOVE_TYPE_BACK";
	  yaiParam.valor = String(ROVER_BODY_MOVE_TYPE_BACK);
	  paramsYai[7] = yaiParam;
	  yaiParam.nombre = "ROVER_BODY_MOVE_TYPE_FORWARD";
	  yaiParam.valor = String(ROVER_BODY_MOVE_TYPE_FORWARD);
	  paramsYai[8] = yaiParam;
    yaiParam.nombre = "ROVER_TYPE_2WD";
    yaiParam.valor = String(ROVER_TYPE_2WD);
    paramsYai[9] = yaiParam;

	  String indexHtml = parseSDFile(fileName, paramsYai, totalParamsPass);
	  return indexHtml;
}
