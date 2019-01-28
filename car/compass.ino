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
   Read out the heading in a value from 0-360 degrees.
*/
int compassGetDirection() {
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp);

  float Pi = 3.14159;

  // Calculate the angle of the vector y, x.
  float dir = atan2(mag.magnetic.x, mag.magnetic.y) * (180 / M_PI);

  //float dir = (atan2(mag.magnetic.y, mag.magnetic.x) * 180) / Pi;

  // Normalize to 0-360.
  if (dir < 0)
  {
    //dir = 360 + dir;
  }

  Serial.println("Direction : " + String(dir));
  displayDirection(dir);
  return dir;
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

  Serial.println("x_min : " + String(x_min));
  Serial.println("x_max : " + String(x_max));
  Serial.println("y_min : " + String(y_min));
  Serial.println("y_max : " + String(y_max));
  
  compassCalibrateCalculate();

  Serial.println("End calibration");
}

void compassCalibrateCalculate() {
  //Calculate offsets
  x_offset = (x_min + x_max) / 2;

  y_offset = (y_min + y_max) / 2;

  x_scale = x_max - x_min;
  y_scale = y_max - y_min;

  //Serial.println("x_offset : " + String(x_offset));
  //Serial.println("y_offset : " + String(y_offset));
  Serial.println("x_scale : " + String(x_scale));
  Serial.println("y_scale : " + String(y_scale));
}

/**
  Get the compass heading.
*/
float compassReadHeading() {
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp);
  
  int x = mag.magnetic.x * 1000;
  int y = mag.magnetic.y * 1000;
  
  float heading = (atan2((y - y_offset) * y_scale, (x - x_offset) * x_scale) * (180 / M_PI)) + 180;

  Serial.println("Direction : " + String(heading));
  displayDirection(heading);

  //Calculate the heading
  return heading;
}






/**
   Debug all data from the sensor.
*/
void compassDebugAll() {
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp);

  Serial.print("X : ");
  Serial.println((int) (mag.magnetic.x * 1000));
  Serial.print("Y : ");
  Serial.println((int) (mag.magnetic.y * 1000));
  compassGetDirection();
  return;

  Serial.print("Raw:");
  Serial.print((int)(accel.acceleration.x * 1000));
  Serial.print(',');
  Serial.print((int)(accel.acceleration.y * 1000));
  Serial.print(',');
  Serial.print((int)(accel.acceleration.z * 1000));
  Serial.print(',');
  Serial.print((int)(gyro.gyro.x * 1000));
  Serial.print(',');
  Serial.print((int)(gyro.gyro.y * 1000));
  Serial.print(',');
  Serial.print((int)(gyro.gyro.z * 1000));
  Serial.print(',');
  Serial.print((int)(mag.magnetic.x * 1000));
  Serial.print(',');
  Serial.print((int)(mag.magnetic.y * 1000));
  Serial.print(',');
  Serial.print((int)(mag.magnetic.z * 1000));
  Serial.println();

  delay(50);
}
