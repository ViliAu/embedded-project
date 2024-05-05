/*
 * slave_spi.c
 *
 * Created: 26/04/2024 12.22.50
 * Author: Vili huusko, Jani Heinikoski, Konsta Keski-Mattinen
 * Sources:
 * Course exercise 10, ATmega2560 datasheet pp. 190-199
 */ 
#include "slave_spi.h"

static bool g_setup = false;

static volatile bool g_is_transfer_complete = false;
static volatile uint8_t g_spi_byte_index = 0;
static volatile Packet g_packet;

void setup_slave_spi() {
	if (g_setup == false) {
		/* set master input - slave output (MISO) as output, pin 12 (PB4) */
		DDRB  |= (1 << PB4);
		/* set SPI enable (SPE) and interrupt enable (SPIE) (see ATmega2560 datasheet chapter 21.2.1 p. 197) */
		SPCR  |= (1 << 6) | (1 << 7);
		g_setup = true;
	}
}

void on_transfer_success() {
	/* mark packet transfer as completed */
	g_is_transfer_complete = true;
	/* reset the byte index back to zero */
	g_spi_byte_index = 0;
}

volatile bool is_new_message() {
	return g_is_transfer_complete;
}

void digest_message(Packet* dest) {
	if (dest != NULL) {
		dest->first_byte = g_packet.first_byte;
		for (uint8_t i = 0; i < (BYTES_IN_PACKET - 1) / 2 - 1; i++) {
			dest->param1[i] = g_packet.param1[i];
			dest->param2[i] = g_packet.param2[i];
		}
		dest->param1[(BYTES_IN_PACKET - 1) / 2 - 1] = '\0';
		dest->param2[(BYTES_IN_PACKET - 1) / 2 - 1] = '\0';
	}
	/* Ready to receive a new packet */
	g_is_transfer_complete = false;
}

/* use interrupts to receive a message and send a response */
ISR
(SPI_STC_vect)
{
	if (g_spi_byte_index < BYTES_IN_PACKET && g_is_transfer_complete == false) {
		/* reading SPDR causes the Shift Register Receive buffer to be read */
		unsigned char spi_receive_buffer = SPDR;
		/* determine where the read byte goes to */
		if (g_spi_byte_index == 0) {
			// First byte
			g_packet.first_byte = spi_receive_buffer;
		} else if (g_spi_byte_index >= 1 && g_spi_byte_index <= (BYTES_IN_PACKET - 1) / 2) {
			// param 1
			g_packet.param1[g_spi_byte_index - 1] = spi_receive_buffer;
		} else {
			// param 2
			g_packet.param2[g_spi_byte_index - 1 - (BYTES_IN_PACKET - 1) / 2] = spi_receive_buffer;
		}
		/* transmit the same byte back as a response
		 (writing to SPDR initiates data transmission) */
		SPDR = spi_receive_buffer;
		g_spi_byte_index++;
		/* packet transfer complete when all bytes are transferred */
		if (g_spi_byte_index == BYTES_IN_PACKET)
		{
			on_transfer_success();
		}
	} else {
		// Not ready to receive, send negative acknowledge byte back
		SPDR = NEG_ACK_BYTE;
	}
}

