/**
   Compass related code.

   This is based on the gaus sensor of the LSM9DS1 PCB.

   Calibration:
   https://learn.adafruit.com/ahrs-for-adafruits-9-dof-10-dof-breakout/magnetometer-calibration
*/

// Create the sensor object.
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

// Compass calibration.
#define COMPASS_X_OFFSET 392
#define COMPASS_Y_OFFSET 482
#define COMPASS_X_SCALE 560.00
#define COMPASS_Y_SCALE 573.00

/**
   Random default values!
*/
int x_min = 32767;
int x_max = 0x8000;

int y_min = 32767;
int y_max = 0x8000;

int x_offset = 0;
int y_offset = 0;

float x_scale = 0.0;
float y_scale = 0.0;



/**
   Setup the compass sensor.
*/
void compassSetup() {
  debugStep("Compass Setup");

  if (!lsm.begin()) {
    debugError("! No LSM9DS1 detected... Check your wiring!");
    debugError("  Script halted.");
    for (;;); // Don't proceed, loop forever.
  }

  compassInit();
}

/**
   Init the compass sensor.
*/
void compassInit() {
  debugStep("Compass Init");

  // Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);

  // Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);

  // Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
}

/**
  Compass heading based on the predefined calibration values.
*/
int compassGetHeading() {
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp);

  int x = mag.magnetic.x * 1000;
  int y = mag.magnetic.y * 1000;

  float heading =
    (
      atan2(
        (y - COMPASS_Y_OFFSET) * COMPASS_Y_SCALE,
        (x - COMPASS_X_OFFSET) * COMPASS_X_SCALE
      )
      * (180 / M_PI)
    ) + 180;

  displayDirection(heading);
  return heading;
}

/**
   Calibrate the compass.

   Turn around the board multiple times within 20s during calibration.
*/
void compassCalibrate() {
  int x, y;
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp);

  debugStep("Calibration start...");

  int calibrationStart = millis();
  int calibrationLastChange = calibrationStart;

  while ((calibrationStart + 20000) > calibrationLastChange) {
    lsm.getEvent(&accel, &mag, &gyro, &temp);
    x = mag.magnetic.x * 1000;
    y = mag.magnetic.y * 1000;

    debugValue("X", x);
    debugValue("Y", y);

    if (x < x_min)
    {
      x_min = x;
    }
    if (x > x_max)
    {
      x_max = x;
    }
    if (y < y_min)
    {
      y_min = y;
    }
    if (y > y_max)
    {
      y_max = y;
    }

    calibrationLastChange = millis();
  }

  compassCalibrateCalculate();

  debugStep("Calibration end");
}

/**
  Calculate the x & y scale and offset.
*/
void compassCalibrateCalculate() {
  x_offset = (x_min + x_max) / 2;
  y_offset = (y_min + y_max) / 2;
  x_scale = x_max - x_min;
  y_scale = y_max - y_min;

  debugStep("Calibration result:");
  debugValue("X Offset", x_offset);
  debugValue("Y Offset", y_offset);
  debugValue("X Scale", x_scale);
  debugValue("Y Scale", y_scale);
}

/**
  Get heading based on the measured calibration values.
*/
float compassCalibrateHeading() {
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp);

  int x = mag.magnetic.x * 1000;
  int y = mag.magnetic.y * 1000;

  float heading = (
    atan2(
      (y - y_offset) * y_scale, 
      (x - x_offset) * x_scale
    ) * (180 / M_PI)
  ) + 180;

  displayDirection(heading);
  return heading;
}
