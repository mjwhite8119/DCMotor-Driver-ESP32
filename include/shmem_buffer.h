// AUTOGENERATED FILE. DO NOT MODIFY.
// Generated via `npm run gen-shmem`

// Instance: ef6786ec-24fd-4a0f-9ecd-d8c650a5617e

#pragma once
#include <stdint.h>

#define FIRMWARE_IDENT 126

struct Data {
  uint16_t ioConfig;
  uint8_t firmwareIdent;
  uint8_t status;
  bool heartbeat;
  uint8_t builtinConfig;
  bool builtinDioValues[4];
  int16_t extIoValues[5];
  uint16_t analog[2];
  int16_t pinkMotor;
  int16_t ringMotor;
  int16_t middleMotor;
  int16_t indexMotor;
  uint16_t batteryMillivolts;
  bool resetLeftEncoder;
  bool resetRightEncoder;
  int16_t leftEncoder;
  int16_t rightEncoder;
};
