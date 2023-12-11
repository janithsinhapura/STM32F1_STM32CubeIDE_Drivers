#include "stm32f1xx.h"
#include "rcc.h"
#include "systick.h"
#include "uart.h"
#include "stdio.h"

int main(void) {

	int counter = 0;
	//set sysclock to 72MHZ
	HSE_PLL_SYS_CLK_MAX();
	//Enable PC13 LED
	RCC->APB2ENR |=RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= GPIO_CRH_MODE13;

	UART1_Init();
	DelayMS(1000);
	while (1) {
		counter++;
		printf("Counter : %d\r\n",counter);
		DelayMS(1000);
	}
}


