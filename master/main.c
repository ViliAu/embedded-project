/*
 * master.c
 *
 * Created: 18.3.2024 18.03.05
 * Authors : Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 

#include "main.h"

int g_state = DISARMED;
char* g_pswd;

int main(void) {
    setup_master();
	loop_master();
}

void setup_master() {
	
	KEYPAD_Init();
	write_slave_lcd("A - ARM\0", "C - CHANGE PSWD\0");
	g_pswd = read_password();
	char g[5];
	strcpy(g, g_pswd);
	g[5] = '\0';
	write_slave_lcd(g, "\0");
	g_state = DISARMED;
}

void loop_master() {
	int countdown = 0;
	int seconds_left;
	char s[2];
	while(1) {
		_delay_ms(100);
		switch(g_state) {
			case DISARMED:
			    // stop alarm
				if (KEYPAD_GetKey() == 'A') {
					g_state = ARMED;
				}
				else if (KEYPAD_GetKey() == 'C') {
					g_state = SET_PSWD;
				}
				break;
			case ARMED:
				write_slave_lcd("ARMED!\0", "\0");
				if (check_motion()) {
					g_state = TRIGGERED;
					countdown = 0;
				}
				break;
			case TRIGGERED:
				countdown++;
				seconds_left = 10 - countdown / 10;
				itoa(seconds_left, s, 10);
				write_slave_lcd("COUNTDOWN!\0", s);
				if (countdown > 100) {
					countdown = 100;
					// Sound alarm
				}
				break;
			case SET_PSWD:
				write_slave_lcd("Set password:\0", "\0");
				break;
			case ERROR:
			default:
				break;
				//error state
		}
		
	}
}

void write_slave_lcd(char* l1, char* l2) {
	//char ll1[31];
	//char ll2[31];
	//strcpy(ll1, l1);
	//strcpy(ll2, l2);
	//ll1[31] = '\0';
	//ll2[31] = '\0';
	Packet p;
	assemble_packet("k", l1, l2, &p);
	send_packet_to_slave(&p);
}



