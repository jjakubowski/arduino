/*
 * SPI.h
 *
 * Created: 01.10.2014 12:17:34
 *  Author: milorads
 */
 
#ifndef SPI_H_
#define SPI_H_
#include <avr/io.h>

uint8_t SPIreceive(void);

void SPIinit(void);

void SPIsend(uint8_t Data);


void SelectSlave(void);
void DeselectSlave(void);
#endif