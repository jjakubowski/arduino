#include "pwm.h"

/** initializes PWM with 7,5% duty cycle
*
*/
void PWM_init(void)
{
	// some of those values (which PWM output, the freq) are just RANDOMLY picked since we don't have many requirements
	DDRE|= (1<<PE5); 
	TCCR3A= 0b00001011;  // noninverting mode, fast pwm 
	TCCR3B = (0b11 << 3) | PWM_CLK_DIV_8 ;  // clk/8,   fast pwm  (TOP - OCR3A)
	OCR3A =  39999; // -> this value gives us 50 kHz
	OCR3C = 2999; // duty cycle 7.5%
}

void PWM_increase(uint8_t step)
{
	int temp;
	
	temp= OCR3C+step;
	
	if(temp<=4199)OCR3C =temp;
	
}


void PWM_decrease(uint8_t step)
{
	
		int temp;
		
		temp= OCR3C-step;
		
		if(temp>=1799) OCR3C =temp;
}