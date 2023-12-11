/*
 * timer.c
 *
 *  Created on: Nov 3, 2023
 *      Author: Janith Sinhapura
 */
#include "stm32f1xx.h"
#include "timer.h"

void TIM2_1Hz_Overflow(void) {

	//apb1 runs in 72MHZ
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	//counter clock frquency set to 72000000/7200 = 10000MHz
	TIM2->PSC = 7200 - 1;

	//so timer2 counter takes 1 second to count to 10000
	TIM2->ARR = 10000;

	//set current counter value to zero
	TIM2->CNT = 0;

	//set to upcounting
	TIM2->CR1 &= ~TIM_CR1_DIR;

	//set UEV update enable
	TIM2->CR1 &= ~TIM_CR1_UDIS;

	//enable counter
	TIM2->CR1 |= TIM_CR1_CEN;

}


