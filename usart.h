#ifndef USART_H_
#define USART_H_


#define F_CPU 16000000
#define BAUD 19200

#define MY_UBRR (F_CPU/16)/BAUD-1

#include <avr/io.h>

void USART_Init(unsigned int baud );
void USART_Transmit(unsigned char data );
unsigned char USART_Receive(void );

#endif
