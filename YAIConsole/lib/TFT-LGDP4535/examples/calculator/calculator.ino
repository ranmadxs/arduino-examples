/***********************************************************
Example 6: Calculator
File version: 1.1
Update: using CeezTouchScreen lib
Description: fix number
************************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <LGDP4535.h>        // Hardware-specific library
#include <zTouchScreen.h>

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// If using the shield, all control and data lines are fixed
LGDP4535 tft;

#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

// your calibrated value should look like this
#define TS_MINX 895
#define TS_MINY 941
#define TS_MAXX 180
#define TS_MAXY 180


// un-comment this line to enable blue dot on touch point
//#define DEBUG

#define PENRADIUS 3
#define MINPRESSURE 10
#define MAXPRESSURE 1000
// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

int matrix[5][4] =
{ {15, 16, 12, 24},
  {1, 2, 3, 23},
  {4, 5, 6, 22},
  {7, 8, 9, 21},
  {0, 10, 11, 21}
}
;

char matrixc[5][4] =
{ {'O', 'C', '<', '/'},
  {'1', '2', '3', '*'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '+'},
  {'0', '.', '=', ' '}
}
;

float result, input, mem1;
byte op, dot, no;
boolean in;

void setup(void) 
{
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));
  
  // initiate these variable for calculation correct point
  ts.InitVariable(0, 240, 320, TS_MINX, TS_MAXX, TS_MINY, TS_MAXY, MINPRESSURE, MAXPRESSURE);

  tft.reset();

  uint16_t identifier = tft.readID();
  Serial.print(F("LCD driver chip: "));
  Serial.println(identifier, HEX);
  if (identifier == 0x4535)
    Serial.println(F("Using the library LGDP4535.\n\nPress the keypad to display number:"));
  else Serial.println(F("This is not the driver chip LGDP4535.\nForce using library LGDP4535..."));
  Serial.println();
  tft.begin();
  drawGUI();
  input = 0;
  showInput();
}

void drawGUI()
{
  tft.fillScreen(BLACK);
  int i, j;

  for (i = 0; i <= 3; i++)
    tft.drawFastHLine(1, 58 + i * 52, 238, WHITE);
  tft.drawFastHLine(1, 58 + 4 * 52, 178, WHITE);
  tft.drawFastHLine(1, 58 + 5 * 52, 238, WHITE);

  for (i = 0; i <= 3; i++)
    tft.drawFastVLine(1 + i * 59, 58, 266, WHITE);
  tft.drawFastVLine(238, 58, 260, WHITE);

  for (j = 0; j < 5; j++)
    for (i = 0; i < 4; i++)
    {
      switch (matrixc[j][i])
      {
        case 'O':
          tft.drawChar(58 * i + 14, 58 + 52 * j + 16, 'A', RED, BLACK, 3);
          tft.drawChar(58 * i + 32, 58 + 52 * j + 16, 'C', RED, BLACK, 3);
          continue;
        case '<':
          tft.drawChar(58 * i + 14, 58 + 52 * j + 16, '<', YELLOW, BLACK, 3);
          tft.drawChar(58 * i + 29, 58 + 52 * j + 16, '-', YELLOW, BLACK, 3);
          continue;
        case '+':
          tft.drawChar(58 * i + 22, 100 + 52 * j, matrixc[j][i], YELLOW, BLACK, 3);
          continue;
        default:
          tft.drawChar(58 * i + 22, 58 + 52 * j + 16, matrixc[j][i], YELLOW, BLACK, 3);
      }
    }
}

void calc(byte _op, float _input, float _mem1)
{
  switch (_op)
  {
    case 1:
      result = _mem1 + _input;
      break;
    case 2:
      result = _mem1 - _input;
      break;
    case 3:
      result = _mem1 * _input;
      break;
    case 4:
      result = _mem1 / _input;
      break;
  }
  showResult();
}

void showInput()
{
  tft.fillRect(1, 10, 220, 40, BLACK);
  tft.setCursor(1, 10),
                tft.setTextColor(GREEN, BLACK);
  tft.setTextSize(3);
  tft.print(input);
}

void showResult()
{
  tft.fillRect(1, 10, 220, 40, BLACK);
  tft.setCursor(1, 10),
                tft.setTextColor(GREEN, BLACK);
  tft.setTextSize(3);
  tft.print(result);
}

void showOper()
{
  tft.fillRect(220, 10, 240, 40, BLACK);
  tft.setCursor(220, 10),
                tft.setTextColor(GREEN, BLACK);
  tft.setTextSize(3);
  if (op == 1) tft.print("+");
  if (op == 2) tft.print("-");
  if (op == 3) tft.print("*");
  if (op == 4) tft.print("/");
}

void loop(void) {
  // Recently Point was renamed TSPoint in the TouchScreen library
  // If you are using an older version of the library, use the
  // commented definition instead.
  // Point p = ts.getPoint();
  int x, y;
  static int anterior = 0, actual;
  static unsigned long int tanterior = 0, tactual = 0;
  TSPoint p = ts.getPoint();

  //pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //pinMode(YM, OUTPUT);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {

    x = (4 * p.x) / tft.width(); //0 - 3
    y = (5 * (p.y - 52)) / (tft.height() - 52); // 0 - 5

    actual = matrix[y][x];
    tactual = millis();
    if (tactual - tanterior > 1000)
    {
      tanterior = tactual;
      anterior = -1;
    }

    if (actual != anterior )
    {
      Serial.println(actual);
      anterior = actual;

      // we get "actual" as our touchpoint result
      // and map it with our matrix and matrixc to decide
      // the pressed button

      switch (actual)
      {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
          if (in == false) input = 0;
          in = true;

          if (dot > 0 && dot < 3)
          {
            no = 9;
            int deci = 1;
            for (int i = 1; i <= dot; i++) deci = deci * 10; // deci = 10 ^ dot
            input = input + (float)actual / deci;
            dot++;
          }
          else if (no < 9)
            input = input * 10 + actual;


          showInput();
          break;

        case 15: //AC
          input = 0;
          mem1 = 0;
          result = 0;
          op = 0;
          showOper();
          in = true;
          dot = 0;
          no = 0;
          showInput();
          break;

        case 16: //C
          input = 0;
          //in = true;
          dot = 0;
          no = 0;
          showInput();
          break;

        case 12: // <--
          // working on it later
          break;

        case 21:// OPERATOR
        case 22:
        case 23:
        case 24:
          in = false;
          dot = 0;
          no = 0;
          mem1 = input;
          op = actual - 20;
          showOper();
          break;

        case 10: //dot
          // working on it later
          if (dot == 0)
          {
            dot = 1;
            no++;
          }

          showInput();
          break;

        case 11: // =
          if (op > 0) //on current operation
            calc(op, input, mem1);
          op = 0;
          dot = 0;
          no = 0;
          showOper();
          mem1 = result;
          input = result;
          showResult();
          in = false;
          break;
      }

#ifdef DEBUG
      tft.fillCircle(p.x, p.y, PENRADIUS, BLUE);
#endif
    }


  }
}

