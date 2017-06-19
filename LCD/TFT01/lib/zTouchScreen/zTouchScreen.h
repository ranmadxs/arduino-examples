// zTouchScreen library version 1.1
// base on TouchScreen library from ladyada / adafruit

#ifndef _ADAFRUIT_TOUCHSCREEN_H_
#define _ADAFRUIT_TOUCHSCREEN_H_
#include <stdint.h>

class TSPoint {
 public:
  TSPoint(void);
  TSPoint(int16_t x, int16_t y, int16_t z);
  
  bool operator==(TSPoint);
  bool operator!=(TSPoint);

  int16_t x, y, z;
};

class TouchScreen {
 public:
  TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym);
  TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym, uint16_t rx);
  void InitVariable(uint8_t _rotate, uint16_t _width, uint16_t _height, uint16_t _min_x, uint16_t _max_x, uint16_t _min_y, uint16_t _max_y);
  void InitVariable(uint8_t _rotate, uint16_t _width, uint16_t _height, uint16_t _min_x, uint16_t _max_x, uint16_t _min_y, uint16_t _max_y, uint16_t _min_pressure, uint16_t _max_pressure);
  void Rotate(uint8_t _rotate = 0); // default = 0 // portrait
  
  void SetResolution(uint16_t _width, uint16_t _height); // Pixels in portrait mode - rotate =  0
  void SetMinMaxXY(uint16_t _min_x, uint16_t _max_x, uint16_t _min_y, uint16_t _max_y);
  void SetPressure(uint16_t _min_pressure, uint16_t _max_pressure);
  
  bool isTouching(void);
  uint16_t pressure(void);

  int readTouchY();
  int readTouchX();
  TSPoint getPoint();
  TSPoint getNextPoint();   // stop everything and wait for touch screen
  
  int readRawTouchY();
  int readRawTouchX();
  TSPoint getRawPoint();
  TSPoint getNextRawPoint(); // stop everything and wait for touch screen
  
  int16_t pressureThreshhold;


private:
  uint8_t rotation;  // Portrait = 0
  uint16_t width;        // Pixels in portrait mode - mode 0
  uint16_t height;       // Pixels in portrait mode - mode 0
  uint16_t min_x;        // The limit 
  uint16_t max_x;        // The limit 
  uint16_t min_y;        // The limit 
  uint16_t max_y;        // The limit 
  uint16_t min_pressure;        // The limit 
  uint16_t max_pressure;        // The limit 
  
  uint8_t _yp, _ym, _xm, _xp;
  uint16_t _rxplate;
  TSPoint RotateTSPoint(TSPoint tsp, int rotate);
};

#endif
