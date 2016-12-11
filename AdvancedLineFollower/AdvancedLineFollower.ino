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
#define SENSOR_THRESHOLD 300

// NO_LINE_THRESHOLD is a value to compare reflectanse sensor
// readings to decide if you are NOT over a black line
#define NO_LINE_THRESHOLD 50

// ABOVE_LINE is a helper macro that takes returns
// 1 if the sensor is over the line and 0 if otherwise
#define ABOVE_LINE(sensor)((sensor) > SENSOR_THRESHOLD)

// Motor speed when turning. TURN_SPEED should always
// have a positive value, otherwise the Zumo will turn
// in the wrong direction.
#define TURN_SPEED 200

// Motor speed when driving straight. SPEED should always
// have a positive value, otherwise the Zumo will travel in the
// wrong direction.
#define SPEED 200 

// Thickness of your line in inches
 #define LINE_THICKNESS .75

#define INCHES_TO_ZUNITS 17142.0

#define OVERSHOOT(line_thickness)(((INCHES_TO_ZUNITS * (line_thickness)) / SPEED))

#define ABOVE_LINE(sensor)((sensor) > SENSOR_THRESHOLD)

ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

void setup() {
  button.waitForButton();
  calibrate_sensors();
  Serial.begin (9600);
  initialPrint();
  
}

void loop() 
{
  followPath();
}
