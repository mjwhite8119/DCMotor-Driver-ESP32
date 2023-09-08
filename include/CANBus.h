#pragma once

#ifndef Arduino
  #include <Arduino.h>
#endif

#include "shmem_buffer.h"
#include "CANBuffer.h"

#include <CAN.h>

// Buffer and delay time
CANBuffer<Data, 20> rPiLink;
#define CAN_TX 21 // Orange
#define CAN_RX 22 // Yellow
// #define CAN_TX 16
// #define CAN_RX 17
// #define CAN_TX 5
// #define CAN_RX 4

void setupCANBus() {
  // Default pin CRX (GPIO4) CTX (GPIO5)
  CAN.setPins(CAN_TX,CAN_RX);
  Serial.print("CAN setup on pins TX:RX ");Serial.print(CAN_TX);Serial.print(":");Serial.println(CAN_RX); 

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

int cycle = 0;
void loopCANReceiver() {
  // try to parse packet
  int packetSize = CAN.parsePacket();

  if (packetSize) {
    // received a packet
    Serial.print("Received ");

    if (CAN.packetExtended()) {
      Serial.print("extended ");
    }

    if (CAN.packetRtr()) {
      // Remote transmission request, packet contains no data
      Serial.print("RTR ");
    }

    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    if (CAN.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      Serial.print(" and length ");
      Serial.println(packetSize);

      // only print packet data for non-RTR packets
      while (CAN.available()) {
        Serial.print((char)CAN.read());
      }
      Serial.println();
    }

    Serial.println();
  } else {
    if (cycle > 100000) {
      Serial.print(".");
      cycle = 0;
    }
    cycle++;
  }
}

void loopCANSender() {
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending packet ... ");

  CAN.beginPacket(0x12);
  CAN.write('h');
  CAN.write('e');
  CAN.write('l');
  CAN.write('l');
  CAN.write('o');
  Serial.print("Ready to send");
  CAN.endPacket();

  Serial.println("done");

  delay(1000);

  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending extended packet ... ");

  CAN.beginExtendedPacket(0xabcdef);
  CAN.write('w');
  CAN.write('o');
  CAN.write('r');
  CAN.write('l');
  CAN.write('d');
  CAN.endPacket();

  Serial.println("done");

  delay(1000);
}

