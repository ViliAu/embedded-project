/*
 * buzzer.c
 *
 * Created: 7.4.2024 13.26.30
 *  Author: Vili Huusko
 */ 

#include "buzzer.h"

#define buzzer_DD DDRB
#define buzzer_PORT PORTB
#define buzzer_PIN 1

int setup = 0;

void setup_buzzer() {
	if (setup == 0) {
		buzzer_DD |= (1 << buzzer_PIN);
		setup = 1;
	}
}

void play_sound(double duration) {
	setup_buzzer();
	buzzer_PORT |= (1 << buzzer_PIN); // Set buzzer pin HIGH
	_delay_ms(duration);
	buzzer_PORT &= ~(1 << buzzer_PIN); // set buzzer pin LOW
}
