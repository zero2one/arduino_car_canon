/**
   Code to elevate the canon.
*/

#define ELEVATE_SERVO  1

uint16_t elevate_pos;

/**
   Setup the elevate servo.
*/
void elevateSetup() {
  elevate_pos = servoGetMax();
  servoTo(ELEVATE_SERVO, elevate_pos);
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

void elevateTest() {
  debugStep("Test elevate");
  
  elevateTo(0);
  delay(1000);
  elevateTo(4);
  delay(1000);
  elevateTo(8);
  delay(1000);
  elevateTo(12);
  delay(1000);
  elevateTo(16);
  delay(1000);
  elevateTo(20);
  delay(1000);
  elevateTo(24);
  delay(1000);
  elevateTo(28);
  delay(1000);
  elevateTo(32);
  delay(1000);
  
  // Back to start.
  debugStep("Elevate back to start position");
  elevateTo(0);
  delay(1000);
}
