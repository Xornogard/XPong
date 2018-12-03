/*
 * xpong.h
 *
 * Created: 03.12.2018 19:11:08
 *  Author: Xornogard
 */ 


#ifndef XPONG_H_
#define XPONG_H_

#include "../glcd/glcd.h"

//////////////////////////////////////////////////////////////////////////
///		GAME CONFIGURATION
//////////////////////////////////////////////////////////////////////////

#define PADDLE_SIZE 10
#define PADDLE_WIDTH 4

#define BALL_SIZE 3

//////////////////////////////////////////////////////////////////////////
///		PROCEDURES
//////////////////////////////////////////////////////////////////////////

void game_init();
void game_reset();
void game_clear_ball();

void game_loop();

void game_update();

void game_draw_ball();
void game_draw_paddles();

#endif /* XPONG_H_ */