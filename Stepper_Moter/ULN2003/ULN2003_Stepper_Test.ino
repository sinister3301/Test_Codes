/*
  Stepper Motor Test using ULN2003 Driver and 28BYJ-48 Motor
  ----------------------------------------------------------
  This Arduino sketch tests the 28BYJ-48 stepper motor using the ULN2003 driver board.
  It rotates the motor one full revolution clockwise and then one full revolution counterclockwise.

  ** TESTED & WORKING **

  Features:
  - Simple test of motor rotation in both directions
  - Adjustable speed via `setSpeed()`
  - Uses built-in Arduino Stepper library

  Hardware Requirements:
  - Arduino board (Uno, Nano, etc.)
  - 28BYJ-48 Stepper Motor
  - ULN2003 Stepper Driver Board
  - Jumper wires and 5V power supply

  Library Requirements:
  - Stepper (included with Arduino IDE)

 
          PIN CONNECTION 

+----------------+--------------------+
| ULN2003 IN Pin | Connects To Nano   |
+----------------+--------------------+
| IN1            | D8                 |
| IN2            | D9                 |
| IN3            | D10                |
| IN4            | D11                |
| VCC            | 5V*                |  * Try to Connect Vcc of ULN2003 Directly to 5v Power Supply For Enough Current
| GND            | GND                |
+----------------+--------------------+

Author - FAIZUL  
DATE   - 21 JUNE 2025
*/

#include <Stepper.h>

// Define number of steps per full revolution (for 28BYJ-48 with gearbox)
const int stepsPerRevolution = 2048;  // 2048 steps ≈ 1 full rotation

// Create Stepper object using IN1-IN4 pins connected to ULN2003
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // Set motor speed in RPM
  myStepper.setSpeed(10);  // Try 5–15 for smooth operation

  // Start serial monitor (optional for debug)
  Serial.begin(9600);
  Serial.println("Stepper motor test starting...");
}

void loop() {
  Serial.println("Rotating clockwise...");
  myStepper.step(stepsPerRevolution);  // One full revolution clockwise
  delay(1000);

  Serial.println("Rotating counterclockwise...");
  myStepper.step(-stepsPerRevolution); // One full revolution counterclockwise
  delay(1000);
}
