#include <Arduino.h>

#include "Config.h"
#include "Util.h"
#include "I2C_Config.h"
#include "Motor.h"
// #include "GameController.h"

Motor motor1 = Motor(0, MOTOR_MODE);
// Motor motor2 = Motor(1, MOTOR_MODE);
// Motor motor3 = Motor(2, MOTOR_MODE);
// Motor motor4 = Motor(3, MOTOR_MODE);

int readPot() {
  int analogValue = analogRead(ANALOG_PIN1); 
  int speed = map(analogValue, 0, 4095, 0, 255);
  logOutput(analogValue, speed);
  return speed;
}

void setupMotors() {
  
  motor1.init();
  // Motor2.init();
  // Motor3.init();
  // Motor4.init();

  // Setup the communication links
  rPiLink.buffer.motor1 = 0;
  rPiLink.buffer.motor2 = 0;
  rPiLink.buffer.motor3 = 0;
  rPiLink.buffer.motor4 = 0;
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
  // rPiLink.buffer.status = 1;

  setupButtons();

  setupMotors();
}

void loop() {

  // Get the latest data including recent i2c master writes
  rPiLink.updateBuffer();
  // Constantly write the firmware ident

  // rPiLink.buffer.motor1 = 1;
  // rPiLink.buffer.motor2 = 2;
  // rPiLink.buffer.motor3 = 3;
  // rPiLink.buffer.motor4 = 4;
  // rPiLink.buffer.motor5 = 5;
  // rPiLink.buffer.motor6 = 8;

  // rPiLink.buffer.encoder1 = 29345;
  // rPiLink.buffer.encoder2 = 201;
  // rPiLink.buffer.encoder3 = 202;
  // rPiLink.buffer.encoder4 = 255;
  // rPiLink.buffer.encoder5 = 256;
  // rPiLink.buffer.encoder6 = 23777;

  // rPiLink.buffer.firmwareIdent = FIRMWARE_IDENT;
  // rPiLink.buffer.status = 1;

  int speed = readPot();

  rPiLink.buffer.motor1 = speed;

  // Update the built-ins.  These are 4 boolean values
  // rPiLink.buffer.builtinDioValues[0] = digitalRead(BUTTON_PIN);

  if (digitalRead(BUTTON_PIN3) == LOW) {
    motor1.encoder.resetEncoder();
    // Motor2.encoder.resetEncoder();
    // Motor3.encoder.resetEncoder();
    // Motor4.encoder.resetEncoder();
  }

  if (digitalRead(BUTTON_PIN2) == LOW) {
    rPiLink.buffer.motor1 = 200;
  }
  else if (digitalRead(BUTTON_PIN4) == LOW) {
    rPiLink.buffer.motor1 = -200;
  } else {
    rPiLink.buffer.motor1 = 0;
  }
  
  // Check if button A is pressed
  // if (rPiLink.buffer.builtinDioValues[0] == HIGH) {
  //   Serial.println("ButtonA is pressed...");
  //   rPiLink.buffer.Motor1 = 200;
  //   digitalWrite(MOTOR1_IN1, HIGH);
  //   digitalWrite(MOTOR1_IN2, LOW);
  // } 
  // else {
  //   rPiLink.buffer.Motor1 = 0;
  //   digitalWrite(MOTOR1_IN1, LOW);
  //   digitalWrite(MOTOR1_IN2, LOW);
  // }

  if (MOTOR_MODE == PWM ) {
    motor1.applyPWMPower(rPiLink.buffer.motor1);
  } else {
    motor1.applyPower(rPiLink.buffer.motor1);
  }
  
  
  // Motor2.applyPower(rPiLink.buffer.Motor2);
  // Motor3.applyPower(rPiLink.buffer.Motor3);
  // Motor4.applyPower(rPiLink.buffer.Motor4);

  // Encoders
  // if (rPiLink.buffer.resetLeftEncoder) {
  //   rPiLink.buffer.resetLeftEncoder = false;
  //   Motor1.encoder.resetEncoder();
  // }

  // if (rPiLink.buffer.resetRightEncoder) {
  //   rPiLink.buffer.resetRightEncoder = false;
  //   Motor2.encoder.resetEncoder();
  // }


  // Motor1.encoder.readEncoder();
  // Motor2.encoder.readEncoder();
  // Motor3.encoder.readEncoder();
  // Motor4.encoder.readEncoder();

  // Write to buffer
  rPiLink.finalizeWrites();
}
