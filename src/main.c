
#include "7Segment.h"
#include "Adc.h"
#include "stm32f4xx.h"
#include "core_cm4.h"
#include "edge_detector.h"
#include "edge_detector_private.h"
#include "RCC.h"
#include "Gpio.h"
#include "LCD.h"
#include "pwm_driver.h"
#include "../EXTI/Exti.h"
#include "../Timer/timer.h"

uint8 emergency_stop = 0; // Flag to indicate emergency stop state
int main() {
    Rcc_Init();
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_GPIOB);
    Rcc_Enable(RCC_SYSCFG);
    Rcc_Enable(RCC_USART1);

    //Initialize Timer
    Timer_Init(GPIO_A, 0, 8, CounterDirectionUp); // Initialize Timer with prescaler 8 for 1ms ticks
    // Start the timer
    Timer_Start();

    // Initialize EXT4 interrupts for emergency stop
    Gpio_Init(GPIO_A , 4 , GPIO_INPUT  , GPIO_PULL_UP);
    Exti_Init(GPIO__A , 4 , TriggerStateFalling );
    Exti_Enable(4);

    // Initialize EXT1 interrupts for Reset
    Gpio_Init(GPIO_C , 1 , GPIO_INPUT  , GPIO_PULL_UP);
    Exti_Init(GPIO__C, 1, TriggerStateFalling);
    Exti_Enable(1);

    // Initialize PWM and ADC (PA1 for ADC, PA8 for PWM output)
    PWM_Init();
    Adc_Init();

    // Initialize edge detector on PA5
    EdgeDetector_Init();

    //Initialize LCD
    LCD_init();
    delay_ms(10);
    LCD_clear();
    delay_ms(10);
    LCD_write_string("Smart Conveyor");
    delay_ms(10);


    while (1) {
        if (emergency_stop == 1) {
            // If emergency stop is active, skip the rest of the loop
            continue;
        }
        if (EdgeDetector_DetectedFallingEdge()) {
            // Toggle PA6 (LED)
            GPIOA_ODR ^= (1 << 6);
        }
        // Read Number of objects detected
        uint8 objects_detected = EdgeDetector_GetNumberOfObjectsDetected();
        LCD_clear();

        // Continuously update PWM based on potentiometer
        uint8 motor_speed_percent = PWM_UpdateFromADC();

        // Calculate the elapsed time between two timer rising edges
        uint32 elapsed_time = Timer_Calculate_Time();

        // Calculate speed in cm/sec
        uint32 speed_cm_per_sec = Timer_Calculate_Speed_CM_Per_Sec(elapsed_time);
        // Display conveyor speed
        if(speed_cm_per_sec != 0 ) {
            LCD_write_string("Conveyor Speed : ");
            LCD_set_cursor(1, 0);
            LCD_write_number(speed_cm_per_sec);
            LCD_write_string("cm/sec");
            delay_ms(5);
            LCD_clear();
        }
        // Display motor speed percentage
        LCD_write_string("Motor Speed: ");
        LCD_set_cursor(1, 0);
        LCD_write_number(motor_speed_percent);
        LCD_write_string("%");
        delay_ms(5);

        LCD_clear();
        // Display number of objects detected on LCD
        LCD_write_string("OBJ Detected: ");
        LCD_write_number(objects_detected);
        delay_ms(5);

    }
    return 0;
}


void EXTI4_IRQHandler() {
    emergency_stop = 1; // Set emergency stop flag
    PWM_EmergencyTurnOffMotor(); // Turn off the motor immediately
    LCD_clear();
    delay_ms(2);
    LCD_write_string("EMERGENCY STOP");
    EXTI_->PR |= (1 << 4); // Clear pending bit for EXTI line 4

}

void EXTI1_IRQHandler() {
    emergency_stop = 0; // Clear emergency stop flag
    EXTI_->PR |= (1 << 1); // Clear pending bit for EXTI line 1
    NVIC_SystemReset(); // Reset the system to recover from emergency stop
}