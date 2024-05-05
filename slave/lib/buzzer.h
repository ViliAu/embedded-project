/*
 * buzzer.h
 *
 * Created: 7.4.2024 13.26.39
 * Authors : Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_
	
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <stdbool.h>
	
	void setup_buzzer();
	
	extern void enable_buzzer();
	extern void disable_buzzer();

#endif /* BUZZER_H_ */