/*
 * adc.h
 *
 *  Created on: Nov 1, 2023
 *      Author: Janith Sinhapura
 */

#ifndef ADC_H_
#define ADC_H_

void ADC1_Single_Conv_Init(void);
uint16_t ADC1_Single_Conv_Init_Read(void);

void ADC1_Continous_Conv_Init(void);
uint16_t ADC1_Continous_Conv_Init_Read(void);

#endif /* ADC_H_ */
