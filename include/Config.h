#pragma once
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
#define ENCODER1 36 // PINK_ENCODER
#define ENCODER2 39 // RING_ENCODER
#define ENCODER3 34 // MIDDLE_ENCODER
#define ENCODER4 35 // INDEX_ENCODER
#define ENCODER5 32
#define ENCODER6 33
#define ENCODER7 25
#define ENCODER8 26

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

// Define the motor mode here!
#define DIGITAL 0
#define PWM 1
#define MOTOR_MODE PWM

// Define buttons
#define BUTTON_PIN1 12 // ADC
#define BUTTON_PIN2 14 // ADC
#define BUTTON_PIN3 27 // ADC
#define BUTTON_PIN4 23

// Can also use for analog reads
#define ANALOG_PIN1 12 // ADC
#define ANALOG_PIN2 14 // ADC