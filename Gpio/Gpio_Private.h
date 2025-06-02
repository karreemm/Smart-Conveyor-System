/**
 * Gpio_Private.h - Smart Conveyor Monitoring & Control System
 */

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

// GPIO Base Addresses for STM32F4xx
#define GPIOA_BASE    0x40020000
#define GPIOB_BASE    0x40020400
#define GPIOC_BASE    0x40020800
#define GPIOD_BASE    0x40020C00

// Register Offsets
#define MODER_OFFSET   0x00  // Mode register
#define IDR_OFFSET     0x10  // Input data register
#define ODR_OFFSET     0x14  // Output data register

// Register Access Macros
#define REG32(addr) (*(volatile uint32*)(addr))

// GPIO Registers for each port
#define GPIOA_MODER   REG32(GPIOA_BASE + MODER_OFFSET)
#define GPIOA_IDR     REG32(GPIOA_BASE + IDR_OFFSET)
#define GPIOA_ODR     REG32(GPIOA_BASE + ODR_OFFSET)

#define GPIOB_MODER   REG32(GPIOB_BASE + MODER_OFFSET)
#define GPIOB_IDR     REG32(GPIOB_BASE + IDR_OFFSET)
#define GPIOB_ODR     REG32(GPIOB_BASE + ODR_OFFSET)

#define GPIOC_MODER   REG32(GPIOC_BASE + MODER_OFFSET)
#define GPIOC_IDR     REG32(GPIOC_BASE + IDR_OFFSET)
#define GPIOC_ODR     REG32(GPIOC_BASE + ODR_OFFSET)

#define GPIOD_MODER   REG32(GPIOD_BASE + MODER_OFFSET)
#define GPIOD_IDR     REG32(GPIOD_BASE + IDR_OFFSET)
#define GPIOD_ODR     REG32(GPIOD_BASE + ODR_OFFSET)

// Macros to get registers based on port
#define GET_MODER_REG(port)  ((port == GPIO_A) ? &GPIOA_MODER : \
                              (port == GPIO_B) ? &GPIOB_MODER : \
                              (port == GPIO_C) ? &GPIOC_MODER : \
                              (port == GPIO_D) ? &GPIOD_MODER : 0)

#define GET_IDR_REG(port)    ((port == GPIO_A) ? &GPIOA_IDR : \
                              (port == GPIO_B) ? &GPIOB_IDR : \
                              (port == GPIO_C) ? &GPIOC_IDR : \
                              (port == GPIO_D) ? &GPIOD_IDR : 0)

#define GET_ODR_REG(port)    ((port == GPIO_A) ? &GPIOA_ODR : \
                              (port == GPIO_B) ? &GPIOB_ODR : \
                              (port == GPIO_C) ? &GPIOC_ODR : \
                              (port == GPIO_D) ? &GPIOD_ODR : 0)

#endif // GPIO_PRIVATE_H