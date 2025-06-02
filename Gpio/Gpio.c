/**
 * Gpio.c - Smart Conveyor Monitoring & Control System
 */

#include "Gpio.h"
#include "Gpio_Private.h"

// Array to store previous pin states for edge detection
static uint8 PrevPinStates[4][16] = {0};

void Gpio_Init(uint8 PortName, uint8 PinNumber, uint8 PinMode)
{
    // Check if number is valid
    if (PinNumber > 15) return;
    
    // Get the mode register
    volatile uint32* ModeReg = GET_MODER_REG(PortName);
    if (ModeReg == 0) return;
    
    // Clear
    *ModeReg &= ~(0x3 << (PinNumber * 2));
    
    // Set
    *ModeReg |= (PinMode << (PinNumber * 2));
    
    // Initialize state for edge detection
    uint8 portIndex = 0;
    if (PortName == GPIO_A) portIndex = 0;
    else if (PortName == GPIO_B) portIndex = 1;
    else if (PortName == GPIO_C) portIndex = 2;
    else if (PortName == GPIO_D) portIndex = 3;
    
    PrevPinStates[portIndex][PinNumber] = Gpio_ReadPin(PortName, PinNumber);
}


void Gpio_WritePin(uint8 PortName, uint8 PinNumber, uint8 Data)
{
    if (PinNumber > 15) return;
    
    volatile uint32* ODRReg = GET_ODR_REG(PortName);
    if (ODRReg == 0) return;
    
    if (Data == GPIO_HIGH)
    {
        *ODRReg |= (1 << PinNumber);  // Set
    }
    else
    {
        *ODRReg &= ~(1 << PinNumber); // Clear
    }
}

uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNumber)
{
    if (PinNumber > 15) return GPIO_LOW;
    
    volatile uint32* IDRReg = GET_IDR_REG(PortName);
    if (IDRReg == 0) return GPIO_LOW;
    
    // Read
    return ((*IDRReg >> PinNumber) & 0x1);
}

void Gpio_TogglePin(uint8 PortName, uint8 PinNumber)
{
    if (PinNumber > 15) return;
    
    volatile uint32* ODRReg = GET_ODR_REG(PortName);
    if (ODRReg == 0) return;
    
    *ODRReg ^= (1 << PinNumber); // toggle
}

uint8 Gpio_DetectEdge(uint8 PortName, uint8 PinNumber)
{
    if (PinNumber > 15) return GPIO_NO_EDGE;
    
    // Get port index
    uint8 portIndex = 0;
    if (PortName == GPIO_A) portIndex = 0;
    else if (PortName == GPIO_B) portIndex = 1;
    else if (PortName == GPIO_C) portIndex = 2;
    else if (PortName == GPIO_D) portIndex = 3;
    else return GPIO_NO_EDGE;
    
    // Read current state
    uint8 currentState = Gpio_ReadPin(PortName, PinNumber);
    uint8 previousState = PrevPinStates[portIndex][PinNumber];
    
    // Update previous state for next time
    PrevPinStates[portIndex][PinNumber] = currentState;
    
    // Check for edges
    if (previousState == GPIO_LOW && currentState == GPIO_HIGH)
    {
        return GPIO_RISING_EDGE;
    }
    else if (previousState == GPIO_HIGH && currentState == GPIO_LOW)
    {
        return GPIO_FALLING_EDGE;
    }
    
    return GPIO_NO_EDGE;
}