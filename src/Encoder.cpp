#include "Encoder.h"

// Constructor to connect encoder GPIO pins to microcontroller
Encoder::Encoder(uint8_t port)
  :port_(port)
{}  

void Encoder::init() {
  position = map(analogRead(port_), 0, 1023, 0, 100);
  continuous_position = position;
  printPort(); Serial.print("Initialized. "); printPosition(); printRotations();
}

int16_t Encoder::readEncoder() {
  raw = analogRead(port_);
  position = map(raw, 0, 4095, 0, 100);
  
  if (position != 100) {
    if (transitioning & (direction == FORWARD) & (position != 0)) {
      continuous_position = getRotations() - offset;
      return continuous_position;
    }
    else if (transitioning & (direction == REVERSE) & (position != 100)) {
      continuous_position = getRotations() - offset;
      return continuous_position;
    }  

    transitioning = false;
    continuous_position = getRotations() + getPosition();
    return continuous_position;
  }

  // Stopped at 100 so return current value since we have no direction
  if (direction == STOPPED) {
    continuous_position = getRotations() - offset;
    return continuous_position;
  }

  // We've taken care of the rotations already so return
  if (transitioning == true) {
    continuous_position = getRotations() - offset;
    return continuous_position;
  }
  
  // Transitioning so take care of business
  transitioning = true;

  if (direction == FORWARD) {
    Serial.println("ROTATIONS +");
    rotations += 1;
  } else {
    Serial.println("ROTATIONS -");
    rotations -= 1;  
  }

  // Only return position so as not to double count
  continuous_position = getPosition();
  return continuous_position;
}

void Encoder::resetEncoder() {
  rotations = 0;
  offset = position;
  Serial.print("Reset "); printInfo();
}