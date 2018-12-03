
 /*
 * glcd.c
 *
 * Created: 13.10.2018 18:06:44
 *  Author: Daniel Miller
 */ 


 #include "glcd.h"

uint8_t glcd_y;
uint8_t glcd_x;
uint8_t screen_data[128][8];

 void glcd_init()
 {
	data_ddr = DATA_WRITE;
	controller_ddr |= E | RS | CS2 | CS1;

	uint8_t screen_count = SCREEN_WIDTH/SINGLE_CONTROLLER_SCREEN_WIDTH;

	for (uint8_t i=0; i<screen_count; i++)
	{
		glcd_enable_controller(i);
		glcd_command(DISPLAY_ON);
		glcd_command(DISPLAY_LINE_START(0));
		glcd_clear();
	}
 }

 void glcd_enable_controller(uint8_t controller_nr)
 {
	 if(controller_nr)
	 {
		 controller_port &= ~CS2;
		 controller_port |= CS1;
	 }
	 else
	 {
		 controller_port &= ~CS1;
		 controller_port |= CS2;
	 }
 }

 void glcd_command(uint8_t command)
 {
	data_ddr = DATA_WRITE;

	controller_port |= E;
	_delay_us(E_RISE_TIME);

	data_port = command;

	controller_port &= ~E;
	_delay_us(E_FALL_TIME+DATA_WRITE_TIME);
 }

 void glcd_clear()
 {
	 clear_screen_data();
	 glcd_command(SET_Y(0));

	 for (int i=0; i<SCREEN_HEIGHT/BITS_IN_BYTE; i++)
	 {
		 glcd_command(SET_X(i));
		 for (int j=0; j<SINGLE_CONTROLLER_SCREEN_WIDTH; j++)
		 {
			glcd_write_data(0);
		 }
	 }

	 glcd_command(SET_X(0));
 }

 void glcd_write_data(uint8_t byte)
 {
	controller_port |= RS;

	glcd_command(byte);

	screen_data[glcd_y][glcd_x] = byte;

	glcd_y++;
	glcd_y %= SINGLE_CONTROLLER_SCREEN_WIDTH;

	controller_port &= ~RS;
 }

 void glcd_set_cursor(uint8_t x, uint8_t y)
 {
	uint8_t row = y/BITS_IN_BYTE;
	uint8_t column = x % SINGLE_CONTROLLER_SCREEN_WIDTH;
	uint8_t controller = x/SINGLE_CONTROLLER_SCREEN_WIDTH;

	glcd_enable_controller(controller);

	glcd_command(SET_X(row));
	glcd_command(SET_Y(column));
 }

 void glcd_set_pixel(uint8_t x, uint8_t y)
 {
	uint8_t pixel = y%BITS_IN_BYTE;
	glcd_set_cursor(x,y);

	uint8_t page_state = screen_data[glcd_y][glcd_x] | 1 << pixel;

	glcd_write_data(page_state);
 }
 

void glcd_draw_single_screen(char* const graphic, uint8_t controller)
{
	glcd_enable_controller(controller);
	glcd_command(SET_Y(0));

	for (int i=0; i<SCREEN_HEIGHT/BITS_IN_BYTE; i++)
	{
		glcd_command(SET_X(i));

		for (int j=0; j<SINGLE_CONTROLLER_SCREEN_WIDTH; j++)
		{
			glcd_write_data(graphic[i*SINGLE_CONTROLLER_SCREEN_WIDTH+j]);
		}
	}
}

void glcd_draw(char* const graphic)
{
	glcd_command(SET_Y(0));

	for (int i=0; i<SCREEN_HEIGHT/BITS_IN_BYTE; i++)
	{
		glcd_command(SET_X(i));
		glcd_enable_controller(0);

		for (int j=0; j<SCREEN_WIDTH; j++)
		{
			if(j == SINGLE_CONTROLLER_SCREEN_WIDTH)
			{
				glcd_enable_controller(1);
			}
			glcd_write_data(graphic[i*SCREEN_WIDTH+j]);
		}
	}

	_delay_us(320);
}

void clear_screen_data()
{
	for(uint8_t i=0; i<SCREEN_WIDTH; i++)
	{
		for(uint8_t j=0; j<SCREEN_HEIGHT/BITS_IN_BYTE; j++)
		{
			screen_data[i][j] = 0;
		}
	}
}

void redraw_screen_data()
{
	for(uint8_t i=0; i<SCREEN_WIDTH; i++)
	{
		for(uint8_t j=0; j<SCREEN_HEIGHT/BITS_IN_BYTE; j++)
		{
			glcd_write_data(screen_data[i][j]);
		}
	}
}