//
// Created by Youssef Aboelela on 5/11/2025.
//

#ifndef EXTI_H
#define EXTI_H
#include "Gpio.h"

typedef struct {
    uint32 IMR;
    uint32 EMR;
    uint32 RTSR;
    uint32 FTSR;
    uint32 SWIER;
    uint32 PR;
} ExtiType;

#define EXTI_          ((ExtiType*)0x40013C00)

typedef struct {
    uint32  NVIC_ISER[8];
    uint32  NVIC_ICER[8];
} NVICType;

#define NVIC_          ((NVICType*)0xE000E100)

#define GPIO__A 0
#define GPIO__B 1
#define GPIO__C 2
#define GPIO__D 3
#define GPIO__E 4
#define GPIO__H 7

#define TriggerStateFalling 0
#define TriggerStateRising 1
#define TriggerStateBoth 2

static const uint8 GpioExtiMapper [8] = {0x0 , 0x1 , 0x2, 0x3, 0x4 , 0x5 , 0x6 , 0x7};

static const uint8 VectorTableExtiEnableMapper [7] = {6,7,8,9,10,23,40};

void Exti_Init(uint8 PortName , uint8 PinNum, uint8 TriggerState);
void Exti_Enable(uint8 PinNum);
void Exti_Disable(uint8 PinNum);

#endif //EXTI_H
