#ifndef _BOURN_ENCODER_H_
#define _BOURN_ENCODER_H_

#ifndef Arduino
  #include <Arduino.h>
#endif

#define STOPPED 2
#define FORWARD 1
#define REVERSE 0

class BournEncoder
{  
   public:

    BournEncoder() {} // Default constructor  

    uint8_t direction = STOPPED;
    int16_t rotations = 0;
    int16_t position = 0;
    int16_t raw = 0;
    int16_t offset = 0;
    boolean transitioning = false;

    // Constructor to connect encoder GPIO pins to microcontroller
    BournEncoder(uint8_t port);

    void init();

    int16_t readEncoder();

    int16_t getRotations() {return rotations * 100;}
    int16_t getPosition() {return position - offset;}

    void resetEncoder();

    void printPort() {
      Serial.print("Port "); Serial.print(port_);Serial.print(": ");
    }

    void printPosition() {
      Serial.print(" Position "); Serial.println(position);
    }

    void printRotations() {
      Serial.print(" Rotations "); Serial.println(rotations);
    }

    void printInfo() {
      if (count > 10) {
        printPort(); Serial.print(rotations); Serial.print(":"); Serial.print(position);
       Serial.print(" Raw "); Serial.print(raw);Serial.print(" Offset "); Serial.print(offset);
       Serial.print(" Continuous Position "); Serial.println(continuous_position);
        count = 0;
      }  
      count += 1;   
    }

  private:

    uint8_t port_;
    int16_t continuous_position = 0;
    int count = 0;

    int16_t applyDeadband(int16_t input, const int16_t threshold) {
      if (input < -threshold || input > threshold) {
        return input;
      }
      return 0;
    }

};

#endif // _BOURN_ENCODER_H_