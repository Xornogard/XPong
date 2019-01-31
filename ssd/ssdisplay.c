/*
 * ssdisplay.c
 *
 * Created: 31.01.2019 12:58:34
 *  Author: Xornogard
 */ 
 

 #include "ssdisplay.h"

const uint8_t ssd_numbers[] = { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6 };

uint8_t left_number_to_show;
uint8_t right_number_to_show;

 void ssdisplay_init()
 {
	LED_SSD_NUMBER_DDR = 0xFF;
	LED_SSD_CONTROL_DDR |= LED_SSD_1_PIN;
	LED_SSD_CONTROL_DDR |= LED_SSD_2_PIN;

	TCNT1 = TCNT_VALUE;

	TCCR1A = 0x00;
	TCCR1B = (1<<CS10) | (1<<CS12);
	TIMSK = (1 << TOIE1);

	sei();
 }

void ssdisplay_set_left_number(uint8_t number)
{
	left_number_to_show = number;
}

void ssdisplay_set_right_number(uint8_t number)
{
	right_number_to_show = number;
}

 ISR (TIMER1_OVF_vect) 
 {
	static int8_t left_ssd = 0;

	left_ssd = !left_ssd;

	if(left_ssd)
	{
		LED_SSD_CONTROL_PORT |= LED_SSD_2_PIN;
		LED_SSD_CONTROL_PORT &= ~LED_SSD_1_PIN;
		LED_SSD_NUMBER_PORT = ~ssd_numbers[left_number_to_show % 10];
	}
	else
	{
		LED_SSD_CONTROL_PORT |= LED_SSD_1_PIN;
		LED_SSD_CONTROL_PORT &= ~LED_SSD_2_PIN;
		LED_SSD_NUMBER_PORT = ~ssd_numbers[right_number_to_show % 10];
	}

	TCNT1 = TCNT_VALUE;
 }