#ifndef ADVANCEDLINEFOLLOWERFUNCTIONS_H

#define ADVANCEDLINEFOLLOWERFUNCTIONS_H

#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>

// SENSOR_THRESHOLD is a value to compare reflectance sensor
// readings to to decide if the sensor is over a black line
#define SENSOR_THRESHOLD 700

// NO_LINE_THRESHOLD is a value to compare reflectanse sensor
// readings to decide if you are NOT over a black line
#define NO_LINE_THRESHOLD 50

// ABOVE_LINE is a helper macro that takes returns
// 1 if the sensor is over the line and 0 if otherwise
#define ABOVE_LINE(sensor)((sensor) > SENSOR_THRESHOLD)

// Motor speed when turning. TURN_SPEED should always
// have a positive value, otherwise the Zumo will turn
// in the wrong direction.
#define TURN_SPEED 250

// Motor speed when driving straight. SPEED should always
// have a positive value, otherwise the Zumo will travel in the
// wrong direction.
#define SPEED 250 

// Thickness of your line in inches
#define LINE_THICKNESS .75

#define INCHES_TO_ZUNITS 17142.0

#define OVERSHOOT(line_thickness)(((INCHES_TO_ZUNITS * (line_thickness)) / SPEED))

#define ABOVE_LINE(sensor)((sensor) > SENSOR_THRESHOLD)



void followSegment();

byte intersection();

void turn(char dir);

void calibrate_sensors();

void printSensorReadingsToSerial(unsigned int sensors[6], unsigned int position, unsigned long timestamp);

void initialPrint();


#endif /*ADVANCEDLINEFOLLOWER_H*/
