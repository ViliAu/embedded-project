/*
 * master_spi.c
 *
 * Created: 26/04/2024 16.55.43
 * Author: Vili huusko, Jani Heinikoski, Konsta Keski-Mattinen
 * Sources:
 * Course exercise 10, ATmega2560 datasheet pp. 190-199
 */ 
#include "master_spi.h"

int g_is_setup = 0;
int g_first_byte = 1;

/* see ATmega2560 datasheet chapter 21 pp. 190-199 */
void setup_master_spi() {
	if (g_is_setup == 0) {
		/* set SS, MOSI and SCK as output, pins 53 (PB0), 51 (PB2) and 52 (PB1) */
		DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
		/* set SPI enable and master/slave select, making MEGA the master */
		SPCR |= (1 << 6) | (1 << 4);
		/* set SPI clock rate to 1 MHz */
		SPCR |= (1 << 0);
		g_is_setup = 1;
	}
}

void assemble_packet(uint8_t first_byte, char* param1, char* param2, Packet* package) {
	package->first_byte = first_byte;
	for (uint8_t i = 0; i < (BYTES_IN_PACKET - 1) / 2; i++) {
		package->param1[i] = (unsigned char) param1[i];
		if (param1[i] == '\0') {
			break;
		}
	}
	for (uint8_t i = 0; i < (BYTES_IN_PACKET - 1) / 2; i++) {
		package->param2[i] = (unsigned char) param2[i];
		if (param2[i] == '\0') {
			break;
		}
	}
}  

void packet_to_uchar_arr(Packet* src, unsigned char* dest) {
	/* first byte represents the command (zeroth index byte) */
	dest[0] = (unsigned char) src->first_byte;
	/* copy the first parameter to indices 1-32 */
	for (uint8_t i = 1; i < (BYTES_IN_PACKET - 1) / 2; i++) {
		dest[i] = (unsigned char) src->param1[i - 1];
	}
	/* copy the second parameter to indices 33-64 */
	for (uint8_t i = (BYTES_IN_PACKET - 1) / 2 + 1; i < BYTES_IN_PACKET; i++) {
		dest[i] = (unsigned char) src->param2[i - 1 - (BYTES_IN_PACKET - 1) / 2];
	}
}

/* sends a packet to the slave Arduino UNO using SPI, see ATmega2560 datasheet chapter 21 pp. 190-199 */
bool send_packet_to_slave(Packet* packet) {
	setup_master_spi();
	unsigned char spi_send_data[BYTES_IN_PACKET];
	unsigned char spi_receive_data[BYTES_IN_PACKET];
	unsigned char received_byte;
	packet_to_uchar_arr(packet, spi_send_data);
	/* begin packet transfer (drive SS on LOW) */
	PORTB &= ~(1 << PB0);
	/* transmit the packet */
	for(uint8_t spi_data_index = 0; spi_data_index < BYTES_IN_PACKET; spi_data_index++)
	{
		/* writing to the SPDR starts the SPI clock gen. and the byte is shifted into the slave */
		SPDR = spi_send_data[spi_data_index];
		_delay_us(5);
		while(!(SPSR & (1 << SPIF)))
		{
			/* wait until the transmission is complete */
			;
		}
		_delay_us(5);
		/* compare sent byte and received byte (reading SPDR causes the Shift Register Receive buffer to be read) */
		received_byte = SPDR;
		spi_receive_data[spi_data_index] = received_byte;
	}
	/* check if sent bytes match received ones (except last) */
	bool success = true;
	for (uint8_t i = 0; i < BYTES_IN_PACKET - 1; i++) {
		if (spi_send_data[i] != spi_receive_data[i+1]) {
			success = false;
		}
	}
	/* end packet transfer (drive SS on HIGH), return true/false as indication of success */
	PORTB |= (1 << PB0);
	return success;
}