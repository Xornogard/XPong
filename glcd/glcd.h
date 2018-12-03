/*
 * glcd.h
 *
 * Created: 13.10.2018 18:05:58
 *  Author: Daniel Miller
 */ 


#ifndef GLCD_H_
#define GLCD_H_

#include "../defines.h"

#define BITS_IN_BYTE 8
#define SINGLE_CONTROLLER_SCREEN_WIDTH 64

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//////////////////////////////////////////////////////////////////////////
///		CONNECTION SETTINGS
//////////////////////////////////////////////////////////////////////////

#define controller_port PORTA
#define controller_ddr DDRA

#define data_port PORTC
#define data_ddr DDRC

#define E	(1 << 0)
#define RS	(1 << 1)
#define CS2 (1 << 2)
#define CS1 (1 << 3)

//////////////////////////////////////////////////////////////////////////
///		VARIABLES
//////////////////////////////////////////////////////////////////////////

extern uint8_t glcd_y;
extern uint8_t glcd_x;
extern uint8_t screen_data[SCREEN_WIDTH][SCREEN_HEIGHT/BITS_IN_BYTE];


//////////////////////////////////////////////////////////////////////////
///		COMMANDS
//////////////////////////////////////////////////////////////////////////

#define DISPLAY_ON	0x3F
#define DISPLAY_OFF 0x3E

#define DISPLAY_STATUS_BUSY 0x80

#define DATA_WRITE 0xFF

#define DISPLAY_LINE_START(data) 0xc0 | data

#define SET_Y(data) glcd_y = 0x40 | data
#define SET_X(data) glcd_x = 0xB8 | data

//////////////////////////////////////////////////////////////////////////
///		TIMIMING CONFIGURATION
//////////////////////////////////////////////////////////////////////////

#define E_RISE_TIME 5
#define E_FALL_TIME 5
#define DATA_WRITE_TIME 5


//////////////////////////////////////////////////////////////////////////
///		PROCEDURES
//////////////////////////////////////////////////////////////////////////

void glcd_init();
void glcd_clear();
void glcd_clear_all();

void glcd_enable_mirroring_controllers();
void glcd_enable_controller(uint8_t controller);

void glcd_command(uint8_t command);
void glcd_write_data(uint8_t byte);

void glcd_set_cursor(uint8_t x, uint8_t y);
void glcd_set_pixel(uint8_t x, uint8_t y);
void glcd_clear_pixel(uint8_t x, uint8_t y);

void glcd_draw_single_screen(char* graphic, uint8_t controller);

void clear_screen_data();

void redraw_screen_data();

void glcd_set_y(uint8_t y);
void glcd_set_x(uint8_t x);


#endif /* GLCD_H_ */