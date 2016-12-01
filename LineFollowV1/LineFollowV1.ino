
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#define LED_PIN 13

ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

void setup()
{
  
  // Initialize the reflectance sensors module
  reflectanceSensors.init();

  // Wait for the user button to be pressed and released
  button.waitForButton();

  // Turn on LED to indicate we are in calibration mode
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
  delay(1000);
  int i;
  for(i = 0; i < 80; i++)
  {
    if ((i > 10 && i <= 30) || (i > 50 && i <= 70))
      motors.setSpeeds(-200, 200);
    else
      motors.setSpeeds(200, -200);
    reflectanceSensors.calibrate();

    // Since our counter runs to 80, the total delay will be
    // 80*20 = 1600 ms.
    delay(20);
  }
  motors.setSpeeds(0,0);


  // Wait for the user button to be pressed and released
  button.waitForButton();

  
}

void loop()
{
  unsigned int sensors[6];
  
  // Get the position of the line.  Note that we *must* provide the "sensors"
  // argument to readLine() here, even though we are not interested in the
  // individual sensor readings
  int position = reflectanceSensors.readLine(sensors);

  // Our "error" is how far we are away from the center of the line, which
  // corresponds to position 2500.
  int error = position - 2500;

  digitalWrite(LED_PIN, HIGH);
  
  for (int speed = 0; speed <= 400; speed++)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(0.01);
  }

  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(0.01);
  }
  if (position>4000)
  {
        for (int speed = 0; speed <= 400; speed++)
      {
          motors.setLeftSpeed(speed);
          motors.setRightSpeed(-600);
          delay(0.01);
      }
    
      for (int speed = 400; speed >= 0; speed--)
      {
          motors.setLeftSpeed(speed);
          motors.setRightSpeed(-600);
          delay(0.01);
      }
  }
  if (position<1000)
  {
        for (int speed = 0; speed <= 400; speed++)
      {
          motors.setLeftSpeed(-600);
          motors.setRightSpeed(speed);
          delay(0.01);
      }
    
      for (int speed = 400; speed >= 0; speed--)
      {
          motors.setLeftSpeed(-600);
          motors.setRightSpeed(speed);
          delay(0.01);
      }
  }

}
