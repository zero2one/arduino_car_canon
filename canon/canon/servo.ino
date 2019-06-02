/**
   Servo code.
*/

// Create the servo pwm.
Adafruit_PWMServoDriver servoPwm = Adafruit_PWMServoDriver();

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVO_MIN  110 // this is the 'minimum' pulse length count (out of 4096)
#define SERVO_MAX  560 // this is the 'maximum' pulse length count (out of 4096)
#define SERVO_STEP_DELAY  10 // This is the delay after each pulse (ms).

/**
   Setup the servo board.
*/
void servoSetup() {
  Serial.begin(9600);
  Serial.println("2 channel Servo test!");

  servoPwm.begin();
  servoPwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  delay(50);
}

/**
   you can use this function if you'd like to set the pulse length in seconds
   e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
*/
void servoSetPulse(uint8_t n, double pulse) {
  double pulselength;

  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period");
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit");
  pulse *= 1000000;  // convert to us
  pulse /= pulselength;
  Serial.println(pulse);
  servoPwm.setPWM(n, 0, pulse);
}

/**
   Get the minimum servo pulse lenght

   @return uint16_t
*/
uint16_t servoGetMin() {
  return SERVO_MIN;
}

/**
   Get the maximum servo pulse lenght.

   @return uint16_t
*/
uint16_t servoGetMax() {
  return SERVO_MAX;
}

/**
   Get the middle position pulse length.

   @return uint16_t
*/
uint16_t servoGetMiddle() {
  return (servoGetMax() - servoGetMin()) / 2 + servoGetMin();
}

/**
   Convert degrees to servo position.

   @param int degrees
    The position in degrees 0-180.

    @return uint16_t
      The position.
*/
uint16_t servoDegreesToPulselen(int degrees) {
  return map(degrees, 0, 180, SERVO_MIN, SERVO_MAX);
}

void servoStepDelay() {
  delay(SERVO_STEP_DELAY);
}

/**
   Move the given servo to the given pulse length.

   @param int servoNum
     The servo number.
   @param uint16_t pulseLen
     The pulse length.
*/
void servoTo(int servoNum, uint16_t pulseLen) {
  if (!servoCheckPulseLen(pulseLen)) {
    return;
  }

  servoPwm.setPWM(servoNum, 0, pulseLen);
  servoStepDelay();
}

/**
   Check if a given pulse length is within the boundries.

   @param uint16_t pulseLen
     The pulse length.

   @return bool
     Is ok.
*/
bool servoCheckPulseLen(uint16_t pulseLen) {
  if (pulseLen > servoGetMax()) {
    debugError("Pulse length is to big!");
    debugValue("limit", servoGetMax());
    debugValue("value", pulseLen);
    return false;
  }

  if (pulseLen < servoGetMin()) {
    debugError("Pulse length is to small!");
    debugValue("limit", servoGetMin());
    debugValue("value", pulseLen);
    return false;
  }

  return true;
}
