# DCMotor Driver for ESP32
Purpose of this project...

![NODEMCU](assets/DCMotor-Driver/DCMotor-Driver.002.jpeg)

## Pinout
![NODEMCU](assets/DCMotor-Driver/DCMotor-Driver.001.jpeg)

## Motors
The buffer for motors is int8, so only values of 128 to -128 is possible.  For the most part we'll only use -100 to 100.

## Polulu Encoders
Using both interrupts gives 12 ticks per/revolution.  A single interrupt give only 6 ticks per/revolution.

## CANbus

Uses the ESP32 implementation [ESP32-Arduino-CAN](https://github.com/miwagner/ESP32-Arduino-CAN/tree/master/src). Set the speed to 500kBps.  You can set the TX and RX to any PWM pins.

    CAN_cfg.speed = CAN_SPEED_500KBPS;

