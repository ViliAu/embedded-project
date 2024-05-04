/*
 * slave_spi.h
 *
 * Created: 26/04/2024 12.22.11
 * Author: Vili huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 


#ifndef SLAVE_SPI_H_
#define SLAVE_SPI_H_
	
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <stddef.h>
	#include <stdbool.h>
	#include <string.h>
	#include "util.h"
	
	#define BYTES_IN_PACKET 65
	/* See: https://www.ascii-code.com/ */
	#define NEG_ACK_BYTE 21
	
	typedef struct packet {
		uint8_t first_byte;
		char param1[(BYTES_IN_PACKET - 1) / 2];
		char param2[(BYTES_IN_PACKET - 1) / 2];
	} Packet;
	
	void setup_slave_spi();
	void on_transfer_success();
	
	extern void digest_message(Packet* dest);
	extern volatile bool is_new_message();

#endif /* SLAVE_SPI_H_ */