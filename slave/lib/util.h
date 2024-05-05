/*
 * util.c
 *
 * Created: 6.4.2024 16.33.17
 *  Author: Vili huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 


#ifndef UTIL_H_
#define UTIL_H_
	
	#include <string.h>
	#include <stdbool.h>
	#include "lcd.h"
	
	extern void initialize_lcd();
	extern void write_lcd(char* l1, char* l2);

#endif /* UTIL_H_ */