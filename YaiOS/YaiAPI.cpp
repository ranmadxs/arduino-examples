#include "YaiOS.h"

// https://unpkg.com/purecss@0.6.2/build/base-min.css
// https://purecss.io/tables/
//TODO: HTML PIPELINE ACA
//https://www.w3schools.com/code/tryit.asp?filename=FFN34JDG39I0


//https://www.w3schools.com/code/tryit.asp?filename=FFEFW96IDRHC
//https://saeedalipoor.github.io/icono/
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm
String YaiOS::getAPI(){
	YaiParseFile parseFile = baseSDTemplate("html/api.htm");
	return parseFile.content;
}

//https://www.w3schools.com/code/tryit.asp?filename=FFEO7P26WP4M
//https://saeedalipoor.github.io/icono/
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm
String YaiOS::getAPIServo(){
	YaiParseFile parseFile = baseSDTemplate("html/servo.htm");
	return parseFile.content;
}

// https://www.w3schools.com/code/tryit.asp?filename=FFG2SFC8SXW0
//https://codepen.io/sampeniak/pen/Imhpy
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm
// Reversa sed s'/.$//' roverDoc.htm > roverDocv2.htm

String YaiOS::getRoverJoystick(){
	YaiParseFile parseFile = baseSDTemplate("html/yoistick.htm");
	return parseFile.content;
}

//https://www.w3schools.com/code/tryit.asp?filename=FFFGAIJLXX0Y
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm
//http://patorjk.com/software/taag/
//Font Name: Slant Relif
//Font Name: Small Slant
String YaiOS::getIndex(){
	YaiParseFile parseFile = baseSDTemplate("html/index.htm");
	return parseFile.content;
}


YaiParseFile YaiOS::baseSDTemplate(String fileName){
	  int totalParamsPass = 17;
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
	  yaiParam.nombre = "SERVO_ACTION_CONTINUOUS";
	  yaiParam.valor = String(SERVO_ACTION_CONTINUOUS);
	  paramsYai[10] = yaiParam;
	  yaiParam.nombre = "SERVO_STOP";
	  yaiParam.valor = String(SERVO_STOP);
	  paramsYai[11] = yaiParam;
	  yaiParam.nombre = "SERVO_CLOCKWISE";
	  yaiParam.valor = String(SERVO_CLOCKWISE);
	  paramsYai[12] = yaiParam;
	  yaiParam.nombre = "SERVO_COUNTER_CLOCKWISE";
	  yaiParam.valor = String(SERVO_COUNTER_CLOCKWISE);
	  paramsYai[13] = yaiParam;
	  yaiParam.nombre = "SERVO_DIRECTION_HORIZONTAL";
	  yaiParam.valor = String(SERVO_DIRECTION_HORIZONTAL);
	  paramsYai[14] = yaiParam;
	  yaiParam.nombre = "SERVO_DIRECTION_VERTICAL";
	  yaiParam.valor = String(SERVO_DIRECTION_VERTICAL);
	  paramsYai[15] = yaiParam;
	  yaiParam.nombre = "SERVO_DIRECTION_ALL";
	  yaiParam.valor = String(SERVO_DIRECTION_ALL);
	  paramsYai[16] = yaiParam;
	  YaiParseFile indexHtml = parseSDFile(fileName, paramsYai, totalParamsPass);
	  return indexHtml;
}
