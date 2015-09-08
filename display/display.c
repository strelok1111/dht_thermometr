/*
 * display.c
 *
 *  Created on: 07 марта 2015 г.
 *      Author: strelok
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "display.h"

int display_array[4] = {0xFF,0xFF,0xFF,0xFF};
int current_display_number = 0;
void display_tick(void){
	PORT_0 &= ~_BV(PORT_NUMBER_0);
	PORT_1 &= ~_BV(PORT_NUMBER_1);
	PORT_2 &= ~_BV(PORT_NUMBER_2);
	PORT_3 &= ~_BV(PORT_NUMBER_3);
	PORT_SEGMENT = 0xFF;
	switch(current_display_number){
		case 0:
			PORT_0 |= _BV(PORT_NUMBER_0);
			PORT_1 &= ~_BV(PORT_NUMBER_1);
			PORT_2 &= ~_BV(PORT_NUMBER_2);
			PORT_3 &= ~_BV(PORT_NUMBER_3);
			break;
		case 1:
			PORT_1 |= _BV(PORT_NUMBER_1);
			PORT_0 &= ~_BV(PORT_NUMBER_0);
			PORT_2 &= ~_BV(PORT_NUMBER_2);
			PORT_3 &= ~_BV(PORT_NUMBER_3);
			break;
		case 2:
			PORT_2 |= _BV(PORT_NUMBER_2);
			PORT_0 &= ~_BV(PORT_NUMBER_0);
			PORT_1 &= ~_BV(PORT_NUMBER_1);
			PORT_3 &= ~_BV(PORT_NUMBER_3);
			break;
		case 3:
		    PORT_3 |= _BV(PORT_NUMBER_3);
		    PORT_0 &= ~_BV(PORT_NUMBER_0);
			PORT_1 &= ~_BV(PORT_NUMBER_1);
			PORT_2 &= ~_BV(PORT_NUMBER_2);
		    break;
	}
	PORT_SEGMENT = display_array[current_display_number];
	current_display_number++;
	if(current_display_number == 4) current_display_number = 0;
}
int get_port_mask(int d){

	if(d == 0){
		return 0b11000000;
	}else if(d == 1){
		return 0b11111001;
	}else if(d == 2){
		return 0b10100100;
	}else if(d == 3){
		return 0b10110000;
	}else if(d == 4){
		return 0b10011001;
	}else if(d == 5){
		return 0b10010010;
	}else if(d == 6){
		return 0b10000010;
	}else if(d == 7){
		return 0b11111000;
	}else if(d == 8){
		return 0b10000000;
	}else if(d == 9){
		return 0b10010000;
	}
	return 0xFF;
}
void display_none(void){
	display_array[0] = 0xFF;
	display_array[1] = 0xFF;
	display_array[2] = 0xFF;
	display_array[3] = 0xFF;
}
void display_1(int d){
	int has_second = d / 10 > 0;
	display_array[0] = get_port_mask(d % 10);
	if(has_second){
		display_array[1] = get_port_mask(d / 10);
	}else{
		display_array[1] = 0xFF;
	}
}
void display_2(int d){
	int has_second = d / 10 > 0;
	display_array[2] = get_port_mask(d % 10);
	if(has_second){
		display_array[3] = get_port_mask(d / 10);
	}else{
		display_array[3] = 0xFF;
	}
}
void display_error(void){
	display_array[3] = 0b00000110;
	display_array[2] = 0b00101111;
	display_array[1] = 0b00101111;
	display_array[0] = 0b00100011;
}
void display_t(int pos){
	display_array[pos] = 0b01000111;
}
void display_h(int pos){
	display_array[pos] = 0b00001001;
}
void clear(int pos){
	display_array[pos] = 0;
}

