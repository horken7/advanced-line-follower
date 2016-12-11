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
