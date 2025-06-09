/**
 * Gpio.c - Smart Conveyor Monitoring & Control System
 */

#include "Gpio.h"
#include "Gpio_Private.h"

#ifndef STD_TYPES_H
typedef unsigned char uint8;
typedef unsigned int uint32;
typedef unsigned short uint16;
#endif

// Array to store previous pin states for edge detection
static uint8 PrevPinStates[4][16] = {0};

// GPIO Base Address Array
const uint32 GPIO_BASE_ADDRESSES[4] = {
    GPIOA_BASE,
    GPIOB_BASE,
    GPIOC_BASE,
    GPIOD_BASE
};

// get GPIO register pointer
volatile uint32* GET_GPIO_REG(uint8 PortName, uint32 offset)
{
    uint8 portIndex = PORT_TO_INDEX(PortName);
    if (portIndex == 0xFF) return 0;
    
    return (volatile uint32*)(GPIO_BASE_ADDRESSES[portIndex] + offset);
}

void Gpio_Init(uint8 PortName, uint8 PinNumber, uint8 PinMode, uint8 DefaultState)
{
    // Check if pin number and port are valid
    if (PinNumber > 15) return;
    uint8 portIndex = PORT_TO_INDEX(PortName);
    if (portIndex == 0xFF) return;

    // Enable GPIO port clock
    switch(PortName) {
        case GPIO_A: RCC_AHB1ENR |= RCC_GPIOA_EN; break;
        case GPIO_B: RCC_AHB1ENR |= RCC_GPIOB_EN; break;
        case GPIO_C: RCC_AHB1ENR |= RCC_GPIOC_EN; break;
        case GPIO_D: RCC_AHB1ENR |= RCC_GPIOD_EN; break;
        default: return;
    }

    // Small delay for clock to stabilize
    for(volatile int i = 0; i < 1000; i++);

    // Get register pointers
    volatile uint32* MODER_REG = GET_GPIO_REG(PortName, MODER_OFFSET);
    volatile uint32* PUPDR_REG = GET_GPIO_REG(PortName, PUPDR_OFFSET);
    volatile uint32* OTYPER_REG = GET_GPIO_REG(PortName, OTYPER_OFFSET);

    if (!MODER_REG || !PUPDR_REG || !OTYPER_REG) return;

    // Configure mode (2 bits per pin)
    *MODER_REG &= ~(0x03 << (PinNumber * 2));
    *MODER_REG |= (PinMode << (PinNumber * 2));

    if (PinMode == GPIO_INPUT) {
        // Configure pull-up/pull-down for input pins
        *PUPDR_REG &= ~(0x03 << (PinNumber * 2));
        *PUPDR_REG |= (DefaultState << (PinNumber * 2));
    } else if (PinMode == GPIO_OUTPUT) {
        // Configure output type for output pins
        if (DefaultState == GPIO_PUSH_PULL) {
            *OTYPER_REG &= ~(0x1 << PinNumber);  // Push-pull (clear bit)
        } else if (DefaultState == GPIO_OPEN_DRAIN) {
            *OTYPER_REG |= (0x1 << PinNumber);   // Open-drain (set bit)
        }

        // Set initial output state to LOW
        Gpio_WritePin(PortName, PinNumber, GPIO_LOW);
    }

    // Initialize edge detection state
    PrevPinStates[portIndex][PinNumber] = Gpio_ReadPin(PortName, PinNumber);
}

void Gpio_SetAF(uint8 PortName, uint8 PinNumber, uint8 AFNumber)
{
    if (PinNumber > 15 || AFNumber > 15) return;
    uint8 portIndex = PORT_TO_INDEX(PortName);
    if (portIndex == 0xFF) return;
    
    volatile uint32* AFR_REG;
    uint8 bitPosition;
    
    if (PinNumber <= 7) {
        // Use AFRL for pins 0-7
        AFR_REG = GET_GPIO_REG(PortName, AFRL_OFFSET);
        bitPosition = PinNumber * 4;
    } else {
        // Use AFRH for pins 8-15
        AFR_REG = GET_GPIO_REG(PortName, AFRH_OFFSET);
        bitPosition = (PinNumber - 8) * 4;
    }
    
    if (!AFR_REG) return;
    
    *AFR_REG &= ~(0xF << bitPosition);
    *AFR_REG |= (AFNumber << bitPosition);
}

void Gpio_WritePin(uint8 PortName, uint8 PinNumber, uint8 Data)
{
    if (PinNumber > 15) return;
    
    volatile uint32* ODR_REG = GET_GPIO_REG(PortName, ODR_OFFSET);
    if (!ODR_REG) return;
    
    if (Data == GPIO_HIGH) {
        *ODR_REG |= (1 << PinNumber);  // Set
    } else {
        *ODR_REG &= ~(1 << PinNumber); // Clear
    }
}

uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNumber)
{
    if (PinNumber > 15) return GPIO_LOW;
    
    volatile uint32* IDR_REG = GET_GPIO_REG(PortName, IDR_OFFSET);
    if (!IDR_REG) return GPIO_LOW;
    
    return ((*IDR_REG >> PinNumber) & 0x1);
}

void Gpio_TogglePin(uint8 PortName, uint8 PinNumber)
{
    if (PinNumber > 15) return;
    
    volatile uint32* ODR_REG = GET_GPIO_REG(PortName, ODR_OFFSET);
    if (!ODR_REG) return;
    
    *ODR_REG ^= (1 << PinNumber); // toggle
}

uint8 Gpio_DetectEdge(uint8 PortName, uint8 PinNumber)
{
    if (PinNumber > 15) return GPIO_NO_EDGE;
    
    // Get port index
    uint8 portIndex = PORT_TO_INDEX(PortName);
    if (portIndex == 0xFF) return GPIO_NO_EDGE;
    
    // Read current state
    uint8 currentState = Gpio_ReadPin(PortName, PinNumber);
    uint8 previousState = PrevPinStates[portIndex][PinNumber];
    
    // Update previous state for next time
    PrevPinStates[portIndex][PinNumber] = currentState;
    
    // Check for edges
    if (previousState == GPIO_LOW && currentState == GPIO_HIGH) {
        return GPIO_RISING_EDGE;
    } else if (previousState == GPIO_HIGH && currentState == GPIO_LOW) {
        return GPIO_FALLING_EDGE;
    }
    
    return GPIO_NO_EDGE;
}