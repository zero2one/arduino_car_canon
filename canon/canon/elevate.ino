/**
   Code to elevate the canon.
*/

#define ELEVATE_SERVO  4

uint16_t elevate_pos;

/**
   Setup the elevate servo.
*/
void elevateSetup() {
  debugStep("Setup Elevate");

  elevate_pos = servoGetMax();
  servoTo(ELEVATE_SERVO, elevate_pos);
  debugValue("Elevation value", 0);
}

/**
   Elevate the servo to the given number of degrees.

   @param int degrees
     The position in degrees 0-75.
*/
void elevateTo(int degrees) {
  if (degrees > 75) {
    debugError("Elevation may not be bigger then 75°!");
    return;
  }

  debugValue("Elevate to", degrees);
  degrees = 180 - degrees;

  uint16_t elevateTo;
  elevateTo = servoDegreesToPulselen(degrees);

  if (elevate_pos == rotateTo) {
    debugText("Rotate is already in proper direction.");
    return;
  }

  if (elevateTo > elevate_pos) {
    for (uint16_t pulselen = elevate_pos; elevate_pos < elevateTo; elevate_pos++) {
      servoTo(ELEVATE_SERVO, elevate_pos);
    }
  } else {
    for (uint16_t pulselen = elevate_pos; elevate_pos > elevateTo; elevate_pos--) {
      servoTo(ELEVATE_SERVO, elevate_pos);
    }
  }
}

/**
   Test the elevate servo.
*/
void elevateTest() {
  debugStep("Test elevate");
  for (int degrees = 0; degrees < 31; degrees += 2) {
    elevateTo(degrees);
    delay(1000);
  }

  debugStep("Elevate back to start position");
  elevateTo(0);
  delay(1000);
}
