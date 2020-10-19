/**
   Launch code.

   Code to launch the ball.
*/

// Launch motor connected to IO 9.
#define LAUNCH_MOTOR_PIN 2

/**
   Setup the launch motor control.
*/
void launchSetup() {
  debugStep("Setup Launch");

  pinMode(LAUNCH_MOTOR_PIN, OUTPUT);
  launchOff();
}

/**
   Put the launch motor on.
*/
void launchOn() {
  debugValue("Launch motor", String("On"));
  digitalWrite(LAUNCH_MOTOR_PIN, HIGH);
}

/**
   Put the launch motor off.
*/
void launchOff() {
  debugValue("Launch motor", String("Off"));
  digitalWrite(LAUNCH_MOTOR_PIN, LOW);
}

/**
   Test the launch motor.
*/
void launchTest() {
  debugStep("Test launch motor control.");
  launchOn();
  delay(6000);
  launchOff();
}
