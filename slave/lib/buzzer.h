/*
 * buzzer.h
 *
 * Created: 7.4.2024 13.26.39
 *  Author: Vili
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_
	
	#define __DELAY_BACKWARD_COMPATIBLE__ // Allows for variable sound play duration
	#define F_CPU 16000000UL
	
	#include <avr/io.h>
	#include <util/delay.h>
	
	extern void setup_buzzer();
	extern void play_sound(double duration);

#endif /* BUZZER_H_ */