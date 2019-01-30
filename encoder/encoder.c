/*
 * encoder.c
 *
 * Created: 30.01.2019 14:11:41
 *  Author: Xornogard
 */ 

 #include "encoder.h"

 uint8_t enc_value;

 void enc_init()
 {
	 ENC_PORT |= ENC_PIN_B;
	 ENC_PORT |= ENC_PIN_A;

	 GICR |= (1 << INT0); //Enable INT0
	 MCUCR |= (1 << ISC00);

	 sei();
 }

ISR( INT0_vect)
{
	static uint8_t dir;

	if(!(ENC_PIN & ENC_PIN_B))
	{
		dir = (ENC_PIN & ENC_PIN_A);
	}
	else
	{
		if(dir != (ENC_PIN & ENC_PIN_A))
		{
			if(dir)
			{
				enc_value++;
			}
			else
			{
				enc_value--;
			}
		}
	}
}