//
// Created by louai on 6/3/2025.
//

#ifndef EDGE_DETECTOR_PRIVATE_H
#define EDGE_DETECTOR_PRIVATE_H

#include "Gpio_Private.h"
#define RCC_BASE        0x40023800

#define GPIOA_MODER     *GET_GPIO_REG(GPIO_A , MODER_OFFSET)
#define GPIOA_IDR       *GET_GPIO_REG(GPIO_A , IDR_OFFSET)
#define GPIOA_PUPDR     *GET_GPIO_REG(GPIO_A , PUPDR_OFFSET)
#define GPIOA_ODR       *GET_GPIO_REG(GPIO_A , ODR_OFFSET)
#define GPIOA_OTYPER    *GET_GPIO_REG(GPIO_A , OTYPER_OFFSET)

// #define GPIOA_BASE      0x40020000
// #define GPIOA_MODER     (*(unsigned long *)(GPIOA_BASE + 0x00))
// #define GPIOA_IDR       (*(unsigned long *)(GPIOA_BASE + 0x10))
// #define GPIOA_PUPDR     (*(unsigned long *)(GPIOA_BASE + 0x0C))
// #define GPIOA_ODR       (*(unsigned long *)(GPIOA_BASE + 0x14))
// #define GPIOA_OTYPER    (*(unsigned long *)(GPIOA_BASE + 0x04))

#define  BUTTON_BIN            5
#define  LED_BIN               6


#endif //EDGE_DETECTOR_PRIVATE_H
