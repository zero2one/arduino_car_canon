/**
   Code related to determine the location.
*/


/**
  Direction delta.
*/
#define LOCATION_DIRECTION_DELTA 5
#define LOCATION_DISTANCE_DELTA 5

/**
  X-Y direction values.
*/
int locationDirectionX = 0;
int locationDirectionY = 90;

/**
  Current X-Y distance.
*/
int locationDistanceX = 0;
int locationDistanceY = 0;



/**
  Setup the location variables.
*/
void locationSetup() {
  debugStep("Location Setup");
  locationDirectionInit();
}

/**
  Init X Y locations based on current heading.
*/
void locationDirectionInit() {
  debugStep("Location Direction Init");

  locationDirectionX = compassGetHeading();
  locationDirectionY = locationDirectionX + 90;
  if (locationDirectionY > 360) {
    locationDirectionY = locationDirectionY - 360;
  }

  locationDirectionDebug();
}

/**
  Init X Y distances based on current location.
*/
void locationDistanceInit() {
  moveToDirectionX();
  locationDistanceX = distanceGet();
  delay(1000);
  moveToDirectionY();
  locationDistanceY = distanceGet();
  delay(1000);
  moveToDirectionX();

  locationDistanceDebug();
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
  Check if the current direction is equal to given value.

  @param int dir

  @return bool
*/
bool locationDirectionIs(int dir) {
  int dirCurrent = compassGetHeading();

  return (dir - LOCATION_DIRECTION_DELTA) < dirCurrent
         && (dir + LOCATION_DIRECTION_DELTA) > dirCurrent;
}

/**
  Check if the current direction is X.

  @return bool
*/
bool locationDirectionIsX() {
  return locationDirectionIs(locationDirectionGetX());
}

/**
  Check if the current location is Y.

  @return bool
*/
bool locationDirectionIsY() {
  return locationDirectionIs(locationDirectionGetY());
}

/**
  Print out all measured & calculated values.
*/
void locationDirectionDebug() {
  debugValue("X", locationDirectionGetX());
  debugValue("Y", locationDirectionGetY());
}

/**
  Get the current distance to X.

  @return int
*/
int locationDistanceGetX() {
  displayDistanceX(locationDistanceX);
  return locationDistanceX;
}

/**
  Get the current distance to Y.

  @return int
*/
int locationDistanceGetY() {
  displayDistanceY(locationDistanceY);
  return locationDistanceY;
}

/**
  Print out all measured & calculated values.
*/
void locationDistanceDebug() {
  debugValue("X", locationDirectionGetX());
  debugValue("Y", locationDirectionGetY());
}

/**
  Check if the current location is X.

  @param int dist
    The requested distance.

  @return bool
*/
bool locationDistanceIs(int dist) {
  int distCurrent = distanceGet();
  return (dist - LOCATION_DISTANCE_DELTA) < distCurrent
         && (dist + LOCATION_DISTANCE_DELTA) > distCurrent;
}
