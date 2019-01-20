/*************************************************************************
 * 
 * Robot test script.
 * 
 * This will test out the attached boards.
 *************************************************************************/

// Libraries -------------------------------------------------------------

// I2C library.
#include <Wire.h>

// OLED display.
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// Gyroscope/compass/direction.
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>

// ------------------------------------------------------------------------


/**
 * Setup the program.
 */
void setup() {
  serialSetup();
  displaySetup();
  compassSetup();

  displayDummy();
}

/**
 * Run the application.
 */
void loop() {
  displayDirection(compassGetDirection());
  delay(100);
}
