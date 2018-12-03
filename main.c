/*
 * LCD_TRY_1000.c
 *
 * Created: 13.10.2018 17:34:28
 * Author : Xornogard
 */ 

#include <avr/io.h>
#include "glcd/glcd.h"
#include "graphics.h"

void port_test();

#define DELAY 50

int main(void)
{
	glcd_init();
	uint8_t actual_controller = 0;
	uint8_t should_clear = 0;
    while (1) 
    {
		glcd_draw_single_screen(K44_filled, 1);
		_delay_ms(500);

		glcd_draw_single_screen(K44_filled, 0);
		_delay_ms(500);

		glcd_clear_all();
		_delay_ms(500);

		draw_square();
		_delay_ms(1000);

    }
}

void draw_square()
{
	uint8_t square_start = 30;
	uint8_t square_size = 30;

	uint8_t y = square_start;

	uint8_t x = square_start;

	for(; x < square_start + square_size; x++)
	{
		glcd_set_pixel(x,y);
		_delay_ms(DELAY);
	}

	for(; y < square_start + square_size; y++)
	{
		glcd_set_pixel(x,y);
		_delay_ms(DELAY);
	}

	for(; x > square_start; x--)
	{
		glcd_set_pixel(x,y);
		_delay_ms(DELAY);
	}

	for(; y > square_start; y--)
	{
		glcd_set_pixel(x,y);
		_delay_ms(DELAY);
	}
}

