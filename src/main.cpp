#include <Arduino.h>

#include "Config.h"
#include "Util.h"

// Use either on rPiLink is defined in both
// #include "I2C_Config.h"
#include "CanBus.h"

#include "Motor.h"
// #include "GameController.h"

Motor motor1 = Motor(0, MOTOR_MODE);
// Motor motor2 = Motor(1, MOTOR_MODE);
// Motor motor3 = Motor(2, MOTOR_MODE);
// Motor motor4 = Motor(3, MOTOR_MODE);

// ----------------------------------------------------
// These loopXXX functions are meant to be inserted 
// into the main loop as needed.
// ----------------------------------------------------
void loopMotors() {
  
  if (MOTOR_MODE == PWM ) {
    motor1.applyPWMPower(rPiLink.buffer.motor1);
  } else {
    motor1.applyPower(rPiLink.buffer.motor1);
  }
}

void loopEncoders() {
  // Reset the encoders
  if (digitalRead(BUTTON_PIN3) == LOW) {
    motor1.encoder.resetEncoder();
  }

  if (MOTOR_MODE == PWM ) {
    motor1.applyPWMPower(rPiLink.buffer.motor1);
  } else {
    motor1.applyPower(rPiLink.buffer.motor1);
  }

  // Encoders
  // if (rPiLink.buffer.resetLeftEncoder) {
  //   rPiLink.buffer.resetLeftEncoder = false;
  //   Motor1.encoder.resetEncoder();
  // }

  // if (rPiLink.buffer.resetRightEncoder) {
  //   rPiLink.buffer.resetRightEncoder = false;
  //   Motor2.encoder.resetEncoder();
  // }
}

int readPot() {
  int analogValue = analogRead(ANALOG_PIN1); 
  // Set motor values only in the range 100 to -100
  int speed = map(analogValue, 0, 4095, 0, 100);
  logOutput(analogValue, speed);
  return speed;
}

int buttonPeriod = 0;
void loopButtons() {
  // Set motor values only in the range 100 to -100
  if (digitalRead(BUTTON_PIN2) == LOW) {
    if (motor1.encoder.getCounts() > 200) {
      rPiLink.buffer.motor1 = 0;
    } else {
      rPiLink.buffer.motor1 = 255;
    }   
  }
  else if (digitalRead(BUTTON_PIN4) == LOW) {
    if (motor1.encoder.getCounts() < 0) {
      rPiLink.buffer.motor1 = 0;
    } else {
      rPiLink.buffer.motor1 = -200;
    }  
  } else {
    rPiLink.buffer.motor1 = 0;
    buttonPeriod = 0;
  }
}

void loopPulseButtons() {
  if (buttonPeriod < 3000){
    loopButtons();
  } else { 
    rPiLink.buffer.motor1 = 0;
  }
  buttonPeriod++;
  if (digitalRead(BUTTON_PIN4) == HIGH & digitalRead(BUTTON_PIN2) == HIGH) {
    buttonPeriod = 0;
  }
}

void loopPot() {
  // Set motor values only in the range 100 to -100
  int speed = readPot();
  rPiLink.buffer.motor1 = speed;
}

void testEncoders() {
  // Set motor values only in the range 100 to -100
  rPiLink.buffer.motor1 = 100;
}

void setupMotors() { 
  motor1.init();
  // motor2.init();
  // motor3.init();
  // motor4.init();

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
  while (!Serial);

  // Serial.setDebugOutput(true); // So as you can use printf
  Serial.println("Setting Up...");

  pinMode (2, OUTPUT);
  // setupI2CClient();

  setupCANBus();

  // setupI2CServer();

  // PS3ControllerSetup();

  setupButtons();

  // setupMotors();
}

void loop() {

  // Get the latest data including recent i2c master writes
  rPiLink.updateBuffer();

  // Use the CANBUS
  loopCANReceiver();
  // loopCANSender();

  // Use potentiometer to control motors
  // loopPot();

  // Use push buttons with short pulses
  // loopPulseButtons();
  
  // Use push buttons to control motors
  // loopButtons();
  
  // Set motor values only in the range 100 to -100
  // testEncoders();
  
  // Use encoders 
  // loopEncoders();

  // Use micro motors
  // loopMotors();

  // Write to buffer
  rPiLink.finalizeWrites();
}
