#include "stm32f1xx.h"
#include "systick.h"


#define CORE_CLOCK_FREQ 72000000

void DelayMS(uint32_t delay)
{
	SysTick->LOAD = (CORE_CLOCK_FREQ/1000) - 1;
	SysTick->VAL = 0; //set the current value of the systick;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk ; //set processor clock source and enable systick
	
	for(uint32_t i =0;i<delay;i++)
	{
		while(((SysTick->CTRL)&SysTick_CTRL_COUNTFLAG_Msk) == 0);
	}
	SysTick->CTRL = 0;
}
