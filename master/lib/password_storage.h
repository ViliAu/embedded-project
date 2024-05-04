/*
 * password_storage.h
 *
 * Created: 25.4.2024 19.47.15
 * Author: Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 


#ifndef MEM_UTIL_H_
#define MEM_UTIL_H_

	#include <avr/eeprom.h>
	#include <avr/interrupt.h>
	#include <string.h>

	char* read_password();
	int store_password(char* pswd);

#endif /* MEM_UTIL_H_ */