/*
 * ExtInt.c
 *
 * Created: 09.09.2014 13:29:13
 *  Author: majapo
 */ 
#include "ExtInt.h"



void ExtIntInit(void)
	{
	EICRB |= (1<<ISC41); //falling edge on INT4
	EIMSK |=(1<<INT4); //enable INT4
	//MCUCR|=(1<<ISC01);
//	GICR|=(1<<INT0);
	}
	
	
