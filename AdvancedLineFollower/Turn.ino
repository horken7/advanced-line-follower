// Turns according to the parameter dir, which should be 
// 'L' (left), 'R' (right), 'S' (straight), or 'B' (back).
void turn(char dir)
{

  // count and last_status help
  // keep track of how much further
  // the Zumo needs to turn.
  unsigned short count = 0;
  unsigned short last_status = 0;
  unsigned int sensors[6];
  
  // dir tests for which direction to turn
  switch(dir)
  {
  
  // Since we're using the sensors to coordinate turns instead of timing them, 
  // we can treat a left turn the same as a direction reversal: they differ only 
  // in whether the zumo will turn 90 degrees or 180 degrees before seeing the 
  // line under the sensor. If 'B' is passed to the turn function when there is a
  // left turn available, then the Zumo will turn onto the left segment.
    case 'L':
      // Turn left.
      motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
      
      // This while loop monitors line position
      // until the turn is complete. 
      while(count < 2)
      {
        reflectanceSensors.readLine(sensors);
    
        // Increment count whenever the state of the sensor changes 
        // (white->black and black->white) since the sensor should 
        // pass over 1 line while the robot is turning, the final 
        // count should be 2
        count += ABOVE_LINE(sensors[1]) ^ last_status; 
        last_status = ABOVE_LINE(sensors[1]);
      }
    
    break;
    case 'B':
      // Turn back.
      motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
      
      // This while loop monitors line position
      // until the turn is complete. 
      while(count < 2)
      {
        reflectanceSensors.readLine(sensors);
    
        // Increment count whenever the state of the sensor changes 
    // (white->black and black->white) since the sensor should 
    // pass over 1 line while the robot is turning, the final 
    // count should be 2
        count += ABOVE_LINE(sensors[1]) ^ last_status; 
        last_status = ABOVE_LINE(sensors[1]);
      }
    
    break;
    
    case 'R':
      // Turn right.
      motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
      
      // This while loop monitors line position
      // until the turn is complete. 
      while(count < 2)
      {
        reflectanceSensors.readLine(sensors);
        count += ABOVE_LINE(sensors[4]) ^ last_status;
        last_status = ABOVE_LINE(sensors[4]);
      }
    
    break;
  
    case 'S':
    // Don't do anything!
    break;
  }
}
