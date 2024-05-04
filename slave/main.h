/*
 * main.h
 *
 * Created: 7.4.2024 14.20.19
 *  Author: Vili
 */ 


#ifndef MAIN_H_
#define MAIN_H_

	#define F_CPU 16000000UL

	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <avr/sleep.h>
	#include <util/delay.h>
	#include <stdlib.h>
	#include <stdbool.h>
	
	#include "./lib/util.h"
	#include "./lib/buzzer.h"
	#include "./lib/slave_spi.h"
	
	void sleep_until_new_msg();

#endif /* MAIN_H_ */