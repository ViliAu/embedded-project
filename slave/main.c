/*
 * slave.c
 *
 * Created: 18.3.2024 18.03.27
 * Authors : Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "./lib/util.h" 

int
main(void)
{
	char c_char[2];
	int buzzer = 0;
	DDRD |= (1 << DDD2);
	int c = 10;
	while(1)
	{
		_delay_ms(1000);
		itoa(c, c_char, 10);
		write_lcd("moi", c_char);
		if (c > 0)
		{
			c--;
		}
		else {
			buzzer = !buzzer;
			if (!buzzer)
			{
				PORTD |= (1 << PD2);
			}
			else
			{
				PORTD &= ~(1 << PD2);
			}
		}
	}
	
	return 0;
}

