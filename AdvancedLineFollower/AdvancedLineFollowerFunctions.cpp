#include "AdvancedLineFollowerFunctions.h"

ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

/*********************************************

FOLLOW SEGMENT

The maze is broken down into segments. Once the Zumo decides
which segment to turn on, it will navigate until it finds another
intersection. followSegment() will then return after the
intersection is found.

@author Johan Larsson Hörkén (main author), based on example in shield libraries

*********************************************/

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

    printSensorReadingsToSerial(sensors, position, millis_curr);

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

      motors.setSpeeds(0,0);
      return;
    }
    else if(ABOVE_LINE(sensors[0]) || ABOVE_LINE(sensors[5]))
    {
      // Found an intersection.
      delay(OVERSHOOT(LINE_THICKNESS));
      motors.setSpeeds(0,0);
      return;
    }

  }
}


/*********************************************

INTERSECTION

When the robot is at an intersection, calling intersection()
will analyse the intersection and determine which kind of
intersection it is

@return byte intersection type where path exist:
1: dead end
2: left
3: right
4: left and straight
5: right and straight
6: T junction
7: full 4 way cartesian intersection

@author Seeralan Sarvaharman, Ben Morris

*********************************************/

byte intersection() {
  bool found_left = 0;
  bool found_straight = 0;
  bool found_right = 0;

  // Now read the sensors and check the intersection type.
  unsigned int sensors[6];
  reflectanceSensors.readLine(sensors);

  // Check for left and right exits.
  if (ABOVE_LINE(sensors[0]))
    found_left = 1;
  if (ABOVE_LINE(sensors[5]))
    found_right = 1;

  // Drive straight a bit more, until we are
  // approximately in the middle of intersection.
  // This should help us better detect if we
  // have left or right segments.
  motors.setSpeeds(SPEED / 2, SPEED / 2);
  delay(OVERSHOOT(LINE_THICKNESS) / 2);

  reflectanceSensors.readLine(sensors);

  // Check for left and right exits.
  if (ABOVE_LINE(sensors[0]))
    found_left = 1;
  if (ABOVE_LINE(sensors[5]))
    found_right = 1;

  // After driving a little further, we
  // should have passed the intersection
  // and can check to see if we've hit the
  // finish line or if there is a straight segment
  // ahead.
  delay(OVERSHOOT(LINE_THICKNESS) / 2);

  // Check for a straight exit.
  reflectanceSensors.readLine(sensors);

  // Check again to see if left or right segment has been found
  if (ABOVE_LINE(sensors[0]))
    found_left = 1;
  if (ABOVE_LINE(sensors[5]))
    found_right = 1;

  if (ABOVE_LINE(sensors[1]) || ABOVE_LINE(sensors[2]) ||
      ABOVE_LINE(sensors[3]) || ABOVE_LINE(sensors[4]))
    found_straight = 1;

  byte intersectionType = 0;

  if (!found_left && !found_right && !found_straight) {
    // deadend
    intersectionType = 1;
  }

  else if (found_left && !found_right && !found_straight) {
    // left
    intersectionType = 2;
  }

  else if (!found_left && found_right && !found_straight) {
    // right
    intersectionType = 3;
  }

  else if (found_left && !found_right && found_straight) {
    // straight left
    intersectionType = 4;
  }

  else if (!found_left && found_right && found_straight) {
    // straight right
    intersectionType = 5;
  }

  else if (found_left && found_right && !found_straight) {
    // T junction
    intersectionType = 6;
  }

  else if (found_left && found_right && found_straight) {
    // T junction
    intersectionType = 7;
  }
  return intersectionType;
}



/*********************************************

TURN

When the robot have reached a junction, turn(dir) will
turn in the direction specified by dir

@param char dir, a character defining the turn direction:
'L' (left)
'R' (right)
'S' (straight)
'B' (back)

@author Johan Larsson Hörkén (main author), based on example in shield libraries

*********************************************/


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
    motors.setSpeeds(0, 0);
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
    motors.setSpeeds(0, 0);
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
    motors.setSpeeds(0, 0);
    break;

    case 'S':
    // Don't do anything!
    motors.setSpeeds(0, 0);
    break;

  }
  //button.waitForButton();
}



/*********************************************

SENSOR CALIBRATION

Calibrate the sensors during setup

@author Example included in shield libraries

*********************************************/


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

  // Wait for button to be pressed before initiate calibration
  button.waitForButton();


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


/*********************************************

PRINT SENSOR READINGS TO SERIAL

Prints the sensor readings to serial as csv values,
in following order:
1-6: Individual calibrated sensor values
7: Weighted average of sensor readings
8: Timestamp

Currently works with a fixed size of 6 calibrated
sensor values, may be updated in the future to
take an arbitrary amount.

@param unsigned int sensors[6], array of sensor values
each value should be in range 0-2500 for calibrated values
@param unsigned int position, weighted average of sensor readings
@param unsigned long timestamp, timestamp of current time in milliseconds

@author Johan Larsson Hörkén

*********************************************/

void printSensorReadingsToSerial(unsigned int sensors[6], unsigned int position, unsigned long timestamp)
{
  for (int i = 0; i < 6; i++)
  {
    Serial.print (sensors[i]);
    Serial.print (',');
  }
  Serial.print (position);
  Serial.print (',');
  Serial.println (timestamp);
}


/*********************************************

INITIAL PRINT

Initial print corresponding to format in printSensorReadingsToSerial()
to label the columns in a potential .csv export

@author Johan Larsson Hörkén

*********************************************/

void initialPrint()
{
  Serial.println("Sensor1,Sensor2,Sensor3,Sensor4,Sensor5,Sensor6,WeightedAverage,Time");
}
