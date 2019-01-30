
 /*
 * glcd.c
 *
 * Created: 13.10.2018 18:06:44
 *  Author: Daniel Miller
 */ 


 #include "glcd.h"

uint8_t glcd_y;
uint8_t glcd_x;
uint8_t enabled_controller;
uint8_t screen_data[SCREEN_WIDTH][SCREEN_HEIGHT/BITS_IN_BYTE];

 void glcd_init()
 {
	data_ddr = DATA_WRITE;
	controller_ddr |= E | RS | CS2 | CS1;

	uint8_t screen_count = SCREEN_WIDTH/SINGLE_CONTROLLER_SCREEN_WIDTH;

	glcd_enable_mirroring_controllers();
	glcd_command(DISPLAY_ON);
	glcd_command(DISPLAY_LINE_START(0));
	glcd_clear();
	glcd_enable_controller(0);
 }

 void glcd_enable_controller(uint8_t controller_nr)
 {
	 if(controller_nr)
	 {
		enabled_controller = 1;
		controller_port &= ~CS2;
		controller_port |= CS1;
	 }
	 else
	 {
		enabled_controller = 0;
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
	_delay_us(E_FALL_TIME);
 }

 void glcd_clear()
 {
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

 void glcd_clear_all()
 {
	glcd_enable_mirroring_controllers();
	glcd_clear();
	glcd_enable_controller(0);
	clear_screen_data();
 }

 void glcd_enable_mirroring_controllers()
 {
	controller_port &= ~(CS2 | CS1);
 }

 void glcd_write_data(uint8_t byte)
 {
	controller_port |= RS;

	glcd_command(byte);

	screen_data[glcd_y*(enabled_controller+1)][glcd_x] = byte;

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
	glcd_set_x(row);
	glcd_set_y(column);
 }

 void glcd_set_pixel(uint8_t x, uint8_t y)
 {
	uint8_t pixel = y%BITS_IN_BYTE;
	glcd_set_cursor(x,y);

	uint8_t page_state = screen_data[glcd_y*(1+enabled_controller)][glcd_x] | 1 << pixel;

	glcd_write_data(page_state);
 }

 void glcd_clear_pixel(uint8_t x, uint8_t y)
 {
	uint8_t pixel = y%BITS_IN_BYTE;
	glcd_set_cursor(x,y);

	uint8_t page_state = screen_data[glcd_y*(1+enabled_controller)][glcd_x] & ~(1 << pixel);

	glcd_write_data(page_state);
 }
 

void glcd_draw_single_screen(char* const graphic, uint8_t controller)
{
	glcd_enable_controller(controller);
	glcd_set_y(0);

	glcd_y = 0;
	glcd_x = 0;

	for (int i=0; i<SCREEN_HEIGHT/BITS_IN_BYTE; i++)
	{
		glcd_set_x(i);

		for (int j=0; j<SINGLE_CONTROLLER_SCREEN_WIDTH; j++)
		{
			glcd_write_data(graphic[i*SINGLE_CONTROLLER_SCREEN_WIDTH+j]);
		}
	}
}

void clear_screen_data()
{
	for (uint8_t i=0; i<SCREEN_WIDTH; i++)
	{
		for(uint8_t j = 0; j<SCREEN_HEIGHT/BITS_IN_BYTE; j++)
		{
			screen_data[i][j] = 0;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
////////COMMANDS
//////////////////////////////////////////////////////////////////////////

void glcd_set_y(uint8_t y)
{
	glcd_command(SET_Y(y));
	glcd_y = y;
}

void glcd_set_x(uint8_t x)
{
	glcd_command(SET_X(x));
	glcd_x = x;
}