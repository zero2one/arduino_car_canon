/**
 * Code to setup the motor shield and to controll the connected motors.
 * 
 * Provided functions:
 * 
 * - motorLeftStop() : Stop the left motor.
 * - motorRightStop() : Stop the right motor.
 * - motorAllStop() : Stop all motors.
 * 
 * - motorLeftRun(int dir, int speed) : Run the left motor.
 * - motorRightRun(int dir, int speed) : Run the right motor.
 * - motorAllRun(int dir, int speed) : Run both motors.
 * 
 * - motorTurnLeft(int dir, int speed) : Turn to the left by running only the right motor.
 * - motorTurnRight(int dir, int speed) : Turn to the Right by running only the left motor.
 * 
 * Turning around its own midpoint by running both motors in opposite directions:
 * - motorTurnAroundLeft(int speed) : Turn around to the left.
 * - motorTurnAroundRight(int speed) : Turn around to the right.
 * 
 * Note:
 * 
 * - Speed value between 0 and 255.
 * - Direction as constants:
 *   - BACKWARD
 *   - FORWARD
 */

// Motor setup
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *MotorRight = AFMS.getMotor(1);
Adafruit_DCMotor *MotorLeft = AFMS.getMotor(3);

// Motor speed setup
#define MOTOR_SPEED_LEFT 0
#define MOTOR_SPEED_RIGHT 2

// Enable/Disable debugging.
#define MOTOR_DEBUG 1



/**
 * Setup the motor shield.
 */
void motorSetup() {
  AFMS.begin();  
}

/**
 * Stop the left motor.
 */
void motorLeftStop() {
  motorDebug("Motor LEFT : STOP");
  MotorLeft->run(RELEASE);
}

/**
 * Stop the right motor.
 */
void motorRightStop() {
  motorDebug("Motor RIGHT : STOP");
  MotorRight->run(RELEASE);
}

/**
 * Stop all motors.
*/
void motorAllStop() {
  motorDebug("Motor ALL : STOP");
  motorLeftStop();
  motorRightStop();
}

/**
 * Run the left motor.
 *
 * @param int direction
 *   The direction to turn.
 * @param int speed
 *   The speed (0-255).
 */
void motorLeftRun(int direction, int speed) {
  motorDebug("Motor LEFT");
  motorDebug("  > dir   : " + String(direction));
  motorDebug("  > speed : " + String(speed));

  speed = speed + MOTOR_SPEED_LEFT;
  if (speed > 255) {
    speed = 255;
  }

  MotorLeft->setSpeed(speed);
  MotorLeft->run(direction);
}

/**
 * Run the right motor.
 *
 * @param int direction
 *   The direction to turn.
 * @param int speed
 *   The speed (0-255).
 */
void motorRightRun(int direction, int speed) {
  motorDebug("Motor RIGHT");
  motorDebug("  > dir   : " + String(direction));
  motorDebug("  > speed : " + String(speed));

  speed = speed + MOTOR_SPEED_RIGHT;
  if (speed > 255) {
    speed = 255;
  }

  MotorRight->setSpeed(speed);
  MotorRight->run(direction);
}

/**
 * Run both motors together.
 *
 * @param int direction
 *   The direction to turn.
 * @param int speed
 *   The speed (0-255).
 */
void motorAllRun(int direction, int speed) {
  motorDebug("Run Both motors");
  motorLeftRun(direction, speed);
  motorRightRun(direction, speed);
}

/**
 * Turn to the left.
 * 
 * This will stop the left motor and run only the right motor.
 *
 * @param int direction
 *   The direction to turn.
 * @param int speed
 *   The speed (0-255).
 */
void motorTurnLeft(int direction, int speed) {
  motorDebug("Motor Turn LEFT");
  motorLeftStop();
  motorRightRun(direction, speed);
}

/**
 * Turn to the right.
 * 
 * This will stop the right motor and run only the left motor.
 *
 * @param int direction
 *   The direction to turn.
 * @param int speed
 *   The speed (0-255).
 */
void motorTurnRight(int direction, int speed) {
  motorDebug("Motor Turn Right");
  motorRightStop();
  motorLeftRun(direction, speed);
}

/**
 * Turn around to the left.
 * 
 * This will run both motors in opposite directions.
 * 
 * @param int direction
 *   The direction to turn.
 * @param int speed
 *   The speed (0-255).
 */
void motorTurnAroundLeft(int speed) {
  motorDebug("Motor Turn around LEFT");
  motorLeftRun(BACKWARD, speed);
  motorRightRun(FORWARD, speed);
}

/**
 * Turn around to the right.
 * 
 * This will run both motors in opposite directions.
 * 
 * @param int direction
 *   The direction to turn.
 * @param int speed
 *   The speed (0-255).   
 */
void motorTurnAroundRight(int speed) {
  motorDebug("Turn around to the RIGHT");
  motorLeftRun(FORWARD, speed);
  motorRightRun(BACKWARD, speed);
}

/**
 * Print debug info on the Serial out.
 * 
 * @param string message
 *   The message to print.
 */
void motorDebug(String message) {
  if (MOTOR_DEBUG) {
    Serial.println(message);
  }
}
