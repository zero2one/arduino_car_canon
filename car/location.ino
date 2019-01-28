/**
   Code related to determine the location.
*/


/**
  Min-Max
*/
#define LOCATION_DIRECTION_DELTA 5


/**
  Min-Max direction values.
*/
int locationDirectionMin = 0;
int locationDirectionMax = 0;

/**
  X-Y direction values.
*/
int locationDirectionX = 360;
int locationDirectionY = 0;

/**
  Current X-Y distance.
*/
int locationDistanceX = 0;
int locationDistanceY = 0;



/**
  Setup the location variables.
*/
void locationSetup() {
  locationDirectionSetup();
}

/**
  Setup X Y locations.
*/
void locationDirectionSetup() {
  // Set the X direction.
  int current = compassGetDirection();
  locationDirectionX = current;
  locationDirectionSetupMinMax(current);

  // Turn around to get the min-max direction values.
  motorTurnAroundRight(MOTOR_SPEED_TURN);
  delay(1000);
  while (!locationDirectionIsX()) {
    current = compassGetDirection();
    locationDirectionSetupMinMax(current);
    delay(50);
  }
  motorAllStop();

  // Calculate the Y direction.
  int ninetyDegrees = floor((locationDirectionMax - locationDirectionMin) / 4);
  Serial.println("Direction 90° : " + String(ninetyDegrees));

  locationDirectionY = locationDirectionX + ninetyDegrees;
  if (locationDirectionY > locationDirectionMax) {
    locationDirectionY = locationDirectionY - locationDirectionMax + locationDirectionMin;
  }

  locationDirectionDebug();
  delay(100000);
}

/**
  Update the min & max direction.

  Values will only be overwritten when they are:
  - lower then min.
  - greather the max.

  @param int direction
*/
void locationDirectionSetupMinMax(int direction) {
  if (locationDirectionMin > direction) {
    locationDirectionMin = direction;
  }
  if (locationDirectionMax < direction) {
    locationDirectionMax = direction;
  }
}

/**
  Get the X-direction.

  @return int
*/
int locationDirectionGetX() {
  return locationDirectionX;
}

/**
  Get the Y-direction.

  @return int
*/
int locationDirectionGetY() {
  return locationDirectionY;
}

/**
  Check if the current location is X.

  @return bool
*/
bool locationDirectionIsX() {
  int dirCurrent = compassGetDirection();
  int dirX = locationDirectionGetX();

  return (dirX - LOCATION_DIRECTION_DELTA) < dirCurrent 
    && (dirX + LOCATION_DIRECTION_DELTA) > dirCurrent;
}

/**
  Check if the current location is Y.

  @return bool
*/
bool locationDirectionIsY() {
  int dirCurrent = compassGetDirection();
  int dirY = locationDirectionGetY();

  return (dirY - LOCATION_DIRECTION_DELTA) < dirCurrent 
    && (dirY + LOCATION_DIRECTION_DELTA) > dirCurrent;
}

/**
  Print out all measured & calculated values.
*/
void locationDirectionDebug() {
  Serial.println("Direction X : " + String(locationDirectionGetX()));
  Serial.println("Direction Y : " + String(locationDirectionGetY()));
  Serial.println("Direction Min : " + String(locationDirectionMin));
  Serial.println("Direction Max : " + String(locationDirectionMax));
}
