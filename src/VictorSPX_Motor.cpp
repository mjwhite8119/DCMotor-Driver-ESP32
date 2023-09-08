#include "VictorSPX_Motor.h"

// -------------------Constructors -----------------------------------

// Constructor to connect Motor GPIO pins to microcontroller
VictorSPX_Motor::VictorSPX_Motor(uint8_t pinGroup, uint8_t mode)
  :encoder(pinGroup), mode_(mode) 
  {
    // Can only run in PWM mode

    // create a PWM channels. Requires only one
    ledcSetup(channel_0, freq, resolution); 

    // attach channels to pins
    port_ = motorPinGroup[pinGroup].motorIN2;
    ledcAttachPin(port_, channel_0);

    // Make sure motor is off
    ledcWrite(channel_0, 0);
    
    pinGroup_ = pinGroup;
  }  


void VictorSPX_Motor::init() {
  Serial.print("Motor initiated on "); Serial.println(port_);
  // encoder.init();

  // encoder.resetEncoder();
  // Serial.print("Encoder "); encoder.printPort(); Serial.println("");
}

void VictorSPX_Motor::applyPower(int16_t speed){
  // VictorSPX only uses PWM
  Serial.print("VictorSPX must use PWM!");
}

void VictorSPX_Motor::applyPWMPower(int16_t speed) {

  // Don't try and move unless we have at least 100 PWM
  DBSpeed_ = applyDeadband(speed, 10);
  if (DBSpeed_ > MAX_DUTY_CYCLE) {
    DBSpeed_ = MAX_DUTY_CYCLE;
  }
  printSpeed();
  
  if (DBSpeed_ == 0) {
    ledcWrite(channel_0, 0); // Write a LOW
    encoder.direction = STOPPED;
  } 
  else if (DBSpeed_ > 0) {
    encoder.direction = FORWARD;
  }
  else {
    encoder.direction = REVERSE;
  }
  ledcWrite(channel_0, abs(DBSpeed_)); // PWM speed
}