void printSensorReadingsToSerial(unsigned int sensors[6], unsigned int position, unsigned long timestamp)
// Prints the sensor readings to serial as csv values,
// it first prints the individual calibrated sensor values,
// then the weighted average.
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

void initialPrint()
{
  Serial.println("Sensor1,Sensor2,Sensor3,Sensor4,Sensor5,Sensor6,WeightedAverage,Time");
}
