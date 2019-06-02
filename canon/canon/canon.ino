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

  debugStep("Setup Canon");
  launchSetup();
  servoSetup();
  rotateSetup();
  elevateSetup();

  delay(2000);
  debugStep("Setup canon : OK");
}

/**
 * Run the application.
 */
void loop() {
  launchTest();
  rotateTest();
  elevateTest();
}
