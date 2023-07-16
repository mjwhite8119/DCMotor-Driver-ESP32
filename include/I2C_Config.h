#pragma once

#ifndef Arduino
  #include <Arduino.h>
#endif

#include "Wire.h"
#include "shmem_buffer.h"
#include "ESP32RPiSlave.h"
#ifndef WireSlave
  #include <WireSlave.h>
#endif

// Addresses for esp32s
#define I2C_DEV_ADDR 0x55

#define I2C_SDA 21
#define I2C_SCL 22

int howManyBytesReceived;
uint8_t registerCode;

// Buffer and delay time
ESP32RPiSlave<Data, 20> rPiLink;

int request_counter=0;
// Outgoing to the wire
void onRequest(){

  // Wire.print(request_counter++);
  // Wire.print(" Packets.");
  // Serial.println("onRequest");

  // rPiLink.writeBuffer();

  // Serial.println(rPiLink.transmit());
  // rPiLink.createBuffer();
  rPiLink.transmit();
}

// Incoming from the wire
void onReceive(int len){
  
  Serial.printf("onReceive[%d]: ", len);Serial.println();

  rPiLink.updateI2CBuffer();

  rPiLink.receive(len);

  rPiLink.finalizeI2CWrites();

  // while(Wire.available()){
  //   Serial.print(Wire.read());
  // }
  Serial.println(rPiLink.buffer.Motor1);
}

void setupI2C() {
 
  // rPiLink.init(I2C_DEV_ADDR);
  pinMode(I2C_SDA, INPUT_PULLUP);
  pinMode(I2C_SCL, INPUT_PULLUP);

  // Join I2C bus as slave with address 0x20 Arduino 1
  // Use the defaults for SDA and SCL
  bool ready = Wire.begin((uint8_t)I2C_DEV_ADDR);
  
  Wire.onReceive(onReceive); // receive register value
  Wire.onRequest(onRequest); // send register value
  
  Serial.println("Setup I2C");

#if CONFIG_IDF_TARGET_ESP32
  // char message[64];
  // snprintf(message, 64, "%u Packets.", request_counter++);
  // Wire.slaveWrite((uint8_t *)&rPiLink.buffer, 32);
  rPiLink.init();
#endif
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