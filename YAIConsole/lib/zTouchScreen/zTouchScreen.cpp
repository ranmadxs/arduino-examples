// zTouchScreen library version 1.1
// base on TouchScreen library from ladyada / adafruit

#include "pins_arduino.h"
#include "wiring_private.h"
#include <avr/pgmspace.h>
#include "zTouchScreen.h"

// increase or decrease the touchscreen oversampling. This is a little different than you make think:
// 1 is no oversampling, whatever data we get is immediately returned
// 2 is double-sampling and we only return valid data if both points are the same
// 3+ uses insert sort to get the median value.
// We found 2 is precise yet not too slow so we suggest sticking with it!

#define NUMSAMPLES 2


// function to change the *virtual* rotation of the touched point.
TSPoint TouchScreen::RotateTSPoint (TSPoint tsp, int rotation)
{
   if (width==0 || height==0) return tsp; //  if resolution is not set
   int x = tsp.x , y = tsp.y;
   if (rotation == 1) // 90 degree
   {
      x=tsp.y;
      y=width-tsp.x;
   }
   if (rotation == 2) // 180 degree
   {
      x=width-tsp.x;
      y=height-tsp.y;
   }
   if (rotation == 3) // 270 degree
   {
      x=height-tsp.y;
      y=width-tsp.x;
   }
   return TSPoint(x, y, tsp.z);
}

TSPoint::TSPoint(void) {
  x = y = 0;
}

TSPoint::TSPoint(int16_t x0, int16_t y0, int16_t z0) {
  x = x0;
  y = y0;
  z = z0;
}

bool TSPoint::operator==(TSPoint p1) {
  return  ((p1.x == x) && (p1.y == y) && (p1.z == z));
}

bool TSPoint::operator!=(TSPoint p1) {
  return  ((p1.x != x) || (p1.y != y) || (p1.z != z));
}

#if (NUMSAMPLES > 2)
static void insert_sort(int array[], uint8_t size) {
  uint8_t j;
  int save;
  
  for (int i = 1; i < size; i++) {
    save = array[i];
    for (j = i; j >= 1 && save < array[j - 1]; j--)
      array[j] = array[j - 1];
    array[j] = save; 
  }
}
#endif


// mode 
// = 0 
void TouchScreen::InitVariable(uint8_t _rotate, uint16_t _width, uint16_t _height, uint16_t _min_x, uint16_t _max_x, uint16_t _min_y, uint16_t _max_y)
{
  min_x = _min_x;
  max_x = _max_x;
  min_y = _min_y;
  max_y = _max_y;
  rotation = _rotate;
  width = _width;
  height = _height;
}
void TouchScreen::InitVariable(uint8_t _rotate, uint16_t _width, uint16_t _height, uint16_t _min_x, uint16_t _max_x, uint16_t _min_y, uint16_t _max_y, uint16_t _min_pressure, uint16_t _max_pressure)
{
  min_x = _min_x;
  max_x = _max_x;
  min_y = _min_y;
  max_y = _max_y;
  rotation = _rotate;
  width = _width;
  height = _height;
  min_pressure = _min_pressure;
  max_pressure = _max_pressure;
}

// default = 0 // portrait
void TouchScreen::Rotate(uint8_t _rotate) 
{
    if (_rotate > 3 || _rotate < 0) rotation = 0;
    else rotation = _rotate;
}

void TouchScreen::SetResolution(uint16_t _width, uint16_t _height) // Pixels in portrait mode - rotation =  0
{
  width = _width;
  height = _height;
}

void TouchScreen::SetMinMaxXY(uint16_t _min_x, uint16_t _max_x, uint16_t _min_y, uint16_t _max_y)
{
  min_x = _min_x;
  max_x = _max_x;
  min_y = _min_y;
  max_y = _max_y;
}

void TouchScreen::SetPressure(uint16_t _min_pressure, uint16_t _max_pressure)
{
  if (_max_pressure ==0) _max_pressure = 1000;
  min_pressure = _min_pressure;
  max_pressure = _max_pressure;
}


TSPoint TouchScreen::getNextPoint() {
  TSPoint p = getNextRawPoint();
  if (width ==0 || height ==0) return p; // if resolution is not set return RawTSpoint
  
  // scale to the real resolution of TFT
  p.x = width-(map(p.x, min_x, max_x, width, 0));
  p.y = height-(map(p.y, min_y, max_y, height, 0));
  
  return RotateTSPoint (p,  rotation);
}

TSPoint TouchScreen::getNextRawPoint() {
  int max_p=  max_pressure, min_p = min_pressure;
  if (min_p == 0) min_p = pressureThreshhold;
  if (max_p == 0 || max_p <= min_p) max_p = 1023;
  TSPoint p;
  do {
    p = getRawPoint();
    pinMode(_xm, OUTPUT);
    pinMode(_yp, OUTPUT);
  }
  while(!(p.z > min_p && p.z < max_p));
  return p;
}


TSPoint TouchScreen::getPoint(void) {
  TSPoint p = getRawPoint();
  if (width ==0 || height ==0) return p; // if resolution is not set return rawTSpoint
  
  // scale to the real resolution of TFT
  p.x = width-(map(p.x, min_x, max_x, width, 0));
  p.y = height-(map(p.y, min_y, max_y, height, 0));
  
  return RotateTSPoint (p,  rotation);
}

TSPoint TouchScreen::getRawPoint(void) {
  int x, y, z;
  int samples[NUMSAMPLES];
  uint8_t i, valid;
  

  uint8_t xp_port = digitalPinToPort(_xp);
  uint8_t yp_port = digitalPinToPort(_yp);
  uint8_t xm_port = digitalPinToPort(_xm);
  uint8_t ym_port = digitalPinToPort(_ym);

  uint8_t xp_pin = digitalPinToBitMask(_xp);
  uint8_t yp_pin = digitalPinToBitMask(_yp);
  uint8_t xm_pin = digitalPinToBitMask(_xm);
  uint8_t ym_pin = digitalPinToBitMask(_ym);


  valid = 1;

  pinMode(_yp, INPUT);
  pinMode(_ym, INPUT);
  
  *portOutputRegister(yp_port) &= ~yp_pin;
  *portOutputRegister(ym_port) &= ~ym_pin;
  //digitalWrite(_yp, LOW);
  //digitalWrite(_ym, LOW);
   
  pinMode(_xp, OUTPUT);
  pinMode(_xm, OUTPUT);
  //digitalWrite(_xp, HIGH);
  //digitalWrite(_xm, LOW);
  *portOutputRegister(xp_port) |= xp_pin;
  *portOutputRegister(xm_port) &= ~xm_pin;
   
   for (i=0; i<NUMSAMPLES; i++) {
     samples[i] = analogRead(_yp);
   }
#if NUMSAMPLES > 2
   insert_sort(samples, NUMSAMPLES);
#endif
#if NUMSAMPLES == 2
   if (samples[0] != samples[1]) { valid = 0; }
#endif
   //x = samples[NUMSAMPLES/2]; //moded
   x = (1023-samples[NUMSAMPLES/2]); //original
   pinMode(_xp, INPUT);
   pinMode(_xm, INPUT);
   *portOutputRegister(xp_port) &= ~xp_pin;
   //digitalWrite(_xp, LOW);
   
   pinMode(_yp, OUTPUT);
   *portOutputRegister(yp_port) |= yp_pin;
   //digitalWrite(_yp, HIGH);
   pinMode(_ym, OUTPUT);
  
   for (i=0; i<NUMSAMPLES; i++) {
     samples[i] = analogRead(_xm);
   }

#if NUMSAMPLES > 2
   insert_sort(samples, NUMSAMPLES);
#endif
#if NUMSAMPLES == 2
   if (samples[0] != samples[1]) { valid = 0; }
#endif

  // y = samples[NUMSAMPLES/2]; //moded
   y = (1023-samples[NUMSAMPLES/2]); //original
   // Set X+ to ground
   pinMode(_xp, OUTPUT);
   *portOutputRegister(xp_port) &= ~xp_pin;
   //digitalWrite(_xp, LOW);
  
   // Set Y- to VCC
   *portOutputRegister(ym_port) |= ym_pin;
   //digitalWrite(_ym, HIGH); 
  
   // Hi-Z X- and Y+
   *portOutputRegister(yp_port) &= ~yp_pin;
   //digitalWrite(_yp, LOW);
   pinMode(_yp, INPUT);
  
   int z1 = analogRead(_xm); 
   int z2 = analogRead(_yp);

   if (_rxplate != 0) {
     // now read the x 
     float rtouch;
     rtouch = z2;
     rtouch /= z1;
     rtouch -= 1;
     rtouch *= x;
     rtouch *= _rxplate;
     rtouch /= 1024;
     
     z = rtouch;
   } else {
     z = (1023-(z2-z1));
   }

   if (! valid) {
     z = 0;
   }

   return TSPoint(x, y, z);
}

TouchScreen::TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym) {
  _yp = yp;
  _xm = xm;
  _ym = ym;
  _xp = xp;
  _rxplate = 0;
  /*
  width = 240; 
  height = 320; //resolution in portrait view // rotation =0
  */
  rotation = 0;
  pressureThreshhold = 10;
}


TouchScreen::TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rxplate) {
  _yp = yp;
  _xm = xm;
  _ym = ym;
  _xp = xp;
  _rxplate = rxplate;
  rotation = 0;
  pressureThreshhold = 10;
}


int TouchScreen::readTouchX(void) {
  int16_t x = readRawTouchX();
  if (width == 0 || height == 0) return x;  // no resolution is set, return raw value
  x = width-(map(x, min_x, max_x, width, 0));
  return x;
}


int TouchScreen::readTouchY(void) {
  int16_t y = readRawTouchY();
  if (width == 0 || height == 0) return y;  // no resolution is set, return raw value
  y = height-(map(y, min_y, max_y, height, 0));
  return y;
}


int TouchScreen::readRawTouchX(void) {
   pinMode(_yp, INPUT);
   pinMode(_ym, INPUT);
   digitalWrite(_yp, LOW);
   digitalWrite(_ym, LOW);
   
   pinMode(_xp, OUTPUT);
   pinMode(_xm, OUTPUT);
   digitalWrite(_xp, HIGH);
   digitalWrite(_xm, HIGH);
   
  switch (rotation)
  {
    case 1: // lanscape
      return (1023-analogRead(_xm)); // return y coordinate
    case 2: // potrait 180
      return analogRead(_yp); // return x coordinate which rotation 180
    case 3: // lanscape 180
      return analogRead(_xm); // return y coordinate which rotation 180
    case 0: // potrait
    default:
      return (1023-analogRead(_yp)); // return x coordinate
  }
}


int TouchScreen::readRawTouchY(void) {
   pinMode(_xp, INPUT);
   pinMode(_xm, INPUT);
   digitalWrite(_xp, LOW);
   digitalWrite(_xm, LOW);
   
   pinMode(_yp, OUTPUT);
   pinMode(_ym, OUTPUT);
   digitalWrite(_yp, HIGH);
   digitalWrite(_ym, HIGH);
   
  switch (rotation)
  {
    case 1: // lanscape
      return (1023-analogRead(_yp)); // return x coordinate 
    case 2: // potrait 180
      return analogRead(_xm); // return y coordinate which rotation 180
    case 3: // lanscape 180
      return analogRead(_yp); // return x coordinate which rotation 180
    case 0: // potrait
    default:
      return (1023-analogRead(_xm)); // return y coordinate
  }
}


uint16_t TouchScreen::pressure(void) {
  // Set X+ to ground
  pinMode(_xp, OUTPUT);
  digitalWrite(_xp, LOW);
  
  // Set Y- to VCC
  pinMode(_ym, OUTPUT);
  digitalWrite(_ym, HIGH); 
  
  // Hi-Z X- and Y+
  digitalWrite(_xm, LOW);
  pinMode(_xm, INPUT);
  digitalWrite(_yp, LOW);
  pinMode(_yp, INPUT);
  
  int z1 = analogRead(_xm); 
  int z2 = analogRead(_yp);

  if (_rxplate != 0) {
    // now read the x 
    float rtouch;
    rtouch = z2;
    rtouch /= z1;
    rtouch -= 1;
    rtouch *= readTouchX();
    rtouch *= _rxplate;
    rtouch /= 1024;
    
    return rtouch;
  } else {
    return (1023-(z2-z1));
  }
}
