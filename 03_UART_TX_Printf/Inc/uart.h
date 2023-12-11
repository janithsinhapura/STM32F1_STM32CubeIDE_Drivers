/*
 * uart.h
 *
 *  Created on: Oct 30, 2023
 *      Author: Janith Sinhapura
 */

#ifndef UART_H_
#define UART_H_

int __io_putchar(char ch);
void UART1_Init(void);
void UART1_Write_Char(char data);

#endif /* UART_H_ */
