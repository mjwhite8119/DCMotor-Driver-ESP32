#include "AS5600Encoder.h"

// Constructor to connect encoder GPIO pins to microcontroller
AS5600Encoder::AS5600Encoder(uint8_t pinGroup)
  :pinGroup_(pinGroup)
{
  // Initialize pulses. 
  ticks = 0;
}  

/*
  Initialization 
*/
void AS5600Encoder::init() {
  pinMode(motorPinGroup[pinGroup_].encoderA, INPUT); //  channel A
  pinMode(motorPinGroup[pinGroup_].encoderB, INPUT); //  channel B
}