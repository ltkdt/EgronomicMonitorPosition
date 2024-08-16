#include <Arduino.h>

#define SPEEDOFSOUND 0.0343
#define TRIG 5
#define ECHO 15

float DetectDistance(bool &safe_status, int lower_bound, int upper_bound);