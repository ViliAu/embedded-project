/*
 * master.c
 *
 * Created: 18.3.2024 18.03.05
 * Authors : Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 

#include "main.h"

volatile static int g_state = DISARMED;

static int g_countdown = 0;

int main(void) {
    setup_master();
	loop_master();
}

void setup_master() {
	init_connection();
	KEYPAD_Init();
	g_state = DISARMED;
}

void loop_master() {
	int keypad_counter = 0;
	char c;
	while(1) {
		_delay_ms(100);
		if (keypad_counter == 5) {
			if ((c = KEYPAD_GetKey()) != 'z') {
				keypad_counter = 0;
			}
		}
		else {
			keypad_counter++;
			c = 'z';
		}
		switch(g_state) {
			case DISARMED:
				toggle_buzzer(0);
				clear_buffer();
				write_slave_lcd("A - ARM\0", "C - CHANGE PSWD\0");
				if (c == 'A') {
					g_state = ARMED;
				}
				else if (c == 'C') {
					g_state = SET_PSWD;
				}
				break;
			case ARMED:
				handle_armed(c);
				break;
			case TRIGGERED:
				handle_triggered(c);
				break;
			case SET_PSWD:
				handle_set_pswd(c);
				break;
			case ERROR:
			default:
				break;
				//error state
		}
	}
}

// Handles the armed state
void handle_armed(char c) {
	// Check for motion
	if (check_motion()) {
		g_state = TRIGGERED;
		// Set alarm countdown iterations to 0
		g_countdown = 0;
		// Clear password buffer
		clear_buffer();
		return;
	}
	
	
	char pswd_msg[17] = " ";
	strcpy(pswd_msg, g_pswd_buffer);
	pswd_msg[16] = '\0';
	switch(c) {
		case 'A':
			if (check_password()) {
				g_state = DISARMED;
			}
			else {
				toggle_buzzer(1);
			}
			clear_buffer();
			break;
		default:
			input_char(c);
	}
	write_slave_lcd("ARMED!", pswd_msg);
}

// Handles triggered state
void handle_triggered(char c) {
	// Check if 10s has passed
	if (g_countdown >= 100) {
		g_countdown = 100;
		toggle_buzzer(1);
	}
	g_countdown++;
	
	char s_left[3];
	int seconds_left = 10 - g_countdown / 10;
	itoa(seconds_left, s_left, 10);
	char msg[17] = "Countdown: ";
	strcat(msg, s_left);
	msg[16] = '\0';
	
	char pswd_msg[17] = " ";
	strcpy(pswd_msg, g_pswd_buffer);
	pswd_msg[16] = '\0';
	switch(c) {
		case 'A':
			if (check_password()) {
				g_state = DISARMED;
			}
			else {
				toggle_buzzer(1);
			}
			clear_buffer();
			break;
		default:
		input_char(c);
	}
	write_slave_lcd(msg, pswd_msg);
}

// Handles the SET_PSWD state
void handle_set_pswd(char c) {
	char msg[17] = "pswd: ";
	strcat(msg, g_pswd_buffer);
	msg[16] = '\0';
	write_slave_lcd(msg, "A OK | C CANCEL\0");
	switch(c) {
		case 'A':
			update_password();
			g_state = DISARMED;
			break;
		case 'C':
			g_state = DISARMED;
			break;
		default:
			input_char(c);
	}
}

void init_connection() {
	Packet p;
	assemble_packet('c', "\0", "\0", &p);
	send_packet_to_slave(&p);
}

void write_slave_lcd(char* l1, char* l2) {
	Packet p;
	assemble_packet('p', l1, l2, &p);
	send_packet_to_slave(&p);
}

void toggle_buzzer(int b) {
	char cmd = b ? 'a' : 'd';
	Packet p;
	assemble_packet(cmd, '\0', '\0', &p);
	send_packet_to_slave(&p);
}



