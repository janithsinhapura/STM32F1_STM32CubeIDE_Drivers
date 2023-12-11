#include "stm32f1xx.h"
#include "rcc.h"
#include "systick.h"
#include "uart.h"
#include "stdio.h"

char key ;

int main(void) {

	//set sysclock to 72MHZ
	HSE_PLL_SYS_CLK_MAX();
	//Enable PC13 LED
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= GPIO_CRH_MODE13;

	UART1_Init();
	GPIOC->ODR |= GPIO_ODR_ODR13;
	printf("Press 1 for LED ON and any other character to OFF\r\n");
	DelayMS(1000);
	while (1) {

		switch (UART1_Read_Char()) {
		case '1':
			GPIOC->ODR &= ~GPIO_ODR_ODR13;
			break;
		default:
			GPIOC->ODR |= GPIO_ODR_ODR13;
		}

	}
}

