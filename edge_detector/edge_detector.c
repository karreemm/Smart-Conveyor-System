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
    // Enable GPIOA Pin 5 for input (button)
    Gpio_Init(GPIO_A , GPIO_PIN_5 , GPIO_INPUT, GPIO_PULL_UP);

    // Enable GPIOA Pin 6 for output (LED)
    Gpio_Init(GPIO_A , GPIO_PIN_6 , GPIO_OUTPUT, GPIO_PUSH_PULL);

}


uint8_t EdgeDetector_DetectedFallingEdge(void) {
    // Read the current state of the button (PA5)
    uint8 detected_edge = Gpio_DetectEdge(GPIO_A , GPIO_PIN_5);

    if (detected_edge == GPIO_FALLING_EDGE) {
        number_of_edges++;  // Increment edge count
        return 1;  // Falling edge detected
    }
    return 0;  // No falling edge detected

}

uint8_t EdgeDetector_GetNumberOfObjectsDetected(void) {

    return number_of_edges;  // Return the count of edges detected

}






