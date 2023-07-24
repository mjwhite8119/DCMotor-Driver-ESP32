#include <Arduino.h>

#include "Config.h"
#include "Util.h"
#include "I2C_Config.h"
#include "Motor.h"
#include "GameController.h"
#include "CANBus.h"

Motor motor1 = Motor(0, MOTOR_MODE);
// Motor motor2 = Motor(1, MOTOR_MODE);
// Motor motor3 = Motor(2, MOTOR_MODE);
// Motor motor4 = Motor(3, MOTOR_MODE);

int readPot() {
  int analogValue = analogRead(ANALOG_PIN1); 
  // Set motor values only in the range 100 to -100
  int speed = map(analogValue, 0, 4095, 0, 100);
  logOutput(analogValue, speed);
  return speed;
}

void useButtons() {
  // Set motor values only in the range 100 to -100
  if (digitalRead(BUTTON_PIN2) == LOW) {
    rPiLink.buffer.motor1 = 100;
  }
  else if (digitalRead(BUTTON_PIN4) == LOW) {
    rPiLink.buffer.motor1 = -100;
  } else {
    rPiLink.buffer.motor1 = 0;
  }
}

void usePot() {
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

  setupI2CClient();

  // setupI2CServer();

  // Pretend the ESP32 is the Raspberry Pi by using
  // the Pi's MAC address
  uint8_t new_mac[8] = {0xDC,0xA6,0x32,0x75,0x2E,0xAD};
  ps3SetBluetoothMacAddress(new_mac);

  // Define Callback Function
  Ps3.attach(notify);
  // Define On Connection Function
  Ps3.attachOnConnect(onConnect);
  // Emulate console as specific MAC address (change as required)
  // Ps3.begin("98:B6:5A:26:93:40");
  Ps3.begin("DC:A6:32:75:2E:AD");
  // Ps3.begin();
  String address = Ps3.getAddress();
  Serial.println(address);

  // RPi wants the status to be 1 otherwise it will report a brownout.
  // rPiLink.buffer.status = 1;

  setupButtons();

  setupMotors();
}

void loop() {

  // Get the latest data including recent i2c master writes
  rPiLink.updateBuffer();

  if (Ps3.isConnected()){
    Serial.println("Connected!");
  }

  delay(3000);
  // if (!Ps3.isConnected())
  //   Serial.println("PS3 Not connected");
  //   delay(2000);
  // Use potentiometer to control motors
  // usePot();

  // Use push buttons to control motors
  // useButtons();

  // Set motor values only in the range 100 to -100
  // testEncoders();
  
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

  // Write to buffer
  rPiLink.finalizeWrites();
}
