// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <RGBmatrixPanel.h>

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

//#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

void setup() {

     matrix.begin();

}

void left(){
  // draw left arrow (yellow)
while(true){
  matrix.fillRect(21, 11, 11, 10, matrix.Color333(7, 3, 0));
  delay(250);
  matrix.fillRect(15, 11, 11, 10, matrix.Color333(7, 3, 0));
  delay(250); 

  for (int i=0; i < 15; i++){
   matrix.drawLine(i, 15-i, i, 15+i, matrix.Color333(7, 3, 0));
    }

  delay(1000); 
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(250); 
}
}
void right(){
 while(true){
  matrix.fillRect(0, 11, 11, 10, matrix.Color333(7, 3, 0));
  delay(250); 
  matrix.fillRect(6, 11, 11, 10, matrix.Color333(7, 3, 0));
  delay(250);

  for (int i=0; i < 15; i++){
   matrix.drawLine(15+i, 32-i, 15+i,i, matrix.Color333(7, 3, 0));
    }

  delay(1000); 
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(250); 
}
}
void stopNow(){
  matrix.fillScreen(matrix.Color333(7, 0, 0)); 
  delay(1000); 
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(500); 
   matrix.fillScreen(matrix.Color333(7, 0, 0)); 
  delay(1000); 
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(500); 
}

void biking(){
  matrix.fillScreen(matrix.Color333(7, 7, 0)); 
  delay(1000); 
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(500); 
   matrix.fillScreen(matrix.Color333(7, 7, 0)); 
  delay(1000); 
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(500); 
}

void loop() {
  biking(); 
}
