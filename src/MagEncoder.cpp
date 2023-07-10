#include "MagEncoder.h"

// Constructor to connect encoder GPIO pins to microcontroller
MagEncoder::MagEncoder(uint8_t pinGroup)
  :pinGroup_(pinGroup)
{
  attachInterrupt (motorPinGroup[pinGroup].encoderA, encoderISRA, CHANGE);  // Left encoder
  instances [0] = this; 

  attachInterrupt (motorPinGroup[pinGroup].encoderB, encoderISRB, CHANGE); // Right encoder
  instances [1] = this;

  // Switch on interrupts
  sei();
  
  // Initialize pulses. 
  ticks = 0;
}  

void IRAM_ATTR MagEncoder::encoderAFired_() {
  // pulses is 4 bytes so make sure that the write is not interupted
  portENTER_CRITICAL_ISR(&timerMux);
  ticks++;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void IRAM_ATTR MagEncoder::encoderBFired_() {
  // pulses is 4 bytes so make sure that the write is not interupted
  portENTER_CRITICAL_ISR(&timerMux);
  ticks--;
  portEXIT_CRITICAL_ISR(&timerMux);
}

