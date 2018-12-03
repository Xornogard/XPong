/*
 * xpong.c
 *
 * Created: 03.12.2018 19:11:16
 *  Author: Xornogard
 */ 

#include "xpong.h"
//////////////////////////////////////////////////////////////////////////
///		STRUCTURES
//////////////////////////////////////////////////////////////////////////

struct Ball {
	uint8_t pos_x;
	uint8_t pos_y;

	uint8_t speed_x;
	uint8_t speed_y;
};

struct Paddle {
	uint8_t size;
	uint8_t width;
};

//////////////////////////////////////////////////////////////////////////
///		VARIABLES
//////////////////////////////////////////////////////////////////////////

struct Ball ball;
struct Paddle left_player_paddle;
struct Paddle right_player_paddle;

//////////////////////////////////////////////////////////////////////////
///		PROCEDURES
//////////////////////////////////////////////////////////////////////////

void game_init() 
{
	glcd_init();
	game_reset();
}

void game_reset()
{
	ball.pos_x = SCREEN_WIDTH/2;
	ball.pos_y = SCREEN_HEIGHT/2;
	ball.speed_x = 2;
	ball.speed_y = 2;
}

void game_loop()
{
	game_clear_ball();
	game_update();
	game_draw_ball();
	game_draw_paddles();
}

void game_update()
{
	if(ball.pos_x <= 2 || ball.pos_x >= 126)
		ball.speed_x = -ball.speed_x;

	if(ball.pos_y <= 2 || ball.pos_y >= 62)
		ball.speed_y = -ball.speed_y;

	ball.pos_x += ball.speed_x;
	ball.pos_y += ball.speed_y;
}

void game_clear_ball()
{
	glcd_clear_pixel(ball.pos_x-1, ball.pos_y-1);
	glcd_clear_pixel(ball.pos_x-1, ball.pos_y);
	glcd_clear_pixel(ball.pos_x-1, ball.pos_y+1);

	glcd_clear_pixel(ball.pos_x, ball.pos_y-1);
	glcd_clear_pixel(ball.pos_x, ball.pos_y);
	glcd_clear_pixel(ball.pos_x, ball.pos_y+1);

	glcd_clear_pixel(ball.pos_x+1, ball.pos_y-1);
	glcd_clear_pixel(ball.pos_x+1, ball.pos_y);
	glcd_clear_pixel(ball.pos_x+1, ball.pos_y+1);
}

void game_draw_ball()
{
	glcd_set_pixel(ball.pos_x-1, ball.pos_y-1);
	glcd_set_pixel(ball.pos_x-1, ball.pos_y);
	glcd_set_pixel(ball.pos_x-1, ball.pos_y+1);

	glcd_set_pixel(ball.pos_x, ball.pos_y-1);
	glcd_set_pixel(ball.pos_x, ball.pos_y);
	glcd_set_pixel(ball.pos_x, ball.pos_y+1);

	glcd_set_pixel(ball.pos_x+1, ball.pos_y-1);
	glcd_set_pixel(ball.pos_x+1, ball.pos_y);
	glcd_set_pixel(ball.pos_x+1, ball.pos_y+1);
}

void game_draw_paddles()
{

}