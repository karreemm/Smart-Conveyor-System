//
// Created by louai on 6/2/2025.
//

#ifndef PWM_DRIVER_PRIVATE_H
#define PWM_DRIVER_PRIVATE_H

#include <stdint.h>

// review and check the base addresses and offsets with the memory map base addresses

// Base addresses
#define RCC_BASE        0x40023800
#define GPIOA_BASE      0x40020000
#define TIM1_BASE       0x40010000
#define ADC1_BASE       0x40012000

// RCC registers
#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x44))

// GPIOA registers
#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRH      (*(volatile uint32_t *)(GPIOA_BASE + 0x24))

// TIM1 registers
#define TIM1_CR1        (*(volatile uint32_t *)(TIM1_BASE + 0x00))
#define TIM1_CCMR1      (*(volatile uint32_t *)(TIM1_BASE + 0x18))
#define TIM1_CCER       (*(volatile uint32_t *)(TIM1_BASE + 0x20))
#define TIM1_PSC        (*(volatile uint32_t *)(TIM1_BASE + 0x28))
#define TIM1_ARR        (*(volatile uint32_t *)(TIM1_BASE + 0x2C))
#define TIM1_CCR1       (*(volatile uint32_t *)(TIM1_BASE + 0x34))
#define TIM1_BDTR       (*(volatile uint32_t *)(TIM1_BASE + 0x44))

// TIM1 bit masks
#define TIM_CR1_CEN         (1 << 0)
#define TIM_CCMR1_OC1PE     (1 << 3)
#define TIM_CCER_CC1E       (1 << 0)
#define TIM_BDTR_MOE        (1 << 15)

// ADC1 registers
//#define ADC1_SR         (*(volatile uint32_t *)(ADC1_BASE + 0x00))
//#define ADC1_CR2        (*(volatile uint32_t *)(ADC1_BASE + 0x08))
//#define ADC1_SMPR2      (*(volatile uint32_t *)(ADC1_BASE + 0x10))
//#define ADC1_SQR3       (*(volatile uint32_t *)(ADC1_BASE + 0x34))
//#define ADC1_DR         (*(volatile uint32_t *)(ADC1_BASE + 0x4C))

// ADC1 bit masks
//#define ADC_CR2_ADON        (1 << 0)
//#define ADC_CR2_SWSTART     (1 << 30)
//#define ADC_SR_EOC          (1 << 1)

#endif //PWM_DRIVER_PRIVATE_H
