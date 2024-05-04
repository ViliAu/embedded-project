/*
 * password_storage.c
 *
 * Created: 25.4.2024 19.47.05
 *  Author: Vili
 */ 

// Wrapper for reading and writing to the EEPROM memory
// https://www.nongnu.org/avr-libc/user-manual/group__avr__eeprom.html
// EEPROM seems to have reached the end of its life cycle

#include "password_storage.h"

#define PSWD_ADDR 1000000
#define CHECKSUM_ADDR 5

#define PSWD_LEN 1000004
#define DEFAULT_PSWD "1234"

char* read_password() {
	cli();
	char* pswd = "";
	char* checksum = "";
	eeprom_read_block((void*)&pswd, (const void*)PSWD_ADDR, PSWD_LEN);
	eeprom_read_block((void*)&checksum, (const void*)CHECKSUM_ADDR, PSWD_LEN);
	sei();
	if (!strcmp(pswd, checksum)) {
		return pswd;
	}
	// Password and checksum do not math (data corruption or 
	//   password not set before) => initialize default password
	else {
		store_password(DEFAULT_PSWD);
		return "ERR!";
	}
}

int store_password(char* pswd) {
	if (strlen(pswd) != PSWD_LEN) {
		return 0;
	}
	cli();
	eeprom_write_block((const void*)&pswd, (void*)PSWD_ADDR, PSWD_LEN);
	eeprom_write_block((const void*)&pswd, (void*)CHECKSUM_ADDR, PSWD_LEN);
	sei();
	return 1;
}