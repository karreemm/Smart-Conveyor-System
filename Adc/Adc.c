/**
 * Adc.c - FIXED VERSION for STM32F4
 */
#include "Adc.h"
#include "Adc_private.h"
#include "Gpio.h"

void Adc_Init(void) {
    // Enable clocks FIRST
    RCC_AHB1ENR |= RCC_GPIOAEN;  
    RCC_APB2ENR |= RCC_ADC1EN;  

    // Wait for clocks to stabilize
    for (volatile int i = 0; i < 10000; i++);

    // Configure PA0 as analog input PROPERLY
    Gpio_Init(GPIO_A, GPIO_PIN_0, GPIO_ANALOG, GPIO_NO_PULL);

    // delay after GPIO configuration
    for (volatile int i = 0; i < 5000; i++);

    // Reset ADC completely
    ADC1_CR2 = 0;  
    ADC1_CR1 = 0; 

    // Configure ADC Common Control Register
    ADC_CCR = 0;
    ADC_CCR |= (0x1 << 16);   // ADCPRE = 01 (divide by 4)

    // Configure ADC1 settings
    // Set resolution to 12-bit 
    ADC1_CR1 &= ~(0x3 << 24);  // RES = 00 for 12-bit

    // Set data alignment to right 
    ADC1_CR2 &= ~(1 << 11);    // ALIGN = 0 for right alignment

    // Disable continuous conversion mode for single conversions
    ADC1_CR2 &= ~(1 << 1);     // CONT = 0 for single conversion

    // Configure external trigger for regular channels 
    ADC1_CR2 &= ~(0xF << 24);  // Clear EXTSEL
    ADC1_CR2 &= ~(0x3 << 28);  // Clear EXTEN 

    // Set sampling time for channel 0 
    // Clear existing setting and set to 480 cycles for stable readings
    ADC1_SMPR2 &= ~(0x07 << (3 * 0));  // Clear SMP0
    ADC1_SMPR2 |= (0x07 << (3 * 0));   // Set SMP0 = 111 (480 cycles)

    // Configure sequence
    ADC1_SQR1 &= ~(0xF << 20);  // L = 0 (1 conversion)
    ADC1_SQR3 &= ~0x1F;         // Clear and set channel 0
    ADC1_SQR3 |= 0;             // Channel 0 in first position

    // Power on ADC
    ADC1_CR2 |= ADC_CR2_ADON;

    // Wait for ADC to stabilize
    for (volatile int i = 0; i < 50000; i++);

    // Perform calibration conversion 
    // Start first conversion to stabilize ADC
    ADC1_CR2 |= ADC_CR2_SWSTART;

    // Wait for this calibration conversion to complete
    volatile uint32_t timeout = 1000000;
    while (!(ADC1_SR & ADC_SR_EOC) && timeout > 0) {
        timeout--;
    }

    // Read and discard the calibration result
    volatile uint32_t dummy = ADC1_DR;
    (void)dummy;

    // Clear any remaining flags
    ADC1_SR = 0;
}

uint16_t Adc_ReadChannel(Adc_Channel channel) {
    // Validate channel
    if (channel > ADC_CHANNEL_15) {
        return 0;
    }

    if (channel != ADC_CHANNEL_0) {
        return 0;
    }

    // Clear any previous flags
    ADC1_SR &= ~ADC_SR_EOC;

    // Set the channel 
    ADC1_SQR3 &= ~0x1F;
    ADC1_SQR3 |= (channel & 0x1F);

    // Small delay for channel selection to settle
    for (volatile int i = 0; i < 100; i++);

    // Start conversion
    ADC1_CR2 |= ADC_CR2_SWSTART;

    // Wait for conversion to complete with proper timeout
    volatile uint32_t timeout = 1000000;
    while (!(ADC1_SR & ADC_SR_EOC) && timeout > 0) {
        timeout--;
    }

    // Check for timeout
    if (timeout == 0) {
        return 0xFFFF;  // Return obvious error value
    }

    // Read result
    uint16_t result = (uint16_t)(ADC1_DR & 0xFFF);

    // Clear EOC flag
    ADC1_SR &= ~ADC_SR_EOC;

    return result;
}

// debug function to check ADC status
uint32_t Adc_GetStatus(void) {
    return ADC1_SR;
}

// Function to check if ADC is properly initialized
uint8_t Adc_SelfTest(void) {
    // Check if ADC is powered on
    if (!(ADC1_CR2 & ADC_CR2_ADON)) {
        return 0;  // ADC not powered
    }

    // Check if clocks are enabled
    if (!(RCC_APB2ENR & RCC_ADC1EN)) {
        return 0;  // ADC clock not enabled
    }

    if (!(RCC_AHB1ENR & RCC_GPIOAEN)) {
        return 0;  // GPIO clock not enabled
    }

    return 1;  // Basic checks passed
}