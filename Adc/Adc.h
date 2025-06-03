/**
 * Adc.h - Smart Conveyor Monitoring & Control System
 */
#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

typedef enum {
    ADC_CHANNEL_0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7,
    ADC_CHANNEL_8,
    ADC_CHANNEL_9,
    ADC_CHANNEL_10,
    ADC_CHANNEL_11,
    ADC_CHANNEL_12,
    ADC_CHANNEL_13,
    ADC_CHANNEL_14,
    ADC_CHANNEL_15
} Adc_Channel;

void Adc_Init(void);
uint32_t Adc_GetStatus(void);
uint8_t Adc_SelfTest(void);
uint16_t Adc_ReadChannel(Adc_Channel channel);

#endif /* ADC_H_ */
