/*
 * sensor.h
 *
 * Created: 25.4.2024 18.06.45
 * Author: Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 


#ifndef SENSOR_H_
#define SENSOR_H_
	
	#define F_CPU 16000000UL
		
	#include <avr/io.h>
	#include <util/delay.h>
	
	void setup();
	void set_pin(int pin, int state);
	int read_pin_digital(int pin);
	void transmit();
	int get_reading();
	void set_base_distance();
	int check_motion();

#endif /* SENSOR_H_ */