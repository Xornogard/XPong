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

uint8_t is_ball_reflected = 0;
uint8_t is_left_player_connected = 0;
uint8_t is_right_player_connected = 0;

//////////////////////////////////////////////////////////////////////////
///		PROCEDURES
//////////////////////////////////////////////////////////////////////////

void game_init() 
{
	game_reset(BALL_START_SPEED_X);
	glcd_init();
	game_draw_static_graphic();

	enc_init();
	game_detect_controllers();
	enc_1_value = PADDLE_START_POSITION;
	enc_2_value = PADDLE_START_POSITION;
}

void game_detect_controllers()
{
	if((PIND & RIGHT_PLAYER_CONNECT_PIN) == 0)
	{
		is_right_player_connected = 1;
	}

	if((PIND & LEFT_PLAYER_CONNECT_PIN) == 0)
	{
		is_left_player_connected = 1;
	}
}

void game_reset()
{
	ball.pos_x = BALL_START_POSITION_X;
	ball.pos_y = BALL_START_POSITION_Y;

	ball.speed_x = BALL_START_SPEED_X;
	ball.speed_y = BALL_START_SPEED_Y;

	left_player_paddle.position = PADDLE_START_POSITION;
	right_player_paddle.position = PADDLE_START_POSITION;
}

void game_loop()
{
	is_ball_reflected = 0;
	game_clear_ball();
	game_clear_paddles();
	game_update();
	game_draw_ball();
	game_draw_paddles();
}

void game_update()
{
	if(ball.pos_x <= LEFT_TABLE_HALF+PADDLE_WIDTH)
	{
		if(ball.pos_x <= LEFT_TABLE_HALF)
		{
			right_player_paddle.score++;
			game_reset();
			ball.speed_x = -BALL_START_SPEED_X;
		}
		else if(game_is_ball_in_paddle(left_player_paddle.position))
		{
			ball.speed_y = game_get_ball_vertical_speed(left_player_paddle.position);
			ball.speed_x = game_get_ball_reflected_horizontal_speed();
			is_ball_reflected = 1;
		} 
	}
	else if(ball.pos_x >= RIGHT_TABLE_HALF - PADDLE_WIDTH)
	{
		if(ball.pos_x >= RIGHT_TABLE_HALF)
		{
			left_player_paddle.score++;
			game_reset();
		}
		else if(game_is_ball_in_paddle(right_player_paddle.position))
		{
			ball.speed_y = game_get_ball_vertical_speed(right_player_paddle.position);
			ball.speed_x = game_get_ball_reflected_horizontal_speed();
			is_ball_reflected = 1;
		}
	}

	game_get_left_player_movement();
	game_get_right_player_movement();
		
	if(ball.pos_x + ball.speed_x < LEFT_TABLE_HALF)
	{
		ball.pos_x = LEFT_TABLE_HALF;
	}
	else if(ball.pos_x + ball.speed_x > RIGHT_TABLE_HALF)
	{
		ball.pos_x = RIGHT_TABLE_HALF;
	}
	else
	{
		ball.pos_x += ball.speed_x;
	}

	if(ball.pos_y + ball.speed_y < 0)
	{
		ball.pos_y = 0;
		ball.speed_y = -ball.speed_y;
		is_ball_reflected = 1;
	}
	else if(ball.pos_y + ball.speed_y > SCREEN_HEIGHT-BALL_SIZE)
	{
		ball.pos_y = SCREEN_HEIGHT-BALL_SIZE;
		ball.speed_y = -ball.speed_y;
		is_ball_reflected = 1;
	}
	else
	{
		ball.pos_y += ball.speed_y;
	}
}

void game_get_left_player_movement()
{
	if(ball.pos_x < GAME_CENTER && !is_left_player_connected)
	{
		game_move_left_paddle();
	}
	else if(is_left_player_connected)
	{
		int8_t paddle_position = enc_1_value;

		if(paddle_position+PADDLE_SIZE > SCREEN_HEIGHT)
		{
			paddle_position = SCREEN_HEIGHT - PADDLE_SIZE;
			enc_1_value = paddle_position;
		}
		else if(paddle_position < 0)
		{
			paddle_position = 0;
			enc_1_value = 0;
		}

		left_player_paddle.position = paddle_position;
	}
}

void game_get_right_player_movement()
{
	if(ball.pos_x > GAME_CENTER && !is_right_player_connected)
	{
		game_move_right_paddle();
	}
	else if(is_right_player_connected)
	{
		int8_t paddle_position = enc_2_value;

		if(paddle_position+PADDLE_SIZE > SCREEN_HEIGHT)
		{
			paddle_position = SCREEN_HEIGHT - PADDLE_SIZE;
			enc_2_value = paddle_position;
		}
		else if(paddle_position < 0)
		{
			paddle_position = 0;
			enc_2_value = 0;
		}

		right_player_paddle.position = paddle_position;
	}
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

uint8_t game_is_ball_in_paddle(uint8_t paddle_position)
{
	if(paddle_position > ball.pos_y || paddle_position+PADDLE_SIZE < ball.pos_y)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int8_t game_get_ball_vertical_speed(uint8_t paddle_position)
{
	if(ball.pos_y == paddle_position)
	{
		return -3;
	}
	else if(ball.pos_y == paddle_position+PADDLE_SIZE)
	{
		return 3;
	}
	else if(ball.pos_y < paddle_position + PADDLE_SIZE/4)
	{
		return -2;
	}
	else if(ball.pos_y > paddle_position+PADDLE_SIZE - PADDLE_SIZE/4)
	{
		return 2;
	}
	else if(ball.pos_y < paddle_position + PADDLE_SIZE/2)
	{
		return -1;
	}
	else if(ball.pos_y > paddle_position+PADDLE_SIZE - PADDLE_SIZE/2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int8_t game_get_ball_reflected_horizontal_speed()
{
	int8_t result = -ball.speed_x;

	if(ball.speed_y == 0)
	{
		result += result > 0 ? 1 : -1;

	}
	
	if(result > BALL_MAX_SPEED)
	{
		result = BALL_MAX_SPEED;
	}
	else if(result < -BALL_MAX_SPEED)
	{
		result = -BALL_MAX_SPEED;
	}
	
	return result;
}

void game_move_right_paddle()
{
	int8_t target_position = ball.pos_y - PADDLE_SIZE/2;

	static int8_t offset = 3;

	offset = -offset;

	target_position += offset;

	if(target_position+PADDLE_SIZE > SCREEN_HEIGHT)
	{
		target_position = SCREEN_HEIGHT - PADDLE_SIZE;
	}
	else if(target_position < 0)
	{
		target_position = 0;
	}

	int8_t difference = target_position - right_player_paddle.position;

	if(difference > 0)
	{
		right_player_paddle.position += difference > PADDLE_SIZE*2 ? PADDLE_SIZE : difference > PADDLE_SIZE ? PADDLE_SIZE/2 : PADDLE_SIZE/4;
	}
	else if(difference < 0)
	{
		right_player_paddle.position -= difference > PADDLE_SIZE*2 ? PADDLE_SIZE : difference > PADDLE_SIZE ? PADDLE_SIZE/2 : PADDLE_SIZE/4;
	}
}

void game_move_left_paddle()
{
	int8_t target_position = ball.pos_y - PADDLE_SIZE/2;

	static int8_t offset = 2;

	offset = -offset;

	target_position+= offset;

	if(target_position+PADDLE_SIZE > SCREEN_HEIGHT)
	{
		target_position = SCREEN_HEIGHT - PADDLE_SIZE;
	}
	else if(target_position < 0)
	{
		target_position = 0;
	}

	int8_t difference = target_position - left_player_paddle.position;

	if(difference > 0)
	{
		left_player_paddle.position += difference > PADDLE_SIZE*2 ? PADDLE_SIZE : difference > PADDLE_SIZE ? PADDLE_SIZE/2 : PADDLE_SIZE/4;
	}
	else if(difference < 0)
	{
		left_player_paddle.position -= difference > PADDLE_SIZE*2 ? PADDLE_SIZE : difference > PADDLE_SIZE ? PADDLE_SIZE/2 : PADDLE_SIZE/4;
	}
}

void game_draw_static_graphic()
{
	game_draw_borders();
}

void game_draw_borders()
{
	for (uint8_t i=0; i<TABLE_HEIGHT; i++)
	{
		for(uint8_t j=i%2; j<LEFT_TABLE_HALF-2; j += 2)
		{
			glcd_set_pixel(j, i);
		}
	}

	for (uint8_t i=0; i<TABLE_HEIGHT; i++)
	{
		glcd_set_pixel(LEFT_TABLE_HALF-2, i);
		glcd_set_pixel(RIGHT_TABLE_HALF+2, i);
	}

	for (uint8_t i=0; i<TABLE_HEIGHT; i++)
	{
		for(uint8_t j=i%2; j<LEFT_TABLE_HALF-2; j += 2)
		{
			glcd_set_pixel(j+RIGHT_TABLE_HALF+2, i);
		}
	}
}