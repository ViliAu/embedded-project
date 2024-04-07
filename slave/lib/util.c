/*
 * util.c
 *
 * Created: 6.4.2024 16.33.17
 *  Author: Vili huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 
#include <string.h>

#include "lcd.h"
#include "util.h"

int initialized = 0;

char c_l1[16];
char c_l2[16];

void initialize_lcd() {
	if (!initialized) {
		lcd_init(LCD_DISP_ON);
		initialized = 1;
	}
}

void write_lcd(char* l1, char* l2) {
	initialize_lcd();
	// Prevent the screen from flickering if printing the same msg
	if (!strcmp(c_l1, l1) && !strcmp(c_l2, l2)) {
		return;
	}
	strcpy(c_l1, l1);
	strcpy(c_l2, l2);
	lcd_clrscr();
	lcd_puts(c_l1);
	lcd_gotoxy(0,1);
	lcd_puts(c_l2);
}