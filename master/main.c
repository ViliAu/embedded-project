/*
 * master.c
 *
 * Created: 18.3.2024 18.03.05
 * Authors : Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "lib/master_spi.h"

int g_switch = 0;

void random_packet(Packet* p) {
	assemble_packet('k', "  moikka\0", "  maailma\0", p);
	
	if (g_switch == 0) {
		g_switch = 1;
		p->param1[0] = 'd';
		p->param2[0] = 'd';
		} else {
		g_switch = 0;
		p->param1[0] = 'e';
		p->param2[0] = 'e';
	}
}

int main(void)
{
	Packet p;
	random_packet(&p);
	
    /* Replace with your application code */
    while (1) 
    {
		_delay_ms(2500);
		send_packet_to_slave(&p);
		random_packet(&p);
    }
}

