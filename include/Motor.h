#ifndef _MOTOR_H_
#define _MOTOR_H_

#ifndef Arduino
  #include <Arduino.h>
#endif

#ifndef Config
  #include <Config.h>
#endif

// #ifndef PoluluEncoder
//   #include "PoluluEncoder.h"
// #endif

#ifndef AS5600Encoder
  #include "AS5600Encoder.h"
#endif

#define STOPPED 2
#define FORWARD 1
#define REVERSE 0

class Motor
{  
  public:

    Motor() {} // Default constructor

    // Constructor to connect Motor GPIO pins to microcontroller
    Motor(uint8_t pinGroup, uint8_t mode=0);

    // Encoder attached to the motor
    // PoluluEncoder encoder;
    AS5600Encoder encoder;

    // PMW for motors
    const int channel_0 = 0;
    const int channel_1 = 1;
    const int freq = 30000;
    const int resolution = 8;
    const int MAX_DUTY_CYCLE = (int)(pow(2, resolution) - 1);

    void init();

    void applyPower(int16_t speed);

    void applyPWMPower(int16_t speed);

  private:
    // Motor ports
    uint8_t pinGroup_;
    uint8_t mode_;

     int DBSpeed_ = 0;
     int count = 0;

    double applyDeadband(double input, double threshold) {
      if (input < -threshold || input > threshold) {
        return input;
      }
      return 0.0;
    }

    void printPort() {
      if (count > 1000) {
        Serial.print("Ports "); Serial.print(motorPinGroup[pinGroup_].motorIN1); Serial.print(","); Serial.print(motorPinGroup[pinGroup_].motorIN2);Serial.print(": ");
        count = 0;
      }  
      count += 1; 
    }

    void printSpeed() {
      if (count > 1000) {
        Serial.print("Ports "); Serial.print(motorPinGroup[pinGroup_].motorIN1); Serial.print(", ");Serial.print("Speed "); Serial.println(DBSpeed_);
        count = 0;
      }  
      count += 1; 
    }

};

#endif // _MOTOR_H_