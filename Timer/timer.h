//
// Created by Youssef Aboelela on 6/2/2025.
//

#ifndef TIMER_H
#define TIMER_H

#include "Gpio.h"
#include "Utils.h"
#include "Rcc.h"

#define TIM2_BASE_ADDR 0x40000000

#define TIM2_CR1 REG32(TIM2_BASE_ADDR + 0x00)

#define TIM2_SR REG32(TIM2_BASE_ADDR + 0x10)

#define TIM2_CCMR1 REG32(TIM2_BASE_ADDR + 0x18)

#define TIM2_CCER REG32(TIM2_BASE_ADDR + 0x20)

#define TIM2_CNT REG32(TIM2_BASE_ADDR + 0x24)

#define TIM2_PSC REG32(TIM2_BASE_ADDR + 0x28)

#define TIM2_ARR REG32(TIM2_BASE_ADDR + 0x2C)

#define TIM2_CCR1 REG32(TIM2_BASE_ADDR + 0x34)

#define CounterDirectionUp 0x0
#define CounterDirectionDown 0x1

void Timer_Init(uint8 port_name , uint8 pin_num ,  uint8 prescaler , uint8 counter_direction);

void Timer_Start(void);

void Timer_Stop(void);

uint32 Timer_Capture_Time_At_Edge(void);

uint32 Timer_Calculate_Time(void);

uint32 Timer_Calculate_Speed_CM_Per_Sec(uint32 elapsed_time);

#endif //TIMER_H
