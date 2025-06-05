
#include <stdint.h>
#include "pwm_driver.h"
#include "edge_detector.h"

#define GPIOA_BASE     0x40020000
#define GPIOA_MODER    (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_ODR      (*(volatile uint32_t *)(GPIOA_BASE + 0x14))


int main(void) {
    // Initialize PWM (PA0 for ADC, PA8 for PWM output)
    PWM_Init();

    // Initialize edge detector on PA5
    EdgeDetector_Init();


    while (1) {
        // Continuously update PWM based on potentiometer
        PWM_UpdateFromADC();

        // Check if falling edge occurred (button press or IR sensor trigger)
        if (EdgeDetector_DetectedFallingEdge()) {
            // Toggle PA6 (LED)
            GPIOA_ODR ^= (1 << 6);
        }

    }
}
