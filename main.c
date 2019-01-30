/*
 * LCD_TRY_1000.c
 *
 * Created: 13.10.2018 17:34:28
 * Author : Xornogard
 */ 

#include <avr/io.h>
#include "game/xpong.h"
#include "glcd/glcd.h"
#include "graphics/graphics.h"

int main(void)
{
	game_init();

    while (1) 
    {
		game_loop();
		_delay_ms(200);
    }
}
