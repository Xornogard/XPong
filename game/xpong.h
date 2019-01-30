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

#define BALL_START_POSITION_X SCREEN_WIDTH/2
#define BALL_START_POSITION_Y SCREEN_HEIGHT/2
 
#define PADDLE_START_POSITION (SCREEN_HEIGHT/2) - (PADDLE_SIZE/2)

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

//////////////////////////////////////////////////////////////////////////
///		PROCEDURES
//////////////////////////////////////////////////////////////////////////

void game_init();
void game_reset();
void game_clear_ball();
void game_clear_paddles();

void game_loop();

void game_update();

void game_draw_ball();
void game_draw_paddles();

void game_draw_static_graphic();
void game_draw_borders();

#endif /* XPONG_H_ */