#include "distance_detect.h"

float duration, distance;

float DetectDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);// set trig to LOW
  duration = pulseIn(ECHO, HIGH); // wait for when the the reading value will be high | Reference: https://www.arduino.cc/reference/en/language/functions/advanced-io/pulsein/ | 
  distance = duration * SPEEDOFSOUND / 2;// divide the time by 2 then multiply it by 0.0343
  
  return distance;
}