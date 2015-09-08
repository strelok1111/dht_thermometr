#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "dht/dht.h"
#include "display/display.h"


int8_t temperature = 0;
int8_t humidity = 0;
int8_t display_only_t = 0;
int8_t display_only_h = 0;
int8_t error = 0;

int main (void){
	DDRB = 0xFF;
	DDRC = 0xFF;

	sei();
	TIMSK = 1<<TOIE0;

	TCCR0 |= (1 << CS01) | (1 << CS00);
	dht_gettemperaturehumidity(&temperature, &humidity);
	_delay_ms(1000);
    while (1){
    	if(dht_gettemperaturehumidity(&temperature, &humidity) == -1) error = 1;
    	else error = 0;
	    _delay_ms(3000);
    }
}
ISR (TIMER0_OVF_vect){
	TCNT0 += 180;
	if(error){
		display_error();
	}else if (display_only_t){
		display_t(3);
		display_1(temperature);
	}else if (display_only_h){
		display_h(3);
		display_1(humidity);
	}else{
		display_1(humidity);
		display_2(temperature);
	}
	display_tick();
}


