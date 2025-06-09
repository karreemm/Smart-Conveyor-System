//
// Created by Youssef Aboelela on 5/11/2025.
//

#include "Exti.h"

#include <stm32f401xe.h>

void Exti_Init(uint8 PortName , uint8 PinNum, uint8 TriggerState) {
    // Select the Register Number and the index in the register
    uint8 RegisterNumber = PinNum / 4;
    uint8 RegisterIndex = PinNum % 4;
    uint8 Data = GpioExtiMapper[PortName];

    // Clear the External Interrput Configuration Register with the selected register number
    SYSCFG->EXTICR[RegisterNumber] &= ~(0x0F << (4 * RegisterIndex));

    // Write the External Interrput Configuration Register with the selected register number
    SYSCFG->EXTICR[RegisterNumber] |= (Data  << (4 * RegisterIndex));

    // Check the required trigger state
    switch (TriggerState) {
        case 0:
            EXTI_->RTSR &= ~(0x1 << PinNum);
            EXTI_->FTSR |= (0x1 << PinNum);
            break;
        case 1:
            EXTI_->FTSR &= ~(0x1 << PinNum);
            EXTI_->RTSR |= (0x1 << PinNum);
            break;
        case 2:
            EXTI_->RTSR |= (0x1 << PinNum);
            EXTI_->FTSR |= (0x1 << PinNum);
            break;
        default:
            break;
    }
}

void Exti_Enable(uint8 PinNum) {
    uint8 VectorTableIndex = 0;
    uint8 NvicIserRegisterNumber = 0;
    // Set the required pin in the IMR
    EXTI_->IMR |= (0x1 << PinNum);

    // Mapping the PinNum to the index of the VectorTableExtiEnableMapper array
    if(PinNum <= 4) {
        VectorTableIndex = PinNum;
    }
    else if (PinNum < 10) {
        VectorTableIndex = 5;
    }
    else {
        VectorTableIndex = 6;
    }

    // Selecting the NVIC_ISER register number depending on the PinNum / index
    if(VectorTableIndex == 6) {
        NvicIserRegisterNumber = 1;
    }

    NVIC_->NVIC_ISER[NvicIserRegisterNumber] |= (0x1 << (VectorTableExtiEnableMapper[VectorTableIndex]-(32 *NvicIserRegisterNumber )));
}

void Exti_Disable(uint8 PinNum) {
    uint8 VectorTableIndex;
    uint8 NvicIserRegisterNumber = 0;

    // Clear the required pin in the IMR
    EXTI_->IMR &= ~(0x1 << PinNum);

    // Mapping the PinNum to the index of the VectorTableExtiEnableMapper array
    if(PinNum < 4) {
        VectorTableIndex = PinNum;
    }
    else if (PinNum < 10) {
        VectorTableIndex = 5;
    }
    else {
        VectorTableIndex = 6;
    }

    // Selecting the NVIC_ISER register number depending on the PinNum / index
    if(VectorTableIndex == 6) {
        NvicIserRegisterNumber = 1;
    }

    NVIC_->NVIC_ICER[NvicIserRegisterNumber] |= (0x1 << (VectorTableExtiEnableMapper[VectorTableIndex]-(32 *NvicIserRegisterNumber )));
}
