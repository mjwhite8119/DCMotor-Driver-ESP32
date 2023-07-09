#include <Arduino.h>

#include "Config.h"
#include "I2C_Config.h"
#include "Motor.h"

Motor pinkMotor = Motor(ENCODER1, MOTOR1_IN1, MOTOR1_IN2, MOTOR_MODE);
// Motor ringMotor = Motor(RING_IN3, RING_IN4, RING_ENCODER);
// Motor middleMotor = Motor(MIDDLE_IN1, MIDDLE_IN2, MIDDLE_ENCODER);
// Motor indexMotor = Motor(INDEX_IN3, INDEX_IN4, INDEX_ENCODER);

// int loop_count = 0;
// int print_count = 0;
// int button_state = LOW;

void setupMotors() {
  
  pinkMotor.init();
  // ringMotor.init();
  // middleMotor.init();
  // indexMotor.init();
}

void setupButtons() {
  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  pinMode(BUTTON_PIN3, INPUT_PULLUP);
  pinMode(BUTTON_PIN3, INPUT_PULLUP);
}

// -------------------------------------------------- //
// Setup and Main                                     //
// -------------------------------------------------- //
void setup()
{
  Serial.begin(115200);
  Serial.println("Setting Up..."); 

  // setupI2C();
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

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop() {

  // Get the latest data including recent i2c master writes
  rPiLink.updateBuffer();

  int analogValue = analogRead(ANALOG_PIN1); 
  // Rescale to potentiometer's voltage (from 0V to 3.3V):
  float voltage = floatMap(analogValue, 0, 4095, 0, 3.3);

  // print out the value you read:
  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print(", Voltage: ");
  Serial.println(voltage);
  delay(1000);

  // Constantly write the firmware ident
  rPiLink.buffer.firmwareIdent = FIRMWARE_IDENT;
  rPiLink.buffer.status = 1;

  // Update the built-ins.  These are 4 boolean values
  // rPiLink.buffer.builtinDioValues[0] = digitalRead(BUTTON_PIN);

  if (digitalRead(BUTTON_PIN1) == LOW) {
    pinkMotor.encoder.resetEncoder();
    // i2cScan();
    // ringMotor.encoder.resetEncoder();
    // middleMotor.encoder.resetEncoder();
    // indexMotor.encoder.resetEncoder();
  }

  if (digitalRead(BUTTON_PIN2) == LOW) {
    rPiLink.buffer.pinkMotor = 200;
  }
  else if (digitalRead(BUTTON_PIN3) == LOW) {
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
