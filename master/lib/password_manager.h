/*
 * password_manager.h
 *
 * Created: 4.5.2024 15.38.42
 * Author: Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 


#ifndef PASSWORD_MANAGER_H_
#define PASSWORD_MANAGER_H_

	#include <string.h>
	#include <stdbool.h>
	
	#define PSWD_MAX_LEN 9
	#define PSWD_MIN_LEN 4
	
	char g_pswd_buffer[10];
	
	void add_char(char c);
	
	extern bool check_password();
	extern bool update_password();
	extern void input_char(char c);
	extern void clear_buffer();

#endif /* PASSWORD_MANAGER_H_ */