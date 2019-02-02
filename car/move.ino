/**
  Code related to moving the car.

  Functions:
  - moveToDirectionX() : Move the car until it points to X.
  - moveToDirectionY() : Move the car until it points to Y.
*/

/**
  Move the car to X-Y distance.

  @param int distX
  @param int distY
*/
void moveToXY(int distX, int distY) {
  moveToDistanceX(distX);
  moveToDistanceY(distY);
}

/**
  Move the car to the X direction.
*/
void moveToDirectionX() {
  debugStep("Move to direction X");
  moveToDirection(locationDirectionGetX());
}

/**
  Move the car to the Y direction.
*/
void moveToDirectionY() {
  debugStep("Move to direction Y");
  moveToDirection(locationDirectionGetY());
}

/**
  Turn the car until the proper direction.

  @param int dir
    The requested direction.
 */
void moveToDirection(int dir) {
  debugStep("Move to direction " + String(dir));
  
  if (locationDirectionIs(dir)) {
    debugText("Already in the proper direction");
    return;
  }

  int diff = dir - compassGetHeading();
  if (diff < 0) {
    diff = diff + 360;
  }

  if (diff <= 180) {
    motorTurnAroundRight(MOTOR_SPEED_TURN);
  } else {
    motorTurnAroundLeft(MOTOR_SPEED_TURN);
  }

  while (!locationDirectionIs(dir)) {
    delay(10);
  }

  motorAllStop();
  debugText("Pointing to proper direction");
}

/**
  Move to distance X.

  @param int distance
    The distance we want in the X direction.
*/
void moveToDistanceX(int distance) {
  moveToDirectionX();
  moveToDistance(distance);
}

/**
  Move to distance Y.

  @param int distance
    The distance we want in the Y direction.
*/
void moveToDistanceY(int distance) {
  moveToDirectionY();
  moveToDistance(distance);
}

/**
   Move the car forward/backward until proper distance.

   @param int dist
*/
void moveToDistance(int dist) {
  debugStep("Move to distance : " + String(dist));
  if (locationDistanceIs(dist)) {
    debugText("Already the proper distance");
  }

  int dir;
  int heading = compassGetHeading();
  if (dist > distanceGet()) {
    dir = BACKWARD;
  } else {
    dir = FORWARD;
  }

  while (!locationDistanceIs(dist)) {
    motorAllRun(dir, MOTOR_SPEED_FORWARD); 
    delay(10);
    moveToDirection(heading);
  }

  motorAllStop();
  debugText("Distance is ok");
}
