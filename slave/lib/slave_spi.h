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
	#include <stdbool.h>
	#include <string.h>
	
	#ifndef BYTES_IN_PACKET
	#define BYTES_IN_PACKET 20
	#endif
	
	#ifndef END_OF_PACKET
	#define END_OF_PACKET '\0'
	#endif
	
	void setup_slave_spi();
	void on_transfer_completed();
	
	extern void digest_message(char* dest);
	extern volatile bool is_new_message();

#endif /* SLAVE_SPI_H_ */