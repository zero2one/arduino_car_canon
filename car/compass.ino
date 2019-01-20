/**
 * Compass related code.
 * 
 * This is based on the gaus sensor of the LSM9DS1 PCB.
 * 
 * Calibration:
 * https://learn.adafruit.com/ahrs-for-adafruits-9-dof-10-dof-breakout/magnetometer-calibration
 */

// Create the sensor object.
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();



/**
 * Setup the compass sensor.
 */
void compassSetup() {
  Serial.println("Compass Setup");
  
  if(!lsm.begin()) {
    Serial.println(F("! No LSM9DS1 detected... Check your wiring!"));
    Serial.println(F("  Script halted."));
    for (;;); // Don't proceed, loop forever.
  }

  compassInit();
}

/**
 * Init the compass sensor.
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
 * Read out the heading in a value from 0-360 degrees.
 */
int compassGetDirection() {
  sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp);

  float Pi = 3.14159;
  
  // Calculate the angle of the vector y, x.
  float dir = (atan2(mag.magnetic.y, mag.magnetic.x) * 180) / Pi;
  
  // Normalize to 0-360.
  if (dir < 0)
  {
    dir = 360 + dir;
  }

  Serial.println("Orientation : " + String(dir));
  return dir;
}

/**
 * Debug all data from the sensor.
 */
void compassDebugAll() {
   sensors_event_t accel, mag, gyro, temp;
  lsm.getEvent(&accel, &mag, &gyro, &temp);
  
  Serial.print("Raw:");
  Serial.print((int)(accel.acceleration.x*1000));
  Serial.print(',');
  Serial.print((int)(accel.acceleration.y*1000));
  Serial.print(',');
  Serial.print((int)(accel.acceleration.z*1000));
  Serial.print(',');
  Serial.print((int)(gyro.gyro.x*1000));
  Serial.print(',');
  Serial.print((int)(gyro.gyro.y*1000));
  Serial.print(',');
  Serial.print((int)(gyro.gyro.z*1000));
  Serial.print(',');
  Serial.print((int)(mag.magnetic.x*1000));
  Serial.print(',');
  Serial.print((int)(mag.magnetic.y*1000));
  Serial.print(',');
  Serial.print((int)(mag.magnetic.z*1000));
  Serial.println();  
    
  delay(50);
}
