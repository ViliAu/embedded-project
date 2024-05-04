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
	// Setup error pin
	DDRD |= (1 << ERROR_PIN);
	
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
				write_slave_lcd("A - ARM", "C - CHANGE PSWD");
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
				// set error led HIGH
				ERROR_PORT |= (1 << ERROR_PIN);
				break;
		}
	}
}

void try_pswd(char c) {
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
	try_pswd(c);
	write_slave_lcd("ARMED!", g_pswd_buffer);
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
	char msg[16] = "Countdown: ";
	strcat(msg, s_left);
	
	try_pswd(c);
	write_slave_lcd(msg, g_pswd_buffer);
}

// Handles the SET_PSWD state
void handle_set_pswd(char c) {
	switch(c) {
		case 'A':
			if (update_password()) {
				g_state = DISARMED;	
			}
			break;
		case 'C':
			g_state = DISARMED;
			break;
		default:
			input_char(c);
	}
	char msg[17] = "pswd: ";
	strcat(msg, g_pswd_buffer);
	write_slave_lcd(msg, "A OK | C CANCEL");
}

void init_connection() {
	Packet p;
	assemble_packet('c', "\0", "\0", &p);
	if (!send_packet_to_slave(&p)) {
		g_state = ERROR;
	}
}

// Adds a \0 to the end of parameters and sends the msg to slave
void write_slave_lcd(char* l1, char* l2) {
	char* l1_terminated = (char*)malloc(strlen(l1)+1);
	char* l2_terminated = (char*)malloc(strlen(l2)+1);
	if (l1_terminated == NULL || l2_terminated == NULL) {
		g_state = ERROR;
	}
	strcpy(l1_terminated, l1);
	l1_terminated[strlen(l1)] = '\0';
	strcpy(l2_terminated, l2);
	l1_terminated[strlen(l2)] = '\0';
	
	Packet p;
	assemble_packet('p', l1, l2, &p);
	if (!send_packet_to_slave(&p)) {
		free(l1_terminated);
		free(l2_terminated);
		g_state = ERROR;
	}
}

void toggle_buzzer(int b) {
	char cmd = b ? 'a' : 'd';
	Packet p;
	assemble_packet(cmd, '\0', '\0', &p);
	if (!send_packet_to_slave(&p)) {
		g_state = ERROR;
	}
}



