
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"
#include "can.h"
#include "Extint.h"
#include "mcp2515.h"
#include "mcp.h"
#include "spi.h"
#include <avr/interrupt.h>
#include "stdlib.h"
#include "pwm.h"


can_message_t message_rx;
can_message_t message_tx;

volatile uint8_t Done_flag;


void print_str(char *str);
void print_num(uint16_t num);




int main(void)
{
	DDRB|=(1<<PB7);

	uint8_t temp;
	int i;
	signed int X,Y;

	USART_Init(MY_UBRR);
	PWM_init();
	CanInit();
	
	sei();
	Done_flag=0;

	message_tx.data[0] =0x12;
	message_tx.data[1] =0x34;
	message_tx.data[2] =0x4a;
	message_tx.data[3] =0x65;
	message_tx.data[4] =0xaa;
	message_tx.data[5] =0x55;
	message_tx.data[6] =0xaa;
	message_tx.data[7] =0x55;

	message_tx.id= 0x0A;
	message_tx.length =4;


	
	//	_delay_ms(3000);
	//	USART_Transmit(MCPread(0x0E));
	//
	//	for(i=0;i<13;i++)
	//	{
	//	USART_Transmit(MCPread(0x50+i));
	//	USART_Transmit('\r');
	//	USART_Transmit('\n');
	//	}
	while(1){
		
		if(Done_flag == 1)
		{
		
			
			X=message_rx.data[0];
			Y=message_rx.data[1];
					
			print_str("\r\nX -");
			print_num(X);
			print_str("  Y -");
			print_num(Y);
			if(Y>0) PWM_increase(1);
			else if (Y<0) PWM_decrease(1);
			Done_flag =0;
			
			
			
		}
	}

}


void print_str(char *str)
{
	while(*str)
	{
		USART_Transmit(*str);
		str++;
	}
}

void print_num(uint16_t num)
{
	char buff[5];

	itoa(num,buff,16);
	print_str(buff);
}

ISR(INT4_vect)
{
	uint8_t status;

	status = MCPstatus();
	
	if(status & (1<<1)) CanReceiveMsg(&message_rx,1);
	else if(status & (1<<0)) CanReceiveMsg(&message_rx,0);
	Done_flag=1;
	PORTB^=(1<<PB7);
	//status = MCPstatus();
}
