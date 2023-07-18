#pragma once

#ifndef Arduino
  #include <Arduino.h>
#endif

int count = 0;
void logOutput (int analogValue, int speed) {
  if (count > 10000 & speed > 10) {
    Serial.print("Analog: ");
    Serial.print(analogValue);
    Serial.print(", Speed: ");
    Serial.println(speed);
    count = 0;
  }
  count += 1;
}

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
