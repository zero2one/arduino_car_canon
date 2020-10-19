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
  debugStep("Setup Rotate");

  rotate_pos = servoGetMiddle();
  servoTo(ROTATE_SERVO, rotate_pos);
  debugValue("Rotation value", 90);
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

/**
   Test the rotation control.
*/
void rotateTest() {
  debugStep("Test rotate");

  for (int degrees = 60; degrees < 121; degrees += 2) {
    rotateTo(degrees);
    delay(1000);
  }

  // Back to middle.
  debugStep("Rotate back to start position");
  rotateTo(90);
  delay(1000);
}
