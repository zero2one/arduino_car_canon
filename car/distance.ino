/**
 * Distance related code.
 * 
 * Setup the ultrasone sensor and get its readings.
 * 
 * Use the following function to get the distance:
 * 
 * - distanceGet() : Get the measured distance in cm.
 */

// Distance configuration.
#define DISTANCE_PIN_TRIGGER 9
#define DISTANCE_PIN_ECHO 10



/**
 * Setup the distance sensor.
 */
void distanceSetup() {
  pinMode(DISTANCE_PIN_TRIGGER, OUTPUT);
  pinMode(DISTANCE_PIN_ECHO, INPUT);
}

/**
 * Get the distance from the sensor.
 * 
 * @return int
 *   The measured distance.
 */
int distanceGet() {
  digitalWrite(DISTANCE_PIN_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(DISTANCE_PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(DISTANCE_PIN_TRIGGER, LOW);
  
  unsigned long duration = pulseIn(DISTANCE_PIN_ECHO, HIGH);
  int dist = duration / 29 / 2;

  displayDistance(dist);
  return dist;
}
