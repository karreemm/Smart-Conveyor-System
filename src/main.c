
#include <stdio.h>

#include "7Segment.h"
#include "Adc.h"
#include "edge_detector.h"
#include "edge_detector_private.h"
#include "RCC.h"
#include "Gpio.h"
#include "LCD.h"
#include "pwm_driver.h"
#include "Usart.h"
#include "../EXTI/Exti.h"
#include "../Timer/timer.h"


int main() {
    Rcc_Init();
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_GPIOB);
    Rcc_Enable(RCC_SYSCFG);
    Rcc_Enable(RCC_USART1);


    Timer_Init(GPIO_A, 0, 8, CounterDirectionUp); // Initialize Timer with prescaler 8 for 1ms ticks

    Timer_Start();

    Gpio_Init(GPIO_A , 4 , GPIO_INPUT  , GPIO_PULL_UP);

    Exti_Init(GPIO__A , 4 , TriggerStateFalling );

    Exti_Enable(4);

    // Initialize PWM (PA0 for ADC, PA8 for PWM output)
    PWM_Init();

    Adc_Init();

    // Initialize edge detector on PA5
    EdgeDetector_Init();
    LCD_init();
    delay_ms(10);
    LCD_clear();
    delay_ms(10);
    LCD_write_string("Smart Conveyor");
    delay_ms(10);


    while (1) {
        if (EdgeDetector_DetectedFallingEdge()) {
            // Toggle PA6 (LED)
            GPIOA_ODR ^= (1 << 6);
        }
        uint8 objects_detected = EdgeDetector_GetNumberOfObjectsDetected();
        LCD_clear();

        // Continuously update PWM based on potentiometer
        // PWM_UpdateFromADC();

        uint32 elapsed_time = Timer_Calculate_Time(); // Calculate the elapsed time
        uint32 speed_cm_per_sec = Timer_Calculate_Speed_CM_Per_Sec(elapsed_time);
        if(speed_cm_per_sec != 0 ) {
            LCD_write_string("Conveyor Speed : ");
            LCD_set_cursor(1, 0);
            LCD_write_number(speed_cm_per_sec);
            LCD_write_string("cm/sec");
            delay_ms(1);
            LCD_clear();
        }
        LCD_write_string("OBJ Detected: ");
        LCD_write_number(objects_detected);
        delay_ms(1);

    }
    return 0;
}


void EXTI4_IRQHandler() {
    Usart1_TransmitString("EXTI4 Interrupt Triggered\r\n");
    EXTI_->PR |= (1 << 4);
}
