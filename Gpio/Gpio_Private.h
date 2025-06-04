/**
 * Gpio_Private.h - Smart Conveyor Monitoring & Control System
 */

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

#include "Gpio.h"

#define RCC_BASE        0x40023800  // STM32F4xx RCC base
#define RCC_AHB1ENR     (*(volatile uint32*)(RCC_BASE + 0x30))

// Clock enable bits for GPIO ports
#define RCC_GPIOA_EN    (1 << 0)
#define RCC_GPIOB_EN    (1 << 1)
#define RCC_GPIOC_EN    (1 << 2)
#define RCC_GPIOD_EN    (1 << 3)

// GPIO Base Addresses 
#define GPIOA_BASE    0x40020000
#define GPIOB_BASE    0x40020400
#define GPIOC_BASE    0x40020800
#define GPIOD_BASE    0x40020C00

// Register Offsets
#define MODER_OFFSET   0x00  // Mode register
#define OTYPER_OFFSET  0x04  // Output type register
#define PUPDR_OFFSET   0x0C  // Pull-up/pull-down register
#define IDR_OFFSET     0x10  // Input data register
#define ODR_OFFSET     0x14  // Output data register
#define AFRL_OFFSET    0x20  // Alternate function low register
#define AFRH_OFFSET    0x24  // Alternate function high register

// Register Access Macros
#define REG32(addr) (*(volatile uint32*)(addr))

// GPIO Port Index
#define PORT_TO_INDEX(port) ((port == GPIO_A) ? 0 : \
                            (port == GPIO_B) ? 1 : \
                            (port == GPIO_C) ? 2 : \
                            (port == GPIO_D) ? 3 : 0xFF)

// GPIO Base Address Array
extern const uint32 GPIO_BASE_ADDRESSES[4];

// Register access functions
volatile uint32* GET_GPIO_REG(uint8 PortName, uint32 offset);

#endif // GPIO_PRIVATE_H