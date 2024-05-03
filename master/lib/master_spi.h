/*
 * master_spi.h
 *
 * Created: 26/04/2024 16.55.57
 * Author: Vili huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 


#ifndef MASTER_SPI_H_
#define MASTER_SPI_H_
	
	#include <avr/io.h>
	#define F_CPU 16000000UL
	#include <util/delay.h>
	#include <stdbool.h>
	
	#define BYTES_IN_PACKET 65
	/* See: https://www.ascii-code.com/ */
	#define NEG_ACK_BYTE 21
	
	typedef struct packet {
		uint8_t first_byte;
		char param1[(BYTES_IN_PACKET - 1) / 2];
		char param2[(BYTES_IN_PACKET - 1) / 2];
	} Packet;
	
	void packet_to_uchar_arr(Packet* src, unsigned char* dest);
	void setup_master_spi();
	
	extern bool send_packet_to_slave(Packet* packet);
	extern void assemble_package(uint8_t first_byte, char* param1, char* param2, Packet* package);

#endif /* MASTER_SPI_H_ */