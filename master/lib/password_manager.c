/*
 * password_manager.c
 *
 * Created: 4.5.2024 13.19.51
 *  Author: Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 

#include "password_manager.h"

// Initiate default password
char g_pswd[PSWD_MAX_LEN] = "1234";
int g_pswd_iterator = 0;
int g_ready_for_new_pswd = 1;

int check_password() {
	return strcmp(g_pswd_buffer, g_pswd) == 0;
}

void update_password() {
	strcpy(g_pswd, g_pswd_buffer);
}

void clear_buffer() {
	g_pswd_iterator = 0;
	for (int i = 0; i < PSWD_MAX_LEN; i++) {
		g_pswd_buffer[i] = '\0';
	}
}

void add_char(char c) {
	if (c == '*' || c == '#') {
		if (g_pswd_iterator > 0) {
			//g_pswd_iterator--;
			g_pswd_buffer[--g_pswd_iterator] = '\0';
		}
	}
	else {
		if (g_pswd_iterator < PSWD_MAX_LEN) {
			g_pswd_buffer[g_pswd_iterator++] = c;
			//g_pswd_iterator++;
		}
	}
}

// Adds a character to the password buffer, returns 0 if char not added and 1 if char was added
int input_char(char c) {
	switch(c) {
		// error
		case 'z':
		// Ignore
		case 'A':
		case 'B':
		case 'C':
		case 'D':
			return 0;
			break;
		default:
			add_char(c);
	}
	return 1;
}
