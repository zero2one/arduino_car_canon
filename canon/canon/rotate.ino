/**
   Code to rotate the platform.
*/

#define ROTATE_SERVO  0

// Current position of both servos (in degrees).
uint16_t rotate_pos;

/**
   Setup the rotate servo.
*/
void rotateSetup() {
  rotate_pos = servoGetMiddle();
  servoTo(ROTATE_SERVO, rotate_pos);
}

/**
   Rotate the servo to the given number of degrees.

   @param int degrees
     The position in degrees 0-180.
*/
void rotateTo(int degrees) {
  uint16_t rotateTo;
  rotateTo = servoDegreesToPulselen(degrees);
  debugValue("Rotate to", degrees);
  
  if (rotate_pos == rotateTo) {
    debugText("Rotate is already in proper direction.");
    return;
  }

  if (rotateTo > rotate_pos) {
    for (uint16_t pulselen = rotate_pos; rotate_pos < rotateTo; rotate_pos++) {
      servoTo(ROTATE_SERVO, rotate_pos);
    }
  } else {
    for (uint16_t pulselen = rotate_pos; rotate_pos > rotateTo; rotate_pos--) {
      servoTo(ROTATE_SERVO, rotate_pos);
    }
  }
}

void rotateTest() {
  debugStep("Test rotate");
  
  rotateTo(60);
  delay(1000);
  rotateTo(70);
  delay(1000);
  rotateTo(80);
  delay(1000);
  rotateTo(90);
  delay(1000);
  rotateTo(110);
  delay(1000);
  rotateTo(120);
  delay(1000);
  
  // Back to middle.
  debugStep("Rotate back to start position");
  rotateTo(90);
  delay(1000);
}
