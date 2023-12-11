/*
 * uart.c
 *
 *  Created on: Oct 30, 2023
 *      Author: Janith Sinhapura
 */
#include "stm32f1xx.h"

void UART1_Init(void) {
	//uart1 is under apb2 bus
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	//uart1 TX-PA9
	//uart1	RX-PA10
	//Enable gpio pins for uart1 in apb2 bus
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	//enable gpio alternate funtions
	GPIOA->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_MODE10;
	GPIOA->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_1;

	//enable uart1
	USART1->CR1 |= USART_CR1_UE;

	//8 data bits
	USART1->CR1 &= ~USART_CR1_M;

	//2 stop bits
	USART1->CR2 |= USART_CR2_STOP_1;

	//set baud rate to 115200
	//mantissa is 39 = 0x27
	//fractional part is 0.625 ~ 0.6 = 0x06
	USART1->BRR = (0x27U << 4) | (0x06 << 0);

	//enable tx
	USART1->CR1 |= USART_CR1_TE;
}

void UART1_WriteChar(char data)
{
	USART1->DR = data;

	//check data is transmitted out from the data register
	while((USART1->SR & USART_SR_TXE)==0);
}

