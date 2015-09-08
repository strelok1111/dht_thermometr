/*
 * display.h
 *
 *  Created on: 07 марта 2015 г.
 *      Author: strelok
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <avr/io.h>

#define PORT_0 PORTC
#define PORT_NUMBER_0 PC0

#define PORT_1 PORTC
#define PORT_NUMBER_1 PC1

#define PORT_2 PORTC
#define PORT_NUMBER_2 PC2

#define PORT_3 PORTC
#define PORT_NUMBER_3 PC3

#define PORT_SEGMENT PORTB

extern void display_tick(void);
extern void display_none(void);
extern void display_1(int);
extern void display_2(int);
extern void display_error(void);
extern void display_t(int);
extern void display_h(int);


#endif /* DISPLAY_H_ */
