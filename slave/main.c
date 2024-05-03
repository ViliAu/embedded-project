/*
 * slave.c
 *
 * Created: 18.3.2024 18.03.27
 * Authors : Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 

#include "main.h"

#define CONN_POLL_TIME 10

volatile int state;

int main(void) {
	// enable global interrupts
	sei();
	Packet p;
	setup_slave_spi();
	
	while (1) {
		while (!is_new_message()){}
		digest_message(&p);
		write_lcd(p.param1, p.param2);
	}
	
	//setup_slave();
//	loop_slave();
	return 0;
}

void setup_slave() {
	// initialize state
	state = AWAITING_CONNECTION;
	write_lcd("Awaiting", "Connection...");
	_delay_ms(CONN_POLL_TIME * 1000);
	if (state == AWAITING_CONNECTION) {
		state = ERROR;
		write_lcd("Connection", "timed out");
	}
	else {
		state = READY;
		write_lcd("OK", "");
	}
}

/*void loop_slave() {
	while (1) {
		switch(state) {
			case AWAITING_CONNECTION:
				write_lcd("Awaiting", "Connection...");
				break;
			case ERROR:
				break;
			default:
				state = ERROR;
				break;
		}
	}
}*/

/*
char c_char[2];
int c = 10;
while(1)
{
	_delay_ms(1000);
	itoa(c, c_char, 10);
	write_lcd("moi", c_char);
	if (c > 0)
	{
		c--;
	}
	else {
		//play_sound(1000);
	}
}
*/

