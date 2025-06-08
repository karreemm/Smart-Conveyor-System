//
// Created by louai on 6/2/2025.
//

#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H

// Initializes PWM output on PA8 using TIM1
// and sets up ADC to read from PA0
void PWM_Init(void);

// Reads the ADC value from the potentiometer (PA0)
// and updates the PWM duty cycle on PA8
float PWM_UpdateFromADC(void);
void PWM_EmergencyTurnOffMotor(void);

#endif //PWM_DRIVER_H
