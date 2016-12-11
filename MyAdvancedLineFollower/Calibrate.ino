// Calibrate the sensors during setup
void calibrate_sensors()
{
  unsigned int sensors[6];
  unsigned short count = 0;
  unsigned short last_status = 0;
  int turn_direction = 1;  
  
  reflectanceSensors.init();
  
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);        // turn on LED to indicate we are in calibration mode

  
  // Calibrate the Zumo by sweeping it from left to right
  for(int i = 0; i < 4; i ++)
  {
    // Zumo will turn clockwise if turn_direction = 1.
    // If turn_direction = -1 Zumo will turn counter-clockwise.
    turn_direction *= -1;
  
    // Turn direction.
    motors.setSpeeds(turn_direction * TURN_SPEED, -1*turn_direction * TURN_SPEED);
      
    // This while loop monitors line position
    // until the turn is complete. 
    while(count < 2)
    {
      reflectanceSensors.calibrate();
      reflectanceSensors.readLine(sensors);
      if(turn_direction < 0)
      {
        // If the right  most sensor changes from (over white space -> over 
        // line or over line -> over white space) add 1 to count.
        count += ABOVE_LINE(sensors[5]) ^ last_status;
        last_status = ABOVE_LINE(sensors[5]);
      }
      else
      {
        // If the left most sensor changes from (over white space -> over 
        // line or over line -> over white space) add 1 to count.
        count += ABOVE_LINE(sensors[0]) ^ last_status;
        last_status = ABOVE_LINE(sensors[0]);   
      }
    }
  
    count = 0;
    last_status = 0;
  }
  
  // Turn left.
  turn('L');
  
  motors.setSpeeds(0, 0);
  
  // Turn off LED to indicate we are through with calibration
  digitalWrite(13, LOW);  
}
