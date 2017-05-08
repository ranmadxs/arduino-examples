#include "YaiOS.h"
//https://www.w3schools.com/code/tryit.asp?filename=FFEFW96IDRHC
//https://saeedalipoor.github.io/icono/
//sed -e "s/$/\\\/g" roverDoc.htm > roverDocv2.htm

String YaiOS::getAPI(){
  int totalParamsPass = 1;
  YaiParam paramsYai[totalParamsPass];
  YaiParam yaiParam;
  yaiParam.nombre = "clientIp";
  yaiParam.valor = getClientIP();

  paramsYai[0] = yaiParam;

  String indexHtml = parseSDFile("html/yaiapi.htm", paramsYai, totalParamsPass);
  return indexHtml;
}

