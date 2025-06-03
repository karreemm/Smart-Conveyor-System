/**
 * Adc.c - Smart Conveyor Monitoring & Control System
 */

#include "Adc.h"
#include "Adc_private.h"
#include "Gpio.h"

void Adc_Init(void) {
    // Enable clocks
    RCC_APB2ENR |= RCC_IOPAEN | RCC_ADC1EN;

    // Initialize PA0 as analog
    Gpio_Init(GPIO_A, GPIO_PIN_0, GPIO_ANALOG, GPIO_NO_PULL);

    // Power on ADC
    ADC1_CR2 |= ADC_CR2_ADON;

    // Small delay for ADC to stabilize
    for (volatile int i = 0; i < 1000; i++);

    // Start calibration
    ADC1_CR2 |= ADC_CR2_CAL;
    while (ADC1_CR2 & ADC_CR2_CAL);

    // Set sample time for channel 0 to maximum (239.5 cycles)
    ADC1_SMPR2 |= (0x07 << (3 * 0));  // 3 bits per channel
}

uint16_t Adc_ReadChannel(Adc_Channel channel) {
    // Set the channel in regular sequence register
    ADC1_SQR3 = channel;

    // Start conversion
    ADC1_CR2 |= ADC_CR2_SWSTART;

    // Wait for conversion complete
    while (!(ADC1_SR & ADC_SR_EOC));

    // Return ADC result
    return ADC1_DR;
}
