//
// Created by Youssef Aboelela on 6/2/2025.
//

#include "timer.h"
#define  DETECTION_DISTANCE_CM 10 // Distance in cm for speed calculation

uint32 first_time_capture = 0;

void Timer_Init(uint8 port_name , uint8 pin_num , uint8 prescaler , uint8 counter_direction) {
    Rcc_Enable(RCC_TIM2);

    Gpio_Init(port_name, pin_num, GPIO_AF, GPIO_PUSH_PULL); // Initialize the pin as Alternate Function for TIM2
    Gpio_SetAF(port_name, pin_num, 1); // Set Alternate Function 1 for the specified pin (TIM2_CH1)

    TIM2_PSC &= ~(0xFFFF); // Clear the prescaler register
    TIM2_PSC |= (prescaler - 1); // Set the prescaler value

    TIM2_ARR = 0xFFFFFFFF; // Set the auto-reload value to maximum

    TIM2_CR1 &= ~(0x1 << 4); // Set the direction to up-counting
    TIM2_CR1 |= (counter_direction << 4); // Set the counter direction

    TIM2_CCMR1 &= ~(0xFF); // Clear the capture compare selection mode bits
    TIM2_CCMR1 |= (0x1 << 0); // Set the output compare mode to Input Capture Mode

    TIM2_CCER &= ~(0xFF); // Clear the output compare enable bit
    TIM2_CCER |= (0x1 << 0); // Enable the output compare

    TIM2_CCER &= ~(0x1 << 1); // Clear the output compare polarity bit and set it to rising edge

}

void Timer_Start(void) {
    TIM2_CR1 |= (0x1 << 0); // Enable the timer
}

void Timer_Stop(void) {
    TIM2_CR1 &= ~(0x1 << 0); // Disable the timer
}

uint32 Timer_Capture_Time_At_Edge() {
    if(TIM2_SR & (0x1 << 1)) { // Check if the update event flag is set
        uint32 captured_time = TIM2_CCR1; // Read the current counter value
        TIM2_SR &= ~(0x1 << 1); // Clear the update event flag
        return captured_time; // Return the captured time
    }
    return 100;
}


uint32 Timer_Calculate_Time() {
    uint32 elapsed_time = 0;
    uint32 current_time = Timer_Capture_Time_At_Edge(); // Capture the current time
    if (current_time == 100) {
        return 0; // If no valid capture, return 0
    }
    if (first_time_capture == 0) {
        first_time_capture = current_time; // Initialize the first time capture
        return 0; // Return 0 for the first call
    }
    if (current_time > first_time_capture) {
        elapsed_time = current_time - first_time_capture; // Normal case
    } else {
        elapsed_time =  (0xFFFFFFFF - first_time_capture) + current_time + 1; // Overflow case
    }
    first_time_capture = current_time; // Update the first time capture for the next call
    return  elapsed_time; // Return the elapsed time
}

uint32 Timer_Calculate_Speed_CM_Per_Sec(uint32 elapsed_time) {
    if (elapsed_time == 0) return 0;

    uint32 speed_cm_per_sec = (DETECTION_DISTANCE_CM * 1000000) / elapsed_time;

    return speed_cm_per_sec;
}