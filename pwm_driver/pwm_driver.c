//
//
// Created by louai on 6/1/2025
//

#include <stdint.h>
#include "pwm_driver_private.h"
#include "pwm_driver.h"
#include <stdbool.h>

#include "Adc.h"


void PWM_Init(void) {

    RCC_AHB1ENR |= (1 << 0);   // enable GPIOA
    RCC_APB2ENR |= (1 << 8);   // enable ADC1
    RCC_APB2ENR |= (1 << 0);   // enable TIM1

    // GPIOA_MODER |= (3U << (1 * 2)); // Set PA1 as analog (11)

    // Set PA8 in alternate function mode (10)
    GPIOA_MODER &= ~(3U << (8 * 2));
    GPIOA_MODER |=  (2U << (8 * 2));

    // Set PA8 alternate function to AF1 (TIM1_CH1 which gives the PWM signal)
    GPIOA_AFRH &= ~(0xF << (0 * 4)); // clear first
    GPIOA_AFRH |=  (0x1 << (0 * 4));  // then set to AF1

    // Configure ADC1
    // ADC1_SQR3 = 1;                  // Use channel 1 of the ADC (which is connected to PA1)
    // ADC1_SMPR2 |= (7U << 0);        // Max sampling time (set to 480 cycles)


    // Configure TIM1 to generate a 1 kHz PWM signal with adjustable duty cycle.  many peripherals such as timers, ADCs, cannot operate directly at the high frequency of the system clock
    TIM1_PSC = 16 - 1;              // Sets the prescaler to 15. This divides the system clock (16 MHz) by 16, resulting in a timer clock of 1 MHz.
    TIM1_ARR = 1000 - 1;            // Sets the auto-reload register to 999. This determines the PWM period. With a 1 MHz timer clock, the period is (999 + 1) / 1 MHz = 1 ms, giving a PWM frequency of 1 kHz.
    TIM1_CCR1 = 0;                // Sets the compare register for Channel 1 to 0. This means the initial duty cycle is 0% (no signal output).

    // Set PWM mode 1 on Channel 1
    TIM1_CCMR1 &= ~(7 << 4);        // clear first, then:
    TIM1_CCMR1 |= (6 << 4);         // set the Output Compare Mode (OC1M) bits to 110 (PWM Mode 1).
    TIM1_CCMR1 |= TIM_CCMR1_OC1PE;  // enable the Output Compare Preload feature which ensures that updates to the compare value (CCR1 value which we set in line 101) take effect only at the next timer update event, preventing glitches in the PWM signal.

    // Enable output on Channel 1
    TIM1_CCER |= TIM_CCER_CC1E; // This enables the output for Channel 1 of Timer 1. Without this, the PWM signal will not be sent to the corresponding pin (PA8 in this case).

    // Enable main output for  the advanced timer1
    TIM1_BDTR |= TIM_BDTR_MOE; // This enables the main output for advanced timers like Timer 1. It is required for advanced timers to allow any output on their channels. Without this, even if the channel is enabled, the signal will not be output.

    // Enable Timer
    TIM1_CR1 |= TIM_CR1_CEN; // This line enables Timer 1 by setting the CEN (Counter Enable) bit in the CR1 (Control Register 1). When this bit is set, the timer starts counting based on the configured prescaler and auto-reload values, allowing the PWM signal to be generated.

    // ADC1_CR2 |= ADC_CR2_ADON;
}

static bool adc_conversion_started = false;

void PWM_UpdateFromADC(void) {

    // if (!adc_conversion_started) {
    //     // Start ADC conversion
    //     ADC1_CR2 |= ADC_CR2_SWSTART;
    //     adc_conversion_started = true;
    // } else if (ADC1_SR & ADC_SR_EOC) {

        // Read ADC result
        uint16_t adc_val = Adc_ReadChannel(ADC_CHANNEL_1);
        // uint16_t adc_val = ADC1_DR;

        // Convert to percentage (0–100)
        uint8_t percent = ((adc_val) * 100) / 4095;

        // Update duty cycle
        TIM1_CCR1 = (percent * (TIM1_ARR + 1)) / 100;


        // Reset the flag
        // adc_conversion_started = false;
    // }


}
