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

class AS5600Encoder
{  
   public:

    AS5600Encoder() {} // Default constructor  

    // Constructor to connect encoder GPIO pins to microcontroller
    AS5600Encoder(uint8_t pinGroup);

    // Ticks of the right and left encoder. This is volatile so 
    // that it doesn't interfere with the rest of the code.
    volatile int32_t ticks = 0;
    uint8_t direction = STOPPED;
    int count = 0;
      
    void init();

    void resetEncoder() {
      ticks = 0;
      printPort();Serial.println(" Encoder reset");
    }

    int32_t getCounts();

    void printInfo() {
      if (count > 10000) {
        Serial.print("Ticks:");Serial.println(getCounts());   
        count = 0;
      }  
      count += 1; 
    }

    void printPort() {
      Serial.print("Port ");Serial.print(motorPinGroup[pinGroup_].encoderA);
    }

  private:

    uint8_t pinGroup_;
};    
