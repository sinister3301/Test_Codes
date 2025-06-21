/*

  OLED Animation Showcase using U8g2 Library
  ------------------------------------------
  This Arduino sketch displays a series of animated effects on a 128x64 OLED 
  screen (either SH1106 or SSD1306) using the U8g2 graphics library.

  ** TESTED & WORKING **

  Supported Displays:
  - SH1106 128x64 I2C OLED (default)
  - SSD1306 128x64 I2C OLED (uncomment in code to enable)

  Animations Included:
  1. Spinner: Rotating bar symbol
  2. Eyes: Eyes moving left and right
  3. Heartbeat: Pulsing heart shape
  4. Rotating Cube: Simple 3D cube effect
  5. Flame: Flickering flame symbol

  Features:
  - Automatically switches animations every 5 seconds
  - Clean animation rendering using u8g2 buffer drawing
  - Lightweight and beginner-friendly animations

  Hardware Requirements:
  - Arduino board (Uno, Nano, etc.)
  - 128x64 OLED display (SH1106 or SSD1306, I2C)
  - I2C wiring (SDA and SCL)

  Library Requirements:
  - U8g2 by olikraus: https://github.com/olikraus/u8g2

 
          PIN CONNECTION 

+----------------+--------------------+
| OLED Pin Label | Connects To Nano   |
+----------------+--------------------+
| VCC            | 5V                 | 
| GND            | GND                |
| SDA            | A4                 |
| SCL            | A5                 | 
+----------------+--------------------+

Author - FAIZUL
DATE   - 21 JUNE 2025

*/




#include <U8g2lib.h>
#include <Wire.h>

// --------- SELECT YOUR DISPLAY ---------
// Uncomment your OLED type
#define OLED_TYPE_SH1106
// #define OLED_TYPE_SSD1306

// --------- DISPLAY CONSTRUCTOR ---------
#ifdef OLED_TYPE_SH1106
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);
#elif defined(OLED_TYPE_SSD1306)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);
#else
#error "Please define OLED_TYPE_SH1106 or OLED_TYPE_SSD1306"
#endif

// --------- ANIMATION VARIABLES ---------
unsigned long startTime;
int currentAnimation = 0;

// Spinner
int spinnerAngle = 0;
const char spinnerPattern[] = {'|', '/', '-', '\\'};

// Eyes
int eyeOffset = 0;

// Heartbeat
int heartSize = 10;
bool growing = true;

// Cube
int cubeAngle = 0;

// Flame
int flameFrame = 0;
const char* flamePatterns[] = {
  "*", "^", "~", "+"
};

void setup() {
  u8g2.begin();
  startTime = millis();
}

void loop() {
  u8g2.clearBuffer();

  switch (currentAnimation) {
    case 0: drawSpinner(); break;
    case 1: drawEyes(); break;
    case 2: drawHeartbeat(); break;
    case 3: drawCube(); break;
    case 4: drawFlame(); break;
  }

  u8g2.sendBuffer();
  delay(100);

  // Switch animation every 5 seconds
  if (millis() - startTime > 5000) {
    currentAnimation = (currentAnimation + 1) % 5;
    startTime = millis();
  }
}

// --------- ANIMATION FUNCTIONS ---------

// 1. Loading Spinner
void drawSpinner() {
  u8g2.setFont(u8g2_font_logisoso16_tr);
  u8g2.setCursor(60, 40);
  u8g2.print(spinnerPattern[spinnerAngle % 4]);
  spinnerAngle++;
}

// 2. Moving Eyes
void drawEyes() {
  eyeOffset = (millis() / 200) % 5;

  u8g2.drawCircle(40, 32, 10);  // Left eye white
  u8g2.drawCircle(88, 32, 10);  // Right eye white

  u8g2.drawDisc(40 + eyeOffset, 32, 3); // Left pupil
  u8g2.drawDisc(88 - eyeOffset, 32, 3); // Right pupil
}

// 3. Heartbeat
void drawHeartbeat() {
  if (growing) heartSize++; else heartSize--;
  if (heartSize > 18) growing = false;
  if (heartSize < 10) growing = true;

  drawHeart(64, 32, heartSize);
}

void drawHeart(int x, int y, int size) {
  u8g2.drawDisc(x - size / 3, y - size / 3, size / 3);
  u8g2.drawDisc(x + size / 3, y - size / 3, size / 3);
  u8g2.drawTriangle(x - size, y - size / 3,
                    x + size, y - size / 3,
                    x, y + size);
}

// 4. 3D Rotating Cube (pseudo)
void drawCube() {
  int angle = (millis() / 100) % 360;

  int cx = 64;
  int cy = 32;
  int s = 10;
  int offset = (angle % 20) - 10;

  u8g2.drawFrame(cx - s, cy - s, 2 * s, 2 * s);                     // Front
  u8g2.drawFrame(cx - s + offset, cy - s - offset, 2 * s, 2 * s);   // Back

  // Connect corners
  u8g2.drawLine(cx - s, cy - s, cx - s + offset, cy - s - offset);
  u8g2.drawLine(cx + s, cy - s, cx + s + offset, cy - s - offset);
  u8g2.drawLine(cx - s, cy + s, cx - s + offset, cy + s - offset);
  u8g2.drawLine(cx + s, cy + s, cx + s + offset, cy + s - offset);
}

// 5. Flame Flicker
void drawFlame() {
  u8g2.setFont(u8g2_font_helvB24_tf);
  u8g2.setCursor(54, 48);
  u8g2.print(flamePatterns[flameFrame % 4]);
  flameFrame++;
}
