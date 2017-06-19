This library for driver chip LGDP4535
Using Adafruit_GFX library to render pixels on the TFT

Note:
- Touch screen is on the opposiste orentiation with TFT
- LGDP4535 use 3v3 signal input, so 5v signal output from UNO won't work unless using a level shifter like 74HC245
- For Arduino Mega, comment line 14 and uncomment line 14 of file LGDP4535.cpp