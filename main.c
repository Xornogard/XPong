/*
 * LCD_TRY_1000.c
 *
 * Created: 13.10.2018 17:34:28
 * Author : Xornogard
 */ 

#include <avr/io.h>
#include "glcd/glcd.h"
#include "graphics/graphics.h"

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
		draw_rectangle(0,0,127,63);
		_delay_ms(1000);

    }
}

void draw_rectangle(uint8_t left_upper_corner_x, uint8_t left_upper_corner_y, uint8_t width, uint8_t height)
{
	uint8_t x = left_upper_corner_x;
	uint8_t y = left_upper_corner_y;

	for(; x < left_upper_corner_x + width; x++)
	{
		glcd_set_pixel(x,y);
		_delay_ms(DELAY);
	} x--;

	for(; y < left_upper_corner_y + height; y++)
	{
		glcd_set_pixel(x,y);
		_delay_ms(DELAY);
	} y--;

	for(; x > left_upper_corner_x; x--)
	{
		glcd_set_pixel(x,y);
		_delay_ms(DELAY);
	}

	for(; y > left_upper_corner_y; y--)
	{
		glcd_set_pixel(x,y);
		_delay_ms(DELAY);
	}
}