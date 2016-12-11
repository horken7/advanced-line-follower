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
     
    // The offset_from_center should be 0 when we are on the line.
    offset_from_center = ((int)position) - 2500;
     
    // Compute the difference between the two motor power settings,
    // m1 - m2.  If this is a positive number the robot will turn
    // to the left.  If it is a negative number, the robot will
    // turn to the right, and the magnitude of the number determines
    // the sharpness of the turn.
    power_difference = offset_from_center / 3;
     
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
     
    if(!ABOVE_LINE(sensors[0]) && !ABOVE_LINE(sensors[1]) && !ABOVE_LINE(sensors[2]) && !ABOVE_LINE(sensors[3]) && !ABOVE_LINE(sensors[4]) && !ABOVE_LINE(sensors[5]))
    {
      // There is no line visible ahead, and we didn't see any
      // intersection.  Must be a dead end.            
      return;
    }
    else if(ABOVE_LINE(sensors[0]) || ABOVE_LINE(sensors[5]))
    {
      // Found an intersection.
      return;
    }
   
  }
}

