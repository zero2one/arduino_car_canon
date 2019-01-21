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

// Motorshield.
#include <Adafruit_MotorShield.h>

// ------------------------------------------------------------------------



// App config -------------------------------------------------------------

// Default speeds.
#define MOTOR_SPEED_FORWARD 100
#define MOTOR_SPEED_TURN 100

// ------------------------------------------------------------------------



/**
 * Setup the program.
 */
void setup() {
  serialSetup();
  displaySetup();
  compassSetup();
  distanceSetup();
  motorSetup();
}

/**
 * Run the application.
 */
void loop() {
  int dir = compassGetDirection();

  motorTurnAroundRight(MOTOR_SPEED_TURN);
  delay(50);
  
  int current = compassGetDirection();
  while (dir != current) {
    current = compassGetDirection();
    distanceGet();
    delay(100);
  }

  motorAllStop();

  int time = 0;
  while(time < 10000) {
    compassGetDirection();
    distanceGet();
    time++;
  }
}
