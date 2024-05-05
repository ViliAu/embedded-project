/*
 * password_manager.c
 *
 * Created: 4.5.2024 13.19.51
 * Author: Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 

#include "password_manager.h"

// Initiate default password as EEPROM refused to work
char g_pswd[PSWD_MAX_LEN] = "1234";

int g_pswd_iterator = 0;
int g_ready_for_new_pswd = 1;

// Used to check if password buffer equals stored password.
// Return false or true whether the passwords match.
extern bool check_password() {
	return strcmp(g_pswd_buffer, g_pswd) == 0;
}

// Stores the buffered new password.
// Returns false or true depending if the action was successful
extern bool update_password() {
	if (strlen(g_pswd_buffer) < PSWD_MIN_LEN) {
		return 0;
	}
	else {
		strcpy(g_pswd, g_pswd_buffer);
		return 1;
	}
}

// Clears password buffer
extern void clear_buffer() {
	g_pswd_iterator = 0;
	for (int i = 0; i < PSWD_MAX_LEN; i++) {
		g_pswd_buffer[i] = '\0';
	}
}

// Validates input to the password buffer
void add_char(char c) {
	if (c == '*' || c == '#') {
		if (g_pswd_iterator > 0) {
			g_pswd_buffer[--g_pswd_iterator] = '\0';
		}
	}
	else {
		if (g_pswd_iterator < PSWD_MAX_LEN) {
			g_pswd_buffer[g_pswd_iterator++] = c;
		}
	}
}

// Adds a character to the password buffer
extern void input_char(char c) {
	switch(c) {
		// error
		case 'z':
		// Ignore
		case 'A':
		case 'B':
		case 'C':
		case 'D':
			break;
		default:
			add_char(c);
	}
}
