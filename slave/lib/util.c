/*
 * util.c
 *
 * Created: 6.4.2024 16.33.17
 *  Author: Vili huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 
#include "util.h"

static int g_initialized = false;

static char g_c_l1[16];
static char g_c_l2[16];

void initialize_lcd() {
	if (!g_initialized) {
		lcd_init(LCD_DISP_ON);
		g_initialized = true;
	}
}

void write_lcd(char* l1, char* l2) {
	initialize_lcd();
	// Prevent the screen from flickering if printing the same msg
	if (!strcmp(g_c_l1, l1) && !strcmp(g_c_l2, l2)) {
		return;
	}
	strcpy(g_c_l1, l1);
	strcpy(g_c_l2, l2);
	lcd_clrscr();
	lcd_puts(g_c_l1);
	lcd_gotoxy(0,1);
	lcd_puts(g_c_l2);
}