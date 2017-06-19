/*** Example how to use the library ***/
// Read touch screen and display data on Serial

#include <zTouchScreen.h>

// Change these to to fit your touchscreen
#define YP A1
#define XM A2
#define YM 7
#define XP 6

#define MINPRESSURE 10
#define MAXPRESSURE 1000

int TS_MINX = 0;
int TS_MINY = 0;
int TS_MAXX = 1023;
int TS_MAXY = 1023;

typedef struct {
  int x;
  int y;
} XY;

TouchScreen ts(XP, YP, XM, YM, 300);

void setup() {
  Serial.begin(9600);
  ts.InitVariable(0, 240, 320, TS_MINX, TS_MAXX, TS_MINY, TS_MAXY, MINPRESSURE, MAXPRESSURE);
  Serial.println("Start reading touch screen... ");
}

void loop() {
  TSPoint p = ts.getNextPoint(); // stop here until we get touch point
  Serial.print("\nTouch Point:  x = "); Serial.print(p.x);
  Serial.print("  y = ");Serial.println(p.y);
  Serial.print("Pressure:  z = ");Serial.println(p.z);
  delay(100);
}