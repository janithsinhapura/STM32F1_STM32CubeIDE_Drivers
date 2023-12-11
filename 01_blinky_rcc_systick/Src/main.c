#include "stm32f1xx.h"

void DelayMS(uint32_t delay);
void HSE_PLL_SYS_CLK_MAX(void);

volatile int counter = 0;

int main(void) {
	HSE_PLL_SYS_CLK_MAX();
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

	GPIOC->CRH |= GPIO_CRH_MODE13;
	counter = 2;
	while (1) {
		GPIOC->ODR ^= GPIO_ODR_ODR13;
		DelayMS(1000);
	}
}

void DelayMS(uint32_t delay) {
	SysTick->LOAD = 72000 - 1; //(8000000 / 1000) - 1;
	SysTick->VAL = 0; //set the current value of the systick;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; //set processor clock source and enable systick

	for (uint32_t i = 0; i < delay; i++) {
		while (((SysTick->CTRL) & SysTick_CTRL_COUNTFLAG_Msk) == 0)
			;
	}
	SysTick->CTRL = 0;
}

void HSE_PLL_SYS_CLK_MAX(void) {
	RCC->CR |= RCC_CR_HSEON;
	while ((RCC->CR & RCC_CR_HSERDY) == 0)
		;

	FLASH->ACR |=FLASH_ACR_LATENCY_2 |FLASH_ACR_PRFTBE;


	RCC->CFGR |= RCC_CFGR_PLLSRC;
	RCC->CFGR |= RCC_CFGR_PLLMULL9;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

	RCC->CR |= RCC_CR_PLLON;

	//RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	while ((RCC->CR & RCC_CR_PLLRDY) == 0)
		;
}
