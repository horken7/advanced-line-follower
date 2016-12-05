#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>

/* This example uses the Zumo Reflectance Sensor Array
 * to navigate a black line maze with no loops.
 * 
 * The Zumo first calibrates the sensors to account
 * for differences of the black line on white background.
 * Calibration is accomplished in setup().
 * 
 * TODO: Write description of program
 * 
 * The macros SPEED, TURN_SPEED, ABOVE_LINE(), and LINE_THICKNESS 
 * might need to be adjusted on a case by case basis to give better 
 * line following results.
 *
 */

// SENSOR_THRESHOLD is a value to compare reflectance sensor
// readings to to decide if the sensor is over a black line
#define SENSOR_THRESHOLD 700

// ABOVE_LINE is a helper macro that takes returns
// 1 if the sensor is over the line and 0 if otherwise
#define ABOVE_LINE(sensor)((sensor) > SENSOR_THRESHOLD)

// Motor speed when turning. TURN_SPEED should always
// have a positive value, otherwise the Zumo will turn
// in the wrong direction.
#define TURN_SPEED 400

// Motor speed when driving straight. SPEED should always
// have a positive value, otherwise the Zumo will travel in the
// wrong direction.
#define SPEED 400 

// Thickness of your line in inches
// #define LINE_THICKNESS .75 

ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

void setup() {

  button.waitForButton();
  calibrate_sensors();
  
}

void loop() {
  button.waitForButton();
  followSegment();
  motors.setSpeeds(0,0);
  button.waitForButton();
  motors.setSpeeds(SPEED,SPEED);
  delay(100);
  turn('R');
  motors.setSpeeds(0,0);

}

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
  case 'B':
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
  
  while(1)
  {     
    // Get the position of the line.
    position = reflectanceSensors.readLine(sensors);

    // Print sensor readings to serial.
    //printSensorReadingsToSerial();
     
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
     
    if(!ABOVE_LINE(sensors[0]) && !ABOVE_LINE(sensors[1]) && !ABOVE_LINE(sensors[2]) && !ABOVE_LINE(sensors[3]) && !ABOVE_LINE(sensors[4]) && !ABOVE_LINE(sensors[5]))
    {
      // There is no line visible ahead, and we didn't see any
      // intersection.  Must be a dead end.            
      return;
    }
    else if(sensors[0] > SENSOR_THRESHOLD|| sensors[5] > SENSOR_THRESHOLD)
    {
      // Found an intersection.
      return;
    }
   
  }
}

void printSensorReadingsToSerial()
// Prints the sensor readings to serial as csv values,
// it first prints the individual calibrated sensor values,
// then the weighted average.
{
  Serial.begin (9600);
  unsigned int sensors[6];
  unsigned int position = reflectanceSensors.readLine(sensors);

  reflectanceSensors.readCalibrated(sensors);

  for (byte i = 0; i < 6; i++)
  {
    Serial.print (sensors[i]);
    Serial.print (',');
  }
  Serial.println (position);
}
