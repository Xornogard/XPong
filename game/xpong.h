/*
 * xpong.h
 *
 * Created: 03.12.2018 19:11:08
 *  Author: Xornogard
 */ 


#ifndef XPONG_H_
#define XPONG_H_

#include "../glcd/glcd.h"
#include "../encoder/encoder.h"

//////////////////////////////////////////////////////////////////////////
///		GAME CONFIGURATION
//////////////////////////////////////////////////////////////////////////

#define GAME_CENTER 64
#define TABLE_WIDTH 64
#define TABLE_HEIGHT 64
#define HALF_TABLE_WIDTH TABLE_WIDTH / 2
#define MAX_SCORE 10

#define LEFT_TABLE_HALF GAME_CENTER-HALF_TABLE_WIDTH
#define RIGHT_TABLE_HALF GAME_CENTER+HALF_TABLE_WIDTH

#define BALL_SIZE 3
#define PADDLE_SIZE 9
#define PADDLE_WIDTH 2

#define BALL_MAX_SPEED 6
#define BALL_START_SPEED_X 2
#define BALL_START_SPEED_Y 0

#define BALL_START_POSITION_X SCREEN_WIDTH/2
#define BALL_START_POSITION_Y SCREEN_HEIGHT/2

#define PADDLE_START_POSITION (SCREEN_HEIGHT/2) - (PADDLE_SIZE/2)

#define LEFT_PLAYER_CONNECT_PIN (1 << PD7)
#define RIGHT_PLAYER_CONNECT_PIN (1 << PD6)

//////////////////////////////////////////////////////////////////////////
///		STRUCTURES
//////////////////////////////////////////////////////////////////////////

struct Ball {
	uint8_t pos_x;
	int8_t pos_y;

	int8_t speed_x;
	int8_t speed_y;
};

struct Paddle {
	uint8_t previous_position;
	uint8_t position;
	uint8_t score;
};

//////////////////////////////////////////////////////////////////////////
///     VARIABLES
//////////////////////////////////////////////////////////////////////////

extern struct Ball ball;

extern struct Paddle left_player_paddle;
extern struct Paddle right_player_paddle;

extern uint8_t is_ball_reflected;
extern uint8_t is_left_player_connected;
extern uint8_t is_right_player_connected;

//////////////////////////////////////////////////////////////////////////
///		PROCEDURES
//////////////////////////////////////////////////////////////////////////

void game_init();
void game_detect_controllers();

void game_reset();
void game_clear_ball();
void game_clear_paddles();

void game_loop();

void game_update();

void game_draw_ball();
void game_draw_paddles();

void game_draw_static_graphic();
void game_draw_borders();

void game_get_left_player_movement();
void game_get_right_player_movement();

void game_move_right_paddle();
void game_move_left_paddle();

uint8_t game_is_ball_in_paddle(uint8_t paddle_position);
int8_t game_get_ball_vertical_speed(uint8_t paddle_position);
int8_t game_get_ball_reflected_horizontal_speed();

#endif /* XPONG_H_ */