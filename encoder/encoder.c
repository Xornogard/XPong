/*
 * encoder.c
 *
 * Created: 30.01.2019 14:11:41
 *  Author: Xornogard
 */ 

 #include "encoder.h"

 int8_t enc_1_value;
 int8_t enc_2_value;

 void enc_init()
 {
	 ENC_PORT |= ENC_1_PIN_A;
	 ENC_PORT |= ENC_1_PIN_B;

	 ENC_PORT |= ENC_2_PIN_A;
	 ENC_PORT |= ENC_2_PIN_B;

	 GICR |= ENC_1_INTERRUPT;
	 GICR |= ENC_2_INTERRUPT;

	 MCUCR |= ENC_1_ISC;
	 MCUCR |= ENC_2_ISC;

	 sei();
 }

ISR( INT0_vect)
{
	static uint8_t dir;

	if(!(ENC_PIN & ENC_1_PIN_B))
	{
		dir = (ENC_PIN & ENC_1_PIN_A);
	}
	else
	{
		if(dir != (ENC_PIN & ENC_1_PIN_A))
		{
			if(dir)
			{
				enc_1_value++;
			}
			else
			{
				enc_1_value--;
			}
		}
	}
}

ISR( INT1_vect)
{
	static uint8_t dir;

	if(!(ENC_PIN & ENC_2_PIN_B))
	{
		dir = (ENC_PIN & ENC_2_PIN_A);
	}
	else
	{
		if(dir != (ENC_PIN & ENC_2_PIN_A))
		{
			if(dir)
			{
				enc_2_value++;
			}
			else
			{
				enc_2_value--;
			}
		}
	}
}