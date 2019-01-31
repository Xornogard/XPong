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

#define ENC_1_INTERRUPT (1 << INT0);
#define ENC_2_INTERRUPT (1 << INT1);

#define ENC_PORT PORTD
#define ENC_PIN PIND

#define ENC_1_PIN_A (1 << PD5)
#define ENC_1_PIN_B (1 << PD2)
#define ENC_1_ISC (1 << ISC00)

#define ENC_2_PIN_A (1 << PD3)
#define ENC_2_PIN_B (1 << PD4)
#define ENC_2_ISC (1 << ISC10)

extern int8_t enc_1_value;
extern int8_t enc_2_value;

void enc_init();

#endif /* ENCODER_H_ */