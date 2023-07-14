#include <Arduino.h>

#include "Config.h"
#include "Util.h"
#include "I2C_Config.h"
#include "Motor.h"
// #include "GameController.h"

Motor pinkMotor = Motor(0, MOTOR_MODE);
// Motor ringMotor = Motor(1, MOTOR_MODE);
// Motor middleMotor = Motor(2, MOTOR_MODE);
// Motor indexMotor = Motor(3, MOTOR_MODE);

int readPot() {
  int analogValue = analogRead(ANALOG_PIN1); 
  int speed = map(analogValue, 0, 4095, 0, 255);
  logOutput(analogValue, speed);
  return speed;
}

void setupMotors() {
  
  pinkMotor.init();
  // ringMotor.init();
  // middleMotor.init();
  // indexMotor.init();
}

void setupButtons() {
  // pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  pinMode(BUTTON_PIN3, INPUT_PULLUP);
  pinMode(BUTTON_PIN4, INPUT_PULLUP);
}


// -------------------------------------------------- //
// Setup and Main                                     //
// -------------------------------------------------- //
void setup()
{
  Serial.begin(115200);
  // Serial.setDebugOutput(true); // So as you can use printf
  Serial.println("Setting Up..."); 

  setupI2C();
  // Join I2C bus as slave with address 0x20 Arduino 1
  // or 0x21 for Arduino 2
  // rPiLink.init(I2C_DEV_ADDR);

  // RPi wants the status to be 1 otherwise it will report a brownout.
  rPiLink.buffer.status = 1;
  rPiLink.buffer.pinkMotor = 0;
  rPiLink.buffer.ringMotor = 0;
  rPiLink.buffer.middleMotor = 0;
  rPiLink.buffer.indexMotor = 0;
  setupButtons();

  setupMotors();
}

void loop() {

  // Get the latest data including recent i2c master writes
  rPiLink.updateBuffer();
  // Constantly write the firmware ident
  rPiLink.buffer.firmwareIdent = FIRMWARE_IDENT;
  rPiLink.buffer.status = 1;

  int speed = readPot();

  rPiLink.buffer.pinkMotor = speed;

  // Update the built-ins.  These are 4 boolean values
  // rPiLink.buffer.builtinDioValues[0] = digitalRead(BUTTON_PIN);

  if (digitalRead(BUTTON_PIN3) == LOW) {
    pinkMotor.encoder.resetEncoder();
    // ringMotor.encoder.resetEncoder();
    // middleMotor.encoder.resetEncoder();
    // indexMotor.encoder.resetEncoder();
  }

  if (digitalRead(BUTTON_PIN2) == LOW) {
    rPiLink.buffer.pinkMotor = 200;
  }
  else if (digitalRead(BUTTON_PIN4) == LOW) {
    rPiLink.buffer.pinkMotor = -200;
  } else {
    rPiLink.buffer.pinkMotor = 0;
  }
  
  // Check if button A is pressed
  // if (rPiLink.buffer.builtinDioValues[0] == HIGH) {
  //   Serial.println("ButtonA is pressed...");
  //   rPiLink.buffer.pinkMotor = 200;
  //   digitalWrite(MOTOR1_IN1, HIGH);
  //   digitalWrite(MOTOR1_IN2, LOW);
  // } 
  // else {
  //   rPiLink.buffer.pinkMotor = 0;
  //   digitalWrite(MOTOR1_IN1, LOW);
  //   digitalWrite(MOTOR1_IN2, LOW);
  // }

  if (MOTOR_MODE == PWM ) {
    pinkMotor.applyPWMPower(rPiLink.buffer.pinkMotor);
  } else {
    pinkMotor.applyPower(rPiLink.buffer.pinkMotor);
  }
  
  
  // ringMotor.applyPower(rPiLink.buffer.ringMotor);
  // middleMotor.applyPower(rPiLink.buffer.middleMotor);
  // indexMotor.applyPower(rPiLink.buffer.indexMotor);

  // Encoders
  // if (rPiLink.buffer.resetLeftEncoder) {
  //   rPiLink.buffer.resetLeftEncoder = false;
  //   pinkMotor.encoder.resetEncoder();
  // }

  // if (rPiLink.buffer.resetRightEncoder) {
  //   rPiLink.buffer.resetRightEncoder = false;
  //   ringMotor.encoder.resetEncoder();
  // }

  // rPiLink.buffer.leftEncoder = encoders.getCountsLeft();
  // rPiLink.buffer.rightEncoder = encoders.getCountsRight();

  // pinkMotor.encoder.readEncoder();
  // ringMotor.encoder.readEncoder();
  // middleMotor.encoder.readEncoder();
  // indexMotor.encoder.readEncoder();

  // Write to buffer
  rPiLink.finalizeWrites();
}
