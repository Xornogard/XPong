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
	BUZZER_DDR |= BUZZER;

	game_init();


    while (1) 
    {
		game_loop();
		
		if(ball_reflected)
		{
			BUZZER_PORT &= ~BUZZER;
		}
		else
		{
			BUZZER_PORT |= BUZZER;
		}

		_delay_ms(200);
    }
}
