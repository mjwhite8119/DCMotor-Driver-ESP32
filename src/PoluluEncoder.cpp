#include "PoluluEncoder.h"

PoluluEncoder * PoluluEncoder::instances [2] = { NULL, NULL };

// Constructor to connect encoder GPIO pins to microcontroller
PoluluEncoder::PoluluEncoder(uint8_t pinGroup)
  :pinGroup_(pinGroup)
{
  // Switch on interrupts
  sei();

  // Initialize pulses. 
  ticks = 0;
}  

/*
  Interrupts cannot be attached in the constructor since the interrupt handler 
  may not have been started. With one pin attached you get 6 ticks per/revolution.
  This will be doubled to 12 if both pins are attached.
*/
void PoluluEncoder::init() {
  pinMode(motorPinGroup[pinGroup_].encoderA, INPUT); //  channel A
  pinMode(motorPinGroup[pinGroup_].encoderB, INPUT); //  channel B
  
  attachInterrupt (motorPinGroup[pinGroup_].encoderA, encoderISRA, CHANGE);  // Left encoder
  instances [0] = this; 

  attachInterrupt (motorPinGroup[pinGroup_].encoderB, encoderISRB, CHANGE); // Right encoder
  instances [1] = this;
}

void IRAM_ATTR PoluluEncoder::encoderAFired_() {
  // ticks is 4 bytes so make sure that the write is not interupted
  portENTER_CRITICAL_ISR(&timerMux);
  if (direction == FORWARD) {
    ticks++;
  } else {
    ticks--;
  }
  portEXIT_CRITICAL_ISR(&timerMux);
}

void IRAM_ATTR PoluluEncoder::encoderBFired_() {
  // ticks is 4 bytes so make sure that the write is not interupted
  portENTER_CRITICAL_ISR(&timerMux);
  if (direction == FORWARD) {
    ticks++;
  } else {
    ticks--;
  }
  portEXIT_CRITICAL_ISR(&timerMux);
}

int32_t IRAM_ATTR PoluluEncoder::getCounts() {
  portENTER_CRITICAL_ISR(&timerMux);
  int32_t tmp = ticks;
  portEXIT_CRITICAL_ISR(&timerMux);
  return tmp;
}

