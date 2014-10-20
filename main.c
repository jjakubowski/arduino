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


can_message_t message_rx;
can_message_t message_tx;

uint8_t Done_flag;


void print_str(char *str);
void print_num(uint16_t num);


int main(void)
{
	DDRB|=(1<<PB7);

	uint8_t temp;
	int i;

	USART_Init(MY_UBRR);
	USART_Transmit(0x01);
	USART_Transmit(6+CanInit());
	USART_Transmit(0x02);
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


	CanSendMsg(&message_tx,0);
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

		//	PORTB^=(1<<PB7);
		//		USART_Transmit('H');
		//		USART_Transmit('e');
		//		USART_Transmit('l');
		//		USART_Transmit('l');
		//		USART_Transmit('o');
		//		USART_Transmit('\r');
		//		USART_Transmit('\n');
		_delay_ms(500);
		//		USART_Transmit(0x55);
		//		USART_Transmit(MCPstatus());
		//	print_str("Value -");
		//	print_num(global_status);


		if(Done_flag)
		{
			for(i=0;i<6;i++){
				PORTB^=(1<<PB7);
				_delay_ms(100);
			}
			print_str("\r\ndlugosc -");
			print_num(message_rx.length);
			print_str("\r\nid -");
			print_num(message_rx.id);
			print_str("\r\nd1 -");
			print_num(message_rx.data[0]);
			print_str("\r\nd2 -");
			print_num(message_rx.data[1]);
			print_str("\r\nd3 -");
			print_num(message_rx.data[2]);
			print_str("\r\nd4 -");
			print_num(message_rx.data[3]);
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
