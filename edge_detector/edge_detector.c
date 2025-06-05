//
// Edge Detector - Detects falling edges from an IR sensor (on PA5)
// Created by louai
//

#include "edge_detector_private.h"
#include <stdint.h>

// tracking button state/presses
unsigned char previous_button_state = 1;  // unpressed at start
unsigned char number_of_edges = 0;  // count of edges detected

void EdgeDetector_Init(void) {
    RCC_AHB1ENR |= (0x1); // enable GPIO A

    // button pin
    unsigned char button_pin_pull = 0x1; // internal pull-up

    GPIOA_MODER &= ~(0x3 << (BUTTON_BIN * 2)); // Clear to set as input mode (= 00)

    GPIOA_PUPDR &= ~(0x3 << (BUTTON_BIN * 2)); // clear
    GPIOA_PUPDR |=  (button_pin_pull << (BUTTON_BIN * 2)); // set pull-up

    // led pins
    unsigned char led_pin_mode = 0x1; // output mode

    // Set LED_BIN mode to 01 (output)
    GPIOA_MODER &= ~(0x3 << (LED_BIN * 2));  // Clear bits
    GPIOA_MODER |=  (led_pin_mode << (LED_BIN * 2));  // Set output mode

    // Set LED_BIN type to 0 (push-pull)
    GPIOA_OTYPER &= ~(1 << LED_BIN);
}

// This function checks if a falling edge occurred on PA5
// A falling edge means the signal went from HIGH to LOW
// We use this to count how many objects have passed
uint8_t EdgeDetector_DetectedFallingEdge(void) {
    unsigned char button_state_1;
    unsigned char button_state_2;

    // Read first state
    button_state_1 = (GPIOA_IDR >> BUTTON_BIN) & 0x1;

    // Delay ~30ms
    for (volatile int i = 0; i < 100000; i++) {

    }

    // Read second state
    button_state_2 = (GPIOA_IDR >> BUTTON_BIN) & 0x1;

    // If button is stable and was just pressed (falling edge)
    if ((button_state_1 == button_state_2) && button_state_1 == 0 && previous_button_state == 1) {

        // Save current state for next time
        previous_button_state = button_state_1;
        number_of_edges++;  // Increment edge count

        return 1;
    }

    previous_button_state = button_state_1;  // Update state
    return 0;  // No falling edge

}

uint8_t EdgeDetector_GetNumberOfObjectsDetected(void) {

    return number_of_edges;  // Return the count of edges detected

}






