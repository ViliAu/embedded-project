/*
 * util.c
 *
 * Created: 6.4.2024 16.33.17
 *  Author: Vili huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 

#include "lcd.h"
#include "util.h"

int initialized = 0;


void write_lcd(char* l1, char* l2)
{
	if (!initialized)
	{
		lcd_init(LCD_DISP_ON);
		initialized = 1;
	}
	lcd_clrscr();
	lcd_puts(l1);
	lcd_gotoxy(0,1);
	lcd_puts(l2);
}