/*
 * slave.c
 *
 * Created: 18.3.2024 18.03.27
 * Authors : Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 

#include "main.h"

static uint8_t g_buzzer_state = 0;

void sleep_until_new_msg() {
	// disable interrupts to prevent race conditions
	cli();
	// loop while no new message from master
	while (!is_new_message()) {
		// enter sleep mode, interrupts will wake the device up
		sleep_enable();
		sei();
		sleep_cpu();
		sleep_disable();
	}
	// enable global interrupts
	sei();
}

int main(void) {
	Packet p;
	// enable global interrupts
	sei();
	// set the sleep mode to IDLE
	set_sleep_mode(SLEEP_MODE_IDLE);
	// setup the SPI communication
	setup_slave_spi();
	while (1) {
		sleep_until_new_msg();
		digest_message(&p);
		switch (p.first_byte) {
			case 'p':
				// print packet to screen
				write_lcd(p.param1, p.param2);
				break;
			case 'a':
				// play alarm on buzzer
				if (g_buzzer_state == 0) {
					enable_buzzer();
					g_buzzer_state = 1;	
				}
				break;
			case 'd':
				// disable alarm
				if (g_buzzer_state == 1) {
					disable_buzzer();
					g_buzzer_state = 0;
				}
				break;
		}
	}
	return 0;
}
