#include <avr/io.h>

#define PWM_NO_CLOCK 0
#define PWM_CLK_DIV_1 1
#define PWM_CLK_DIV_8 2
#define PWM_CLK_DIV_64 3
#define PWM_CLK_DIV_256 4
#define PWM_CLK_DIV_1024 5


void PWM_init(void);
void PWM_increase(uint8_t step);
void PWM_decrease(uint8_t step);