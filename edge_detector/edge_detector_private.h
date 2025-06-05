//
// Created by louai on 6/3/2025.
//

#ifndef EDGE_DETECTOR_PRIVATE_H
#define EDGE_DETECTOR_PRIVATE_H

#define RCC_BASE        0x40023800
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))

#define GPIOA_BASE      0x40020000
#define GPIOA_MODER     (*(unsigned long *)(GPIOA_BASE + 0x00))
#define GPIOA_IDR       (*(unsigned long *)(GPIOA_BASE + 0x10))
#define GPIOA_PUPDR     (*(unsigned long *)(GPIOA_BASE + 0x0C))
#define GPIOA_ODR       (*(unsigned long *)(GPIOA_BASE + 0x14))
#define GPIOA_OTYPER    (*(unsigned long *)(GPIOA_BASE + 0x04))

#define  BUTTON_BIN            5
#define  LED_BIN               6


#endif //EDGE_DETECTOR_PRIVATE_H
