/*
 * ssdisplay.h
 *
 * Created: 31.01.2019 12:58:46
 *  Author: Xornogard
 */ 


#ifndef SSDISPLAY_H_
#define SSDISPLAY_H_

#include <avr/io.h>
#define F_CPU 16e6
#include <util/delay.h>
#include <avr/interrupt.h>

//////////////////////////////////////////////////////////////////////////
///			CONFIGURATION
//////////////////////////////////////////////////////////////////////////
#define LED_SSD_NUMBER_DDR DDRB
#define LED_SSD_CONTROL_DDR DDRA

#define LED_SSD_NUMBER_PORT PORTB
#define LED_SSD_CONTROL_PORT PORTA

#define LED_SSD_1_PIN (1 << PA5)
#define LED_SSD_2_PIN (1 << PA4)

#define TCNT_VALUE 65456

//////////////////////////////////////////////////////////////////////////
///			VARIABLES & CONSTANTS
//////////////////////////////////////////////////////////////////////////
extern const uint8_t ssd_numbers[];
extern uint8_t left_number_to_show;
extern uint8_t right_number_to_show;

//////////////////////////////////////////////////////////////////////////
///			PROCEDURES
//////////////////////////////////////////////////////////////////////////
void ssdisplay_init();
void ssdisplay_set_left_number(uint8_t number);
void ssdisplay_set_right_number(uint8_t number);
#endif /* SSDISPLAY_H_ */