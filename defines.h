/*
 * defines.h
 *
 * Created: 13.10.2018 18:01:47
 *  Author: Daniel Miller
 */ 


#ifndef DEFINES_H_
#define DEFINES_H_

#include <avr/io.h>
#define F_CPU 16e6
#include <util/delay.h>


#define BUZZER_DDR DDRA
#define BUZZER_PORT PORTA
#define BUZZER (1 << PA6)

#endif /* DEFINES_H_ */