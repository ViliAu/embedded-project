/*
 * password_manager.h
 *
 * Created: 4.5.2024 15.38.42
 * Author: Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 


#ifndef PASSWORD_MANAGER_H_
#define PASSWORD_MANAGER_H_

	#include <string.h>
	
	#define PSWD_MAX_LEN 10
	
	char g_pswd_buffer[10];
	
	int check_password();
	void update_password();
	void add_char(char c);
	int input_char(char c);
	void clear_buffer();

#endif /* PASSWORD_MANAGER_H_ */