/*
 * SPI.c
 *
 * Created: 01.10.2014 12:31:19
 *  Author: milorads
 */

#include "SPI.h"


#define CS_PORT PORTB
#define CS (1<<PB0)

#define SPI_DDR DDRB
#define MOSI (1<<PB2)
#define MISO (1<<PB3)
#define SCK (1<<PB1)


uint8_t SPIreceive(void){

	SPDR = 0xAA;			// a dummy byte
	while(!(SPSR&(1<<SPIF)));//wait for reception
	return SPDR;

}

void SPIinit(void){

	
	SPI_DDR |= SCK | CS | MOSI;				//MOSI, SCK is output, SS output
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	//SPI enable, Master, clk rate fclk/16
	//MSB transmitted first, SPI interrupt disabled, Sampling on the first clk rising edge, 

}


void DeselectSlave(void)
{
	
	CS_PORT |= CS;
}

void SelectSlave(void)
{
	
	CS_PORT &= ~CS;
}

void SPIsend(uint8_t Data) {

	SPDR = Data;				//start conversion
	while(!(SPSR&(1<<SPIF)));	//wait for transmission to complete 

}
