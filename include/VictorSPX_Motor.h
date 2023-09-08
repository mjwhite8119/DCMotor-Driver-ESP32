#ifndef _VICTOR_SPX_MOTOR_H_
#define _VICTOR_SPX_MOTOR_H_

#ifndef Arduino
  #include <Arduino.h>
#endif

#ifndef Config
  #include <Config.h>
#endif


#ifndef AS5600Encoder
  #include "AS5600Encoder.h"
#endif

#define STOPPED 2
#define FORWARD 1
#define REVERSE 0

class VictorSPX_Motor
{  
  public:

    VictorSPX_Motor() {} // Default constructor

    // Constructor to connect Motor GPIO pins to microcontroller
    VictorSPX_Motor(uint8_t pinGroup, uint8_t mode=0);

    // Encoder attached to the motor
    AS5600Encoder encoder;

    // PMW for motors
    // The PWM signal used to control the Victor SP should be between 1-2ms in 
    // duration with a center (neutral) pulse of 1.5ms and a period between 2.9-100ms. 
    // The PWM period is how fast the robot controller can send a new PWM pulse. 
    // The amount of time between the rising edge of one PWM pulse to the next PWM pulse 
    // should not be less than 2.9ms or greater than 100ms.
    const int channel_0 = 0;
    const int freq = 30000; // 30kHz
    const int resolution = 8;
    const int MAX_DUTY_CYCLE = (int)(pow(2, resolution) - 1); // 255

    void init();

    void applyPower(int16_t speed);

    void applyPWMPower(int16_t speed);

  private:
    // Motor ports
    uint8_t pinGroup_;
    uint8_t port_;
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
      if (count > 10000) {
        Serial.print("Port "); Serial.println(port_);
        count = 0;
      }  
      count += 1; 
    }

    void printSpeed() {
      if (count > 10000) {
        Serial.print("Port "); Serial.print(port_); Serial.print(", ");Serial.print("Speed "); Serial.println(DBSpeed_);
        count = 0;
      }  
      count += 1; 
    }

};

#endif // _VICTOR_SPX_MOTOR_H_