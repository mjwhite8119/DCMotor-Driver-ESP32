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
  Serial.println("onRequest");
  rPiLink.transmit();
}

// Incoming from the wire
void onReceive(int len){
  
  Serial.printf("onReceive[%d]: ", len);Serial.println();

  rPiLink.updateI2CBuffer();

  rPiLink.i2c_write_length = 0;
  bool first_byte = true;
  while(Wire.available()){
    if (first_byte) {
      Wire.read();
      first_byte = false;  
    }
    rPiLink.receive();
  }

  rPiLink.printWriteBuffer();

  rPiLink.finalizeI2CWrites();
  rPiLink.updateBuffer();

  rPiLink.printBuffer();
  
  Serial.println("Motors");
  Serial.println(rPiLink.buffer.motor1);
  Serial.println(rPiLink.buffer.motor2);
  Serial.println(rPiLink.buffer.motor6);
  Serial.println("Encoders");
  Serial.println(rPiLink.buffer.encoder1); 
  Serial.println(rPiLink.buffer.encoder2);
  Serial.println(rPiLink.buffer.encoder6);
}

void setupI2CServer() {

}

void setupI2CClient() {
 
  // rPiLink.init(I2C_DEV_ADDR);
  pinMode(I2C_SDA, INPUT_PULLUP);
  pinMode(I2C_SCL, INPUT_PULLUP);

  // Join I2C bus as slave with address 0x20 Arduino 1
  // Use the defaults for SDA and SCL
  bool ready = Wire.begin((uint8_t)I2C_DEV_ADDR);
  
  Wire.onReceive(onReceive); // receive register value
  Wire.onRequest(onRequest); // send register value
  
  Serial.println("Setup I2C");

  // RPi wants the status to be 1 otherwise it will report a brownout.
  // rPiLink.buffer.status = 1;

#if CONFIG_IDF_TARGET_ESP32
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