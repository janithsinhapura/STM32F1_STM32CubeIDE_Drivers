#include "stm32f1xx.h"
#include "rcc.h"
#include "systick.h"
#include "uart.h"
#include "stdio.h"
#include "adc.h"

int16_t val;
int16_t voltage;

int main(void) {

	//set sysclock to 72MHZ
	HSE_PLL_SYS_CLK_MAX();
	//Enable PC13 LED
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= GPIO_CRH_MODE13;
	ADC1_Init();
	UART1_Init();
	GPIOC->ODR |= GPIO_ODR_ODR13;
	printf("ADC Testing\r\n");

	while (1) {

		val = ADC1_Read();
		//volateg step size = 3.3v/4096
		//voltage = (3.3 / 4096.0) *val;
		printf("Pot Value : %d\r\n",val);
		DelayMS(100);
	}
}

