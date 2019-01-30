/*
 * xpong.c
 *
 * Created: 03.12.2018 19:11:16
 *  Author: Xornogard
 */ 

#include "xpong.h"


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
	game_reset();

	glcd_init();
	game_draw_static_graphic();

	enc_init();
	enc_value = PADDLE_START_POSITION;
}

void game_reset()
{
	ball.pos_x = BALL_START_POSITION_X;
	ball.pos_y = BALL_START_POSITION_Y;
	ball.speed_x = 2;
	ball.speed_y = -2;

	left_player_paddle.position = PADDLE_START_POSITION;
	right_player_paddle.position = PADDLE_START_POSITION;
}

void game_loop()
{
	game_clear_ball();
	game_clear_paddles();
	game_update();
	game_draw_ball();
	game_draw_paddles();
}

void game_update()
{
	if(ball.pos_x <= LEFT_TABLE_HALF || ball.pos_x >= RIGHT_TABLE_HALF)
	{
		ball.speed_x = -ball.speed_x;
	}

	if(ball.pos_x > GAME_CENTER)
	{

		right_player_paddle.position = ball.pos_y;
		/*
		uint8_t ball_paddle_relative_position = right_player_paddle.position - ball.pos_y + 1;
		uint8_t center_difference_pos = ball_paddle_relative_position - right_player_paddle.position/2 + 1;

		if(center_difference_pos > 0 && right_player_paddle.position + PADDLE_SIZE < TABLE_HEIGHT)
		{
			right_player_paddle.position++;
		}
		else if(center_difference_pos < 0 && right_player_paddle.position > 0)
		{
			right_player_paddle.position--;
		}*/
	}

	int8_t paddle_position = enc_value;

	if(paddle_position+PADDLE_SIZE > SCREEN_HEIGHT)
	{
		paddle_position = SCREEN_HEIGHT - PADDLE_SIZE;
		enc_value = paddle_position;
	}
	else if(paddle_position < 0)
	{
		paddle_position = 0;
		enc_value = 0;
	}

	left_player_paddle.position = paddle_position;

	if(ball.pos_y <= 2 || ball.pos_y >= 62)
	{
		ball.speed_y = -ball.speed_y;
	}
		

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

void game_clear_paddles()
{
	for (uint8_t i=0; i<PADDLE_SIZE; i++)
	{
		for (uint8_t j=0; j<PADDLE_WIDTH; j++)
		{
			glcd_clear_pixel(LEFT_TABLE_HALF+j,left_player_paddle.previous_position+i);
			glcd_clear_pixel(RIGHT_TABLE_HALF-j,right_player_paddle.previous_position+i);
		}
	}
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
	for (uint8_t i=0; i<PADDLE_SIZE; i++)
	{
		for (uint8_t j=0; j<PADDLE_WIDTH; j++)
		{
			glcd_set_pixel(LEFT_TABLE_HALF+j,left_player_paddle.position+i);
			glcd_set_pixel(RIGHT_TABLE_HALF-j,right_player_paddle.position+i);
		}
	}

	left_player_paddle.previous_position = left_player_paddle.position;
	right_player_paddle.previous_position = right_player_paddle.position;
}

void game_draw_static_graphic()
{
	game_draw_borders();
}

void game_draw_borders()
{
	for (uint8_t i=0; i<TABLE_HEIGHT; i++)
	{
		glcd_set_pixel(LEFT_TABLE_HALF-2, i);
		glcd_set_pixel(RIGHT_TABLE_HALF+2, i);
	}
}