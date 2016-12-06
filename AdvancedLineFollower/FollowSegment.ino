// The maze is broken down into segments. Once the Zumo decides
// which segment to turn on, it will navigate until it finds another
// intersection. followSegment() will then return after the
// intersection is found.
void followSegment()
{
  unsigned int position;
  unsigned int sensors[6];
  int offset_from_center;
  int power_difference;
  unsigned long millis_start;
  unsigned long millis_curr;
  
  while(1)
  {     
    // Delay to make actions each timestep
    millis_start = millis();
    while(100 < (millis()-millis_start));
    millis_curr = millis();
    
    // Get the position of the line.
    position = reflectanceSensors.readLine(sensors);

    // Get calibrated sensor values
    reflectanceSensors.readCalibrated(sensors);

    // Print sensor readings to serial.
    printSensorReadingsToSerial(sensors, position, millis_curr);
         
    // The offset_from_center should be 0 when we are on the line.
    offset_from_center = ((int)position) - 2500;
     
    // Compute the difference between the two motor power settings,
    // m1 - m2.  If this is a positive number the robot will turn
    // to the left.  If it is a negative number, the robot will
    // turn to the right, and the magnitude of the number determines
    // the sharpness of the turn.
    // Corresponds to P regulator with proportional factor Kp = 1/3
    power_difference = offset_from_center / 3;

    // Alternative control function
    // power_difference = offset_from_center/ 4 + 6 * (offset_from_center - last_offset);
    // last_offset = offset_from_center;
     
    // Compute the actual motor settings.  We never set either motor
    // to a negative value.
    if(power_difference > SPEED)
      power_difference = SPEED;
    if(power_difference < -SPEED)
      power_difference = -SPEED;
     
    if(power_difference < 0)
      motors.setSpeeds(SPEED + power_difference, SPEED);
    else
      motors.setSpeeds(SPEED, SPEED - power_difference);
     
    // We use the inner four sensors (1, 2, 3, and 4) for
    // determining whether there is a line straight ahead, and the
    // sensors 0 and 5 for detecting lines going to the left and
    // right.
    if(sensors[0]<NO_LINE_THRESHOLD && sensors[2]<NO_LINE_THRESHOLD && sensors[3]<NO_LINE_THRESHOLD && sensors[4]<NO_LINE_THRESHOLD && sensors[5]<NO_LINE_THRESHOLD)
    {
      // There is no line visible ahead, and we didn't see any
      // intersection.  Must be a dead end.            
      return;
    }
    if(sensors[0] > SENSOR_THRESHOLD || sensors[5] > SENSOR_THRESHOLD)
    {
      // Found an intersection.
      return;
    }
  }
}
