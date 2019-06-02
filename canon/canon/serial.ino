/**
 * Serial related code.
 */



/**
 * Setup the serial output.
 */
void serialSetup() {
  Serial.begin(9600);
  debugStep("Serial setup");
}
