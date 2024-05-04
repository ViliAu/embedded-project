/*
 * password_manager.h
 *
 * Created: 4.5.2024 15.38.42
 * Author: Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 


#ifndef PASSWORD_MANAGER_H_
#define PASSWORD_MANAGER_H_

	#include <string.h>
	
	#define PSWD_MAX_LEN 9
	#define PSWD_MIN_LEN 4
	
	char g_pswd_buffer[10];
	
	void add_char(char c);
	
	extern int check_password();
	extern int update_password();
	extern int input_char(char c);
	extern void clear_buffer();

#endif /* PASSWORD_MANAGER_H_ */