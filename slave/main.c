/*
 * slave.c
 *
 * Created: 18.3.2024 18.03.27
 * Authors : Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 

#include "main.h"

uint8_t g_state;

bool check_connection() {
	double seconds_waited = 0;
	// loop until a new message is received from master or timeout reached
	while (!is_new_message()) {
		if (seconds_waited > CHECK_CONN_TIMEOUT_SECONDS) {
			write_lcd("Connection\0", "Timed out\0");
			return false;
		}
		seconds_waited += 0.005;
		_delay_ms(5);
	}
	// check that the first packet is connection check
	Packet p;
	digest_message(&p);
	if (p.first_byte == CHECK_CONN_BYTE) {
		// connection ok
		write_lcd("Connection\0", "Established\0");
		return true;
		} else {
		// something went wrong
		write_lcd("Unknown\0", "Error\0");
	}
	return false;
}

bool initialize() {
	// enable global interrupts for the SPI communication
	sei();
	// setup the SPI communication
	setup_slave_spi();
	// wait for the connection check packet from master
	write_lcd("Awaiting\0", "Connection\0");
	return check_connection();
}

int main(void) {
	// set state to initializing
	g_state = INIT_STATE;
	// if initialization is ok continue, otherwise exit
	if (initialize()) {
		// set state to OK
		g_state = OK_STATE;
		Packet p;
		while (1) {
			while (!is_new_message()){}
			digest_message(&p);
			switch (p.first_byte) {
				case 'p':
					// print packet to screen
					write_lcd(p.param1, p.param2);
					break;
				case 'a':
					// play alarm on buzzer
					break;
			}
		}
	}
	return 0;
}
