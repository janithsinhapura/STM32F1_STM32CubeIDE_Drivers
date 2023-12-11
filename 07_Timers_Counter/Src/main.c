#include "stm32f1xx.h"
#include "rcc.h"
#include "systick.h"
#include "uart.h"
#include "stdio.h"
#include "timer.h"

////////////////////////////////////////////////////////////////////////
///toggle the led in pin PC13 at 1 second when the counter overflows////
////////////////////////////////////////////////////////////////////////


char key;
int16_t time = 0;

int main(void) {

	//set sysclock to 72MHZ
	HSE_PLL_SYS_CLK_MAX();
	//Enable PC13 LED
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= GPIO_CRH_MODE13;

	UART1_Init();
	GPIOC->ODR |= GPIO_ODR_ODR13;
	TIM2_1Hz_Overflow();

	while (1) {
		while (!(TIM2->SR & TIM_SR_UIF));
			; //wait until counter overflow flag occurs
		TIM2->SR &= ~ TIM_SR_UIF; //reset counter overflow update flag
		GPIOC->ODR ^= GPIO_ODR_ODR13;
		time++;
		printf("time : %d (s)\r\n", time);


	}

}
