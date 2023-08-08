#include "Motor.h"

// -------------------Constructors -----------------------------------

// Constructor to connect Motor GPIO pins to microcontroller
Motor::Motor(uint8_t pinGroup, uint8_t mode)
  :encoder(pinGroup), mode_(mode) 
  {
    if (mode == 1) {
      // create a PWM channels
      ledcSetup(channel_0, freq, resolution); 
      ledcSetup(channel_1, freq, resolution); 

      // attach channels to pins
      ledcAttachPin(motorPinGroup[pinGroup].motorIN1, channel_0); 
      ledcAttachPin(motorPinGroup[pinGroup].motorIN2, channel_1);

      // Make sure motor is off
      ledcWrite(channel_0, 0);
      ledcWrite(channel_1, 0);
      
    } else {
      pinMode(motorPinGroup[pinGroup].motorIN1,OUTPUT);
      pinMode(motorPinGroup[pinGroup].motorIN2,OUTPUT); 

      // Make sure motor is off
      digitalWrite(motorPinGroup[pinGroup].motorIN1, LOW);
      digitalWrite(motorPinGroup[pinGroup].motorIN2, LOW);
    }
    pinGroup_ = pinGroup;
  }  


void Motor::init() {
  Serial.print("Motor initiated on "); printPort(); Serial.println("");
  encoder.init();

  encoder.resetEncoder();
  Serial.print("Encoder "); encoder.printPort(); Serial.println("");
}

/*                IN3/IN1           IN4/IN2
  Forward          HIGH              LOW
  Reverse          LOW               HIGH
  Stop             LOW               LOW
  Stop             HIGH              HIGH 
*/ 
void Motor::applyPower(int16_t speed){
  // Serial.print(speed);
  DBSpeed_ = applyDeadband(speed, 10);
  if (DBSpeed_ > 400) {DBSpeed_ = 0;} // Take care of random values 
  
  if (DBSpeed_ == 0) {
    digitalWrite(motorPinGroup[pinGroup_].motorIN1, LOW);
    digitalWrite(motorPinGroup[pinGroup_].motorIN2, LOW);
    encoder.direction = STOPPED;
    // encoder.printInfo();
  }
  else if( DBSpeed_ > 0) {
    digitalWrite(motorPinGroup[pinGroup_].motorIN1, HIGH);
    digitalWrite(motorPinGroup[pinGroup_].motorIN2, LOW);
    encoder.direction = FORWARD;
    // printSpeed();
    // Serial.print("Flexing ");
    encoder.printInfo();
  }
  else {
    digitalWrite(motorPinGroup[pinGroup_].motorIN1, LOW);
    digitalWrite(motorPinGroup[pinGroup_].motorIN2, HIGH);
    encoder.direction = REVERSE;
    // printSpeed();
    // Serial.print("Extending "); 
    encoder.printInfo();
  }
}

void Motor::applyPWMPower(int16_t speed) {

  // Don't try and move unless we have at least 100 PWM
  DBSpeed_ = applyDeadband(speed, 100);
  if (DBSpeed_ > MAX_DUTY_CYCLE) {
    DBSpeed_ = MAX_DUTY_CYCLE;
  }
  
  if (DBSpeed_ == 0) {
    ledcWrite(channel_0, 0); // Write a LOW
    ledcWrite(channel_1, 0); // Write a LOW
    encoder.direction = STOPPED;
  } 
  else if (DBSpeed_ > 0) {
    ledcWrite(channel_0, abs(DBSpeed_)); // PWM speed
    ledcWrite(channel_1, 0);  // Write a LOW
    encoder.direction = FORWARD;

    // printSpeed();
    encoder.printInfo();
    // Serial.print("Finger flexed ");encoder.printInfo();
  }
  else {
    ledcWrite(channel_1, abs(DBSpeed_)); // PWM speed
    ledcWrite(channel_0, 0);  // Write a LOW
    encoder.direction = REVERSE;

    // printPort(); 
    // printSpeed();
    encoder.printInfo();
    // Serial.print("Finger extended "); encoder.printInfo();
  }
}