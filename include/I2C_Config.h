#pragma once

#ifndef Arduino
  #include <Arduino.h>
#endif

#include "Wire.h"
#include "shmem_buffer.h"
#include "ESP32RPiSlave.h"

// Addresses for esp32s
#define I2C_DEV_ADDR 0x55

#define I2C_SDA 21
#define I2C_SCL 22

// Buffer and delay time
ESP32RPiSlave<Data, 20> rPiLink;

void onRequest(){
  // Wire.print(i++);
  // Wire.print(" Packets.");
  // Serial.println("onRequest");
  rPiLink.transmit();
}

void onReceive(int len){
  rPiLink.receive(len);
  // Serial.printf("onReceive[%d]: ", len);
  // while(Wire.available()){
  //   Serial.write(Wire.read());
  // }
  // Serial.println();
}

void setupI2C() {
  // Join I2C bus as slave with address 0x20 Arduino 1
  // or 0x21 for Arduino 2

  // rPiLink.init(I2C_DEV_ADDR);
  pinMode(I2C_SDA, INPUT_PULLUP);
  pinMode(I2C_SCL, INPUT_PULLUP);
  
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  Wire.begin(I2C_DEV_ADDR, I2C_SDA, I2C_SCL);

// #if CONFIG_IDF_TARGET_ESP32
//   char message[64];
//   snprintf(message, 64, "%u Packets.", i++);
//   Wire.slaveWrite((uint8_t *)message, strlen(message));
// #endif
}

void i2cScan() {
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
      nDevices++;
    }
    else if (error==4) {
      Serial.print("Unknow error at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("done\n");
  }
}