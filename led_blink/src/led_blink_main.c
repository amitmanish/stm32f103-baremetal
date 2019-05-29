/*
 * led_blink_main.c
 *
 *  Created on: 19-May-2019
 *      Author: lucifer
 */

#include <stdint.h>
#include <stm32f10x.h>

// enum declaration for holding led on and led off states
typedef enum{
	led_on , led_off
} led_state;

// function to initialise leds
void init_led(void){
	RCC->APB2ENR |= 1<<4;     // enabled the portc clock
	GPIOC->CRH |= (1<<20 | 1<< 1);         // set gpioc as the output at 50hz
	GPIOC->CRH &= ~(1<<22 | 1<<23);         // set gpioc as push pull configuation

}

led_state led_hearbeat(led_state state)
{
	led_state next_state;

	switch(state)
	{
	case led_on:
		next_state = led_off;
		GPIOC->BSRR = GPIOC;
		break;

	case led_off:
		next_state = led_on;
		GPIOC->BSRR = (1<<(13+16));
		break;
	}
return next_state;
}


// main program starts here

int main(void)
{
led_state state = led_on;

uint32_t led_delay_count = 0;

init_led();

while(1)
{

state = led_hearbeat(state);
for(uint32_t i =0; i<65536; i++);
}
	return 0;
}
