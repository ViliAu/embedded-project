/*
 * slave_spi.c
 *
 * Created: 26/04/2024 12.22.50
 * Author: Vili huusko, Jani Heinikoski, Konsta Keski-Mattinen
 * Sources:
 * Course exercise 10, ATmega2560 datasheet pp. 190-199
 */ 
#include "slave_spi.h"

int g_setup = 0;

// global variables for storing data used in SPI communication
unsigned char g_spi_send_data[BYTES_IN_PACKET] = "acknowledge\0";
unsigned char g_spi_receive_data[BYTES_IN_PACKET];
volatile bool g_is_transfer_complete = 0;
volatile uint8_t g_spi_byte_index = 0;

void setup_slave_spi() {
	if (g_setup == 0) {
		/* set master input - slave output (MISO) as output, pin 12 (PB4) */
		DDRB  |= (1 << PB4);
		/* set SPI enable (SPE) and interrupt enable (SPIE) (see ATmega2560 datasheet chapter 21.2.1 p. 197) */
		SPCR  |= (1 << 6) | (1 << 7);
		g_setup = 1;
	}
}

void on_transfer_success() {
	g_is_transfer_complete = 1;
	g_spi_byte_index = 0;
}

volatile bool is_new_message() {
	return g_is_transfer_complete;
}

void digest_message(char* dest) {
	for (uint8_t i = 0; i < BYTES_IN_PACKET; i++) {
		*(dest + i) = (char) g_spi_receive_data[i]; 
	}
	g_is_transfer_complete = 0;
}

/* use interrupts to receive a message and send a response */
ISR
(SPI_STC_vect)
{
	if (g_spi_byte_index < BYTES_IN_PACKET && g_is_transfer_complete == 0) {
		/* reading SPDR causes the Shift Register Receive buffer to be read */
		unsigned char spi_receive_buffer = SPDR;
		g_spi_receive_data[g_spi_byte_index] = spi_receive_buffer;
		/* transmit a byte back as a response (writing to SPDR initiates data transmission) */
		SPDR = g_spi_send_data[g_spi_byte_index];
		g_spi_byte_index++;
		/* packet transfer complete when all bytes are transferred */
		if (g_spi_byte_index == BYTES_IN_PACKET)
		{
			on_transfer_success();
		}
	}
}

