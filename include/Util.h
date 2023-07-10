#pragma once

#ifndef Arduino
  #include <Arduino.h>
#endif

int count = 0;
void logOutput (int analogValue, int speed) {
  if (count > 1000 & speed > 0) {
    Serial.print("Analog: ");
    Serial.print(analogValue);
    Serial.print(", Speed: ");
    Serial.println(speed);
    count = 0;
  }
  count += 1;
}