#ifndef _CONFIG_H_
#define _CONFIG_H_
/*
  This configuration is for the ESP32 NodeMCU development board.
*/

// TwoWire I2CBME = TwoWire(0); 
// #define ARDUINO_1_ADDRESS 20 // I2C Address of Arduino 1
// #define ARDUINO_2_ADDRESS 21 // I2C Address of Arduino 1

// Addresses for esp32s
#define I2C_DEV_ADDR 0x55

#define TXD 1
#define RXD 3 

// --- Define ENCODERS ---
// These refer to the GPIO numbers
#define ENCODER1_A 36 
#define ENCODER1_B 39 

#define ENCODER2_A 34 
#define ENCODER2_B 35 

#define ENCODER3_A 32
#define ENCODER3_B 33

#define ENCODER4_A 25
#define ENCODER4_B 26

// --- Define MOTORS ---
// These refer to the GPIO numbers
#define MOTOR1_IN1 13 // PINK_IN1
#define MOTOR1_IN2 9 // PINK_IN2 

#define MOTOR2_IN1 10 // RING_IN3 
#define MOTOR2_IN2 11 // RING_IN4 

#define MOTOR3_IN1 19 // MIDDLE_IN1
#define MOTOR3_IN2 18 // MIDDLE_IN2 

#define MOTOR4_IN1 5 // INDEX_IN3
#define MOTOR4_IN2 17 // INDEX_IN4

#define MOTOR5_IN1 16
#define MOTOR5_IN2 4

#define MOTOR6_IN1 0
#define MOTOR6_IN2 2 

#define MOTOR7_IN1 15
#define MOTOR7_IN2 8

#define MOTOR8_IN1 7
#define MOTOR8_IN2 6 

//---------------------------------------
// Define the GPIO pins for the motors
//---------------------------------------
static struct DRAM_ATTR MotorPins {
  const byte motorIN1; // motor IN1 pin1
  const byte motorIN2; // motor IN2 pin2
  const byte encoderA; // encoder channel A
  const byte encoderB; // encoder channel B
} motorPinGroup[4] = {MOTOR1_IN1, MOTOR1_IN2, ENCODER1_A, ENCODER1_B,
                      MOTOR2_IN1, MOTOR2_IN2, ENCODER2_A, ENCODER2_B,
                      MOTOR3_IN1, MOTOR3_IN2, ENCODER3_A, ENCODER3_B,
                      MOTOR4_IN1, MOTOR4_IN2, ENCODER4_A, ENCODER4_B};

// Define the motor mode here!
#define DIGITAL 0
#define PWM 1
#define MOTOR_MODE DIGITAL

// Define buttons
#define BUTTON_PIN1 12 // ADC
#define BUTTON_PIN2 14 // ADC
#define BUTTON_PIN3 27 // ADC
#define BUTTON_PIN4 23

// Can also use for analog reads
#define ANALOG_PIN1 12 // ADC
#define ANALOG_PIN2 14 // ADC

#endif // _CONFIG_H_