/*************************************************************************
 * Canon code.
 *************************************************************************/

#include <Wire.h>

/**
 * Adafruit Servo Board.
 */
#include <Adafruit_PWMServoDriver.h>

/**
 * Setup the program.
 */
void setup() {
  serialSetup();
  
  servoSetup();
  rotateSetup();
  elevateSetup();
}

/**
 * Run the application.
 */
void loop() {
  rotateTest();
  elevateTest();
}
