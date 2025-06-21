/*

 OLED Display Hello World Example
  ---------------------------------
  This Arduino sketch demonstrates how to use the U8g2 library to display
  text on a 128x64 SH1106 OLED display using I2C (0x3C) communication.

  Hardware:
  - Arduino board (e.g., Uno, Nano)
  - SH1106 128x64 OLED display (I2C interface)
  - Connections: SDA and SCL pins connected to Arduino I2C pins

  Functionality:
  - Initializes the OLED display
  - Clears the display buffer
  - Sets a bold font
  - Displays the text "Hello OLED!" at position (0, 30)
  - Updates the display every 2 seconds

  Library Dependencies:
  - U8g2 (by olikraus): https://github.com/olikraus/u8g2


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


#include <Wire.h>
#include <U8g2lib.h>

// Try this for SH1106 128x64 via I2C
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

void setup() {
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(0, 30, "Hello OLED!");
  u8g2.sendBuffer();
  delay(2000);
}
