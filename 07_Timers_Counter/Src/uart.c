/*
 * uart.c
 *
 *  Created on: Oct 30, 2023
 *      Author: Janith Sinhapura
 */
#include "stm32f1xx.h"
#include "stdio.h"

void UART1_Init(void) {
	//uart1 is under apb2 bus
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	//uart1 TX-PA9
	//uart1	RX-PA10
	//Enable gpio pins for uart1 in apb2 bus
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	//enable gpio alternate funtions
	GPIOA->CRH |= GPIO_CRH_MODE9 ;
	GPIOA->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_0;

	//enable uart1
	USART1->CR1 |= USART_CR1_UE;

	//8 data bits
	USART1->CR1 &= ~USART_CR1_M;

	//1 stop bits
	USART1->CR2 &=~USART_CR2_STOP;

	//set baud rate to 115200
	//mantissa is 39 = 0x27
	//fractional part is 0.0625 ~ 0.06 = 0x06
	USART1->BRR = (0x27U << 4) | (0x6<< 0);

	//enable tx
	USART1->CR1 |= USART_CR1_TE;

	//enable rx
	USART1->CR1 |= USART_CR1_RE;


}

void UART1_Write_Char(char data)
{
	//check data is transmitted out from the data register
	while((USART1->SR & USART_SR_TXE)==0);
	USART1->DR = data;


}

char UART1_Read_Char(void){
	while(!(USART1->SR & USART_SR_RXNE));
	return USART1->DR;
}

char __io_putchar(char ch){
	UART1_Write_Char(ch);
	return ch;
}
