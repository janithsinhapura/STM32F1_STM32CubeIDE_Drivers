/*
 * adc.c
 *
 *  Created on: Nov 1, 2023
 *      Author: Janith Sinhapura
 */
#include "stm32f1xx.h"
#include "adc.h"

void ADC1_Single_Conv_Init(void) {
	//PA1 ADC12_IN1
	//set clock access to gpioa
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//Enable analog input mode
	GPIOA->CRL &= ~GPIO_CRL_MODE1;
	GPIOA->CRL &= ~GPIO_CRL_CNF1;

	//enable adc1 clock
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	//set the sequence channel 1 as 1st
	ADC1->SQR3 |= ADC_SQR3_SQ1_0;

	//set 1 conversions
	ADC1->SQR1 &= ~ADC_SQR1_L;

	//wakeup adc
	ADC1->CR2 |= ADC_CR2_ADON;

}

uint16_t ADC1_Single_Conv_Init_Read(void) {
	//need to enable 2nd time of the adc to start
	ADC1->CR2 |= ADC_CR2_ADON;
	//start conversion of regular channels
	ADC1->CR2 |= ADC_CR2_SWSTART;
	//wait until the conversion stop
	while (!(ADC1->SR & ADC_SR_EOC))
		;
	return ADC1->DR;
}

void ADC1_Continous_Conv_Init(void) {
	//PA1 ADC12_IN1
	//set clock access to gpioa
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//Enable analog input mode
	GPIOA->CRL &= ~GPIO_CRL_MODE1;
	GPIOA->CRL &= ~GPIO_CRL_CNF1;

	//enable adc1 clock
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	//set the sequence channel 1 as 1st
	ADC1->SQR3 |= ADC_SQR3_SQ1_0;

	//set 1 conversions
	ADC1->SQR1 &= ~ADC_SQR1_L;

	//wakeup adc
	ADC1->CR2 |= ADC_CR2_ADON;

	ADC1->CR2 |= ADC_CR2_CONT;

}

uint16_t ADC1_Continous_Conv_Init_Read(void) {
	//need to enable 2nd time of the adc to start


	ADC1->CR2 |= ADC_CR2_ADON;
	//start conversion of regular channels
	ADC1->CR2 |= ADC_CR2_SWSTART;
	//wait until the conversion stop
	while (!(ADC1->SR & ADC_SR_EOC))
		;
	return ADC1->DR;
}

