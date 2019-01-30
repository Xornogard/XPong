/*
 * encoder.h
 *
 * Created: 30.01.2019 14:11:31
 *  Author: Xornogard
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef ENCODER_H_
#define ENCODER_H_

#define ENC_INTERRUPT INT0;

#define ENC_PORT PORTD
#define ENC_PIN PIND

#define ENC_PIN_A (1 << PD3)
#define ENC_PIN_B (1 << PD2)

extern uint8_t enc_value;

void enc_init();

#endif /* ENCODER_H_ */