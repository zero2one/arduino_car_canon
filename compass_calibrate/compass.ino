/**
   Compass related code.

   This is based on the gaus sensor of the LSM9DS1 PCB.

   Calibration:
   https://learn.adafruit.com/ahrs-for-adafruits-9-dof-10-dof-breakout/magnetometer-calibration
*/

// Create the sensor object.
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

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
  Serial.println("Compass Setup");

  if (!lsm.begin()) {
    Serial.println(F("! No LSM9DS1 detected... Check your wiring!"));
    Serial.println(F("  Script halted."));
    for (;;); // Don't proceed, loop forever.
  }

  compassInit();
}

/**
   Init the compass sensor.
*/
void compassInit() {
  Serial.println("Compass Init");

  // Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);

  // Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);

  // Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
}

/**
   Calibrate the compass.
*/
void compassCalibrate() {
  int x, y;
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp);

  Serial.println("Start calibration...");
  Serial.println("x : " + String(mag.magnetic.x * 1000));
  Serial.println("y : " + String(mag.magnetic.y * 1000));
  Serial.println("x_min : " + String(x_min));
  Serial.println("x_max : " + String(x_max));
  Serial.println("y_min : " + String(y_min));
  Serial.println("y_max : " + String(y_max));

  int calibrationStart = millis();
  int calibrationLastChange = calibrationStart;

  while ((calibrationStart + 20000) > calibrationLastChange) {
    lsm.getEvent(&accel, &mag, &gyro, &temp);
    x = mag.magnetic.x * 1000;
    y = mag.magnetic.y * 1000;

    Serial.println("x : " + String(x));
    Serial.println("y : " + String(y));

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

  Serial.println("End calibration");
}

/**
  Calculate the compass calibration values.
*/
void compassCalibrateCalculate() {
  //Calculate offsets
  x_offset = (x_min + x_max) / 2;

  y_offset = (y_min + y_max) / 2;

  x_scale = x_max - x_min;
  y_scale = y_max - y_min;

  Serial.println("Calibration result:");

  Serial.print("X Offset : ");
  Serial.println(x_offset);
  Serial.print("Y Offset : ");
  Serial.println(y_offset);
  Serial.print("X Scale : ");
  Serial.println(x_scale);
  Serial.print("Y Scale : ");
  Serial.println(y_scale);
}

/**
  Get the compass heading.
*/
float compassReadHeading() {
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp);

  int x = mag.magnetic.x * 1000;
  int y = mag.magnetic.y * 1000;

  float heading = (
    atan2(
      (y - y_offset) * y_scale, 
      (x - x_offset) * x_scale) * (180 / M_PI)
    ) + 180;

  Serial.print("Heading : ");
  Serial.println(heading);

  // Return the current heading.
  return heading;
}
