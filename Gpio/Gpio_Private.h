/**
 * Adc_Private.h - Smart Conveyor Monitoring & Control System
 */
#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#include <stdint.h>
#include "Adc.h"  

// RCC base and registers
#define RCC_BASE        0x40023800
#define RCC_AHB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define RCC_APB2ENR     (*(volatile uint32_t*)(RCC_BASE + 0x44))

// Enable bits
#define RCC_GPIOAEN     (1 << 0)    // GPIOA enable
#define RCC_GPIOBEN     (1 << 1)    // GPIOB enable
#define RCC_ADC1EN      (1 << 8)    // ADC1 enable

// GPIO base addresses
#define GPIOA_BASE      0x40020000
#define GPIOB_BASE      0x40020400

// GPIO registers
#define GPIOA_MODER     (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOB_MODER     (*(volatile uint32_t*)(GPIOB_BASE + 0x00))
#define GPIOB_ODR       (*(volatile uint32_t*)(GPIOB_BASE + 0x14))

// ADC1 base and registers
#define ADC1_BASE       0x40012000
#define ADC1_SR         (*(volatile uint32_t*)(ADC1_BASE + 0x00))
#define ADC1_CR1        (*(volatile uint32_t*)(ADC1_BASE + 0x04))
#define ADC1_CR2        (*(volatile uint32_t*)(ADC1_BASE + 0x08))
#define ADC1_SMPR2      (*(volatile uint32_t*)(ADC1_BASE + 0x10))
#define ADC1_SQR1       (*(volatile uint32_t*)(ADC1_BASE + 0x2C))
#define ADC1_SQR3       (*(volatile uint32_t*)(ADC1_BASE + 0x34))
#define ADC1_DR         (*(volatile uint32_t*)(ADC1_BASE + 0x4C))

// ADC Common Control Register
#define ADC_CCR         (*(volatile uint32_t*)(0x40012300 + 0x04))

// Bit definitions
#define ADC_CR2_ADON    (1 << 0)
#define ADC_CR2_SWSTART (1 << 30)   
#define ADC_SR_EOC      (1 << 1)

// ADC Channel value definitions
#define ADC_CHANNEL_0_VAL   0
#define ADC_CHANNEL_1_VAL   1
#define ADC_CHANNEL_2_VAL   2
#define ADC_CHANNEL_3_VAL   3
#define ADC_CHANNEL_4_VAL   4
#define ADC_CHANNEL_5_VAL   5
#define ADC_CHANNEL_6_VAL   6
#define ADC_CHANNEL_7_VAL   7
#define ADC_CHANNEL_8_VAL   8
#define ADC_CHANNEL_9_VAL   9
#define ADC_CHANNEL_10_VAL  10
#define ADC_CHANNEL_11_VAL  11
#define ADC_CHANNEL_12_VAL  12
#define ADC_CHANNEL_13_VAL  13
#define ADC_CHANNEL_14_VAL  14
#define ADC_CHANNEL_15_VAL  15

#endif /* ADC_PRIVATE_H_ */