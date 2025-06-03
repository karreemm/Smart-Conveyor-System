/**
 * Gpio.h - Smart Conveyor Monitoring & Control System
 */

#ifndef GPIO_H
#define GPIO_H

#include "Std_Types.h"

// Port Names 
#define GPIO_A     0
#define GPIO_B     1
#define GPIO_C     2
#define GPIO_D     3

// Pin Numbers
#define GPIO_PIN_0   0
#define GPIO_PIN_1   1
#define GPIO_PIN_2   2
#define GPIO_PIN_3   3
#define GPIO_PIN_4   4
#define GPIO_PIN_5   5
#define GPIO_PIN_6   6
#define GPIO_PIN_7   7
#define GPIO_PIN_8   8
#define GPIO_PIN_9   9
#define GPIO_PIN_10  10
#define GPIO_PIN_11  11
#define GPIO_PIN_12  12
#define GPIO_PIN_13  13
#define GPIO_PIN_14  14
#define GPIO_PIN_15  15

// Pin Modes 
#define GPIO_INPUT   0x00
#define GPIO_OUTPUT  0x01
#define GPIO_AF      0x02
#define GPIO_ANALOG  0x03

// Input States 
#define GPIO_NO_PULL    0x00
#define GPIO_PULL_UP    0x01
#define GPIO_PULL_DOWN  0x02

// Output States 
#define GPIO_PUSH_PULL   0x00
#define GPIO_OPEN_DRAIN  0x01

// Data States
#define GPIO_LOW     0
#define GPIO_HIGH    1

// Edge Detection
#define GPIO_NO_EDGE       0
#define GPIO_FALLING_EDGE  1
#define GPIO_RISING_EDGE   2

// Function Prototypes
void Gpio_Init(uint8 PortName, uint8 PinNumber, uint8 PinMode, uint8 DefaultState);
void Gpio_SetAF(uint8 PortName, uint8 PinNumber, uint8 AFNumber);
void Gpio_WritePin(uint8 PortName, uint8 PinNumber, uint8 Data);
uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNumber);
void Gpio_TogglePin(uint8 PortName, uint8 PinNumber);
uint8 Gpio_DetectEdge(uint8 PortName, uint8 PinNumber);

#endif // GPIO_H