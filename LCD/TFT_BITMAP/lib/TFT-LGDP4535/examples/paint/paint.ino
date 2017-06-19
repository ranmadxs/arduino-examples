/*******************************************************
Example 4: Painter , paint with touch screen
File version: 1.1
Update: fix for using CeezTouchScreen lib
*******************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <LGDP4535.h> // Hardware-specific library
#include <zTouchScreen.h>

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

// You need to calibrate to fit your LCD
#define TS_MINX 895
#define TS_MINY 941
#define TS_MAXX 180
#define TS_MAXY 180

#define MINPRESSURE 10
#define MAXPRESSURE 1000


// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Assign human-readable names to some common 16-bit color values:
#define BLACK           0x0000      /*   0,   0,   0 */
#define NAVY            0x000F      /*   0,   0, 128 */
#define DARKGREEN       0x03E0      /*   0, 128,   0 */
#define DARKCYAN        0x03EF      /*   0, 128, 128 */
#define MAROON          0x7800      /* 128,   0,   0 */
#define PURPLE          0x780F      /* 128,   0, 128 */
#define OLIVE           0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY       0xC618      /* 192, 192, 192 */
#define DARKGREY        0x7BEF      /* 128, 128, 128 */
#define BLUE            0x001F      /*   0,   0, 255 */
#define TURQUOISE       0x04AF      /*   0,   0, 255 */
#define GREEN           0x07E0      /*   0, 255,   0 */
#define CYAN            0x07FF      /*   0, 255, 255 */
#define RED             0xF800      /* 255,   0,   0 */
#define MAGENTA         0xF81F      /* 255,   0, 255 */
#define YELLOW          0xFFE0      /* 255, 255,   0 */
#define WHITE           0xFFFF      /* 255, 255, 255 */
#define ORANGE          0xFD20      /* 255, 165,   0 */
#define GREENYELLOW     0xAFE5      /* 173, 255,  47 */
#define PINK            0xF81F

LGDP4535 tft;

#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;

void setup(void) {

  // initiate these variable for calculation correct point
  ts.InitVariable(0, 240, 320, TS_MINX, TS_MAXX, TS_MINY, TS_MAXY);

  Serial.begin(9600);
  Serial.println(F("TFT LCD test - TFT Paint"));

  tft.reset();

  uint16_t identifier = tft.readID();

  Serial.print(F("LCD driver chip: "));
  Serial.println(identifier, HEX);

  if (identifier == 0x4535)
    Serial.println(F("Using the library LGDP4535.\nRun the sample now"));
  else Serial.println(F("This is not the driver chip LGDP4535.\nForce using library LGDP4535..."));

  tft.begin();

  tft.fillScreen(BLACK);

  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
  tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
  tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
  tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
  tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);

  tft.fillRect(0, 279, BOXSIZE, BOXSIZE, TURQUOISE);
  tft.fillRect(BOXSIZE, 279, BOXSIZE, BOXSIZE, ORANGE);
  tft.fillRect(BOXSIZE * 2, 279, BOXSIZE, BOXSIZE, LIGHTGREY);
  tft.fillRect(BOXSIZE * 3, 279, BOXSIZE, BOXSIZE, DARKGREY);
  tft.fillRect(BOXSIZE * 4, 279, BOXSIZE, BOXSIZE, WHITE);
  tft.fillRect(BOXSIZE * 5, 279, BOXSIZE, BOXSIZE, BLACK);
  // tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, WHITE);

  tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
  currentcolor = RED;

  pinMode(13, OUTPUT);
}


void loop()
{
  TSPoint p = ts.getPoint();

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  bool colorchange = 0;

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    //   /*
    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);
    //    */

    Serial.print("("); Serial.print(p.x);
    Serial.print(", "); Serial.print(p.y);
    Serial.println(")");
    //*/
    if (p.y < BOXSIZE) {
      oldcolor = currentcolor;
      colorchange = 1;
      if (p.x < BOXSIZE) {
        currentcolor = RED;
        tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (p.x < BOXSIZE * 2) {
        currentcolor = YELLOW;
        tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (p.x < BOXSIZE * 3) {
        currentcolor = GREEN;
        tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (p.x < BOXSIZE * 4) {
        currentcolor = CYAN;
        tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (p.x < BOXSIZE * 5) {
        currentcolor = BLUE;
        tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (p.x < BOXSIZE * 6) {
        currentcolor = MAGENTA;
        tft.drawRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, WHITE);
      }
    } else if (p.y > 279) {
      colorchange = 1;
      oldcolor = currentcolor;
      if (p.x < BOXSIZE) {
        currentcolor = TURQUOISE;
        tft.drawRect(0, 279, BOXSIZE, BOXSIZE, WHITE);
      } else if (p.x < BOXSIZE * 2) {
        currentcolor = ORANGE;
        tft.drawRect(BOXSIZE, 279, BOXSIZE, BOXSIZE, WHITE);
      } else if (p.x < BOXSIZE * 3) {
        currentcolor = LIGHTGREY;
        tft.drawRect(BOXSIZE * 2, 279, BOXSIZE, BOXSIZE, WHITE);
      } else if (p.x < BOXSIZE * 4) {
        currentcolor = DARKGREY;
        tft.drawRect(BOXSIZE * 3, 279, BOXSIZE, BOXSIZE, WHITE);
      } else if (p.x < BOXSIZE * 5) {
        currentcolor = WHITE;
        tft.drawRect(BOXSIZE * 4, 279, BOXSIZE, BOXSIZE, BLACK);
      } else if (p.x < BOXSIZE * 6) {
        currentcolor = BLACK;
        tft.drawRect(BOXSIZE * 5, 279, BOXSIZE, BOXSIZE, WHITE);
      }
    }
    if (oldcolor != currentcolor && colorchange == 1) {
      colorchange = 0;
      if (oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
      if (oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
      if (oldcolor == GREEN) tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
      if (oldcolor == CYAN) tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
      if (oldcolor == BLUE) tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
      if (oldcolor == MAGENTA) tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);
      if (oldcolor == TURQUOISE) tft.fillRect(0, 279, BOXSIZE, BOXSIZE, TURQUOISE);
      if (oldcolor == ORANGE) tft.fillRect(BOXSIZE, 279, BOXSIZE, BOXSIZE, ORANGE);
      if (oldcolor == LIGHTGREY) tft.fillRect(BOXSIZE * 2, 279, BOXSIZE, BOXSIZE, LIGHTGREY);
      if (oldcolor == DARKGREY) tft.fillRect(BOXSIZE * 3, 279, BOXSIZE, BOXSIZE, DARKGREY);
      if (oldcolor == WHITE) tft.fillRect(BOXSIZE * 4, 279, BOXSIZE, BOXSIZE, WHITE);
      if (oldcolor == BLACK) tft.fillRect(BOXSIZE * 5, 279, BOXSIZE, BOXSIZE, BLACK);
    }

    if (((p.y - PENRADIUS) > BOXSIZE) && ((p.y + PENRADIUS) < tft.height()-BOXSIZE)) {
      tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
    }
  }
}
