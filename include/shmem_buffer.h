// AUTOGENERATED FILE. DO NOT MODIFY.
// Generated via `npm run gen-shmem`

// Instance: ef6786ec-24fd-4a0f-9ecd-d8c650a5617e

#pragma once
#include <stdint.h>

#define FIRMWARE_IDENT 21

struct Data {
  // uint8_t firmwareIdent;
  // uint8_t status;
  // bool heartbeat;
  // uint16_t batteryMillivolts;
  int8_t motor1;
  int8_t motor2;
  int8_t motor3;
  int8_t motor4;
  int8_t motor5;
  int8_t motor6;
  bool resetEncoder1;
  bool resetEncoder2;
  bool resetEncoder3;
  bool resetEncoder4;
  bool resetEncoder5;
  bool resetEncoder6;
  int16_t encoder1;
  int16_t encoder2;
  int16_t encoder3;
  int16_t encoder4;
  int16_t encoder5;
  int16_t encoder6;
};

