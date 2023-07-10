#pragma once

#ifndef Arduino
  #include <Arduino.h>
#endif

#ifndef Config
  #include <Config.h>
#endif

#define STOPPED 2
#define FORWARD 1
#define REVERSE 0

class MagEncoder
{  
   public:

    // Mutex for protecting critical code in interrupts
    portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

    MagEncoder() {} // Default constructor  

    // Constructor to connect encoder GPIO pins to microcontroller
    MagEncoder(uint8_t pinGroup);

    // Ticks of the right and left encoder. This is volatile so 
    // that it doesn't interfere with the rest of the code.
    volatile int32_t ticks = 0;
    uint8_t direction = STOPPED;

    // Encoder interrupt routines
    static void encoderISRA ()
    {
      if (MagEncoder::instances [0] != NULL)
        MagEncoder::instances [0]->encoderAFired_();
    } 
    
    static void encoderISRB ()
    {
      if (MagEncoder::instances [1] != NULL)
        MagEncoder::instances [1]->encoderBFired_();
    }
      
    // Instance members to get encoder ticks. Called from ISR

    // Checks encoder A
    void IRAM_ATTR encoderAFired_();

    // Checks encoder B
    void IRAM_ATTR encoderBFired_();

    void resetEncoder() {
      ticks = 0;
    }

    int32_t readEncoder() {
      return ticks;
    }

    void printInfo() {
      Serial.print("Ticks:");Serial.print(ticks);      
    }

    void printPort() {
      // Serial.print("Port "); Serial.print(portA_);Serial.print(": ");
    }


    static MagEncoder * instances [2];

  private:

    uint8_t pinGroup_;
};    