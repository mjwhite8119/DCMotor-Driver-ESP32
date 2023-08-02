#include "AS5600Encoder.h"

// Constructor to connect encoder GPIO pins to microcontroller
AS5600Encoder::AS5600Encoder(uint8_t pinGroup)
  :pinGroup_(pinGroup)
{
  // Initialize pulses. 
  angle = 0;
}  

/*
  Initialization 
*/
void AS5600Encoder::init() {
  pinMode(motorPinGroup[pinGroup_].encoderA, INPUT); //  channel A
  
  // pinMode(motorPinGroup[pinGroup_].encoderB, INPUT); //  channel B
  // Wire.begin();
  // //  as5600.begin(14,15);
  // as5600.begin(4);  //  set direction pin.
  // as5600.setDirection(AS5600_CLOCK_WISE);  // default, just be explicit.

  // Serial.println(as5600.getAddress());

  // int b = as5600.isConnected();
  // Serial.print("Connect: ");
  // Serial.println(b);

  // Serial.println("14CORE | AS5600 TEST CODE ( Reading Angles )");
  // Serial.println("Initializing .............................. ");
  // if(as5600.detectMagnet() == 0 ){
  //   while(1){
  //       if(as5600.detectMagnet() == 1 ){
  //           Serial.print("Current Magnitude: ");
  //           Serial.println(as5600.readMagnitude());
  //           break;
  //       }
  //       else{
  //           /* Make it sure your magnet is place at the top of the AS5600 sensor distance of 0.5 mm */
  //           Serial.println("ERROR : Can not detect magnet ");
  //       }
  //       delay(1000);
  //   }
  // }
}

float AS5600Encoder::convertRawAngleToDegrees(word newAngle)
{
  /* Raw data reports 0 - 4095 segments, which is 0.087 of a degree */
  float retVal = newAngle * 0.087;
  return retVal;
}

int32_t AS5600Encoder::getCounts() {
  // angle = convertRawAngleToDegrees(as5600.rawAngle());
  angle = analogRead(motorPinGroup[pinGroup_].encoderA);
  return angle;
}