/**
 * Adc_Private.h - Smart Conveyor Monitoring & Control System
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#include <stdint.h>

// RCC base and registers
#define RCC_BASE        0x40021000
#define RCC_APB2ENR     (*(volatile uint32_t*)(RCC_BASE + 0x18))

// Enable bits
#define RCC_IOPAEN      (1 << 2)
#define RCC_ADC1EN      (1 << 9)

// ADC1 base and registers
#define ADC1_BASE       0x40012400
#define ADC1_SR         (*(volatile uint32_t*)(ADC1_BASE + 0x00))
#define ADC1_CR1        (*(volatile uint32_t*)(ADC1_BASE + 0x04))
#define ADC1_CR2        (*(volatile uint32_t*)(ADC1_BASE + 0x08))
#define ADC1_SMPR2      (*(volatile uint32_t*)(ADC1_BASE + 0x10))
#define ADC1_SQR3       (*(volatile uint32_t*)(ADC1_BASE + 0x34))
#define ADC1_DR         (*(volatile uint32_t*)(ADC1_BASE + 0x4C))

// Bit definitions
#define ADC_CR2_ADON    (1 << 0)
#define ADC_CR2_CAL     (1 << 2)
#define ADC_CR2_SWSTART (1 << 22)
#define ADC_SR_EOC      (1 << 1)

#endif /* ADC_PRIVATE_H_ */
