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
	#include <util/delay.h>
	#include <stdlib.h>
	#include <time.h>
	#include "./lib/util.h"
	#include "./lib/buzzer.h"
	#include "./lib/slave_spi.h"
	
	// Define states
	#define AWAITING_CONNECTION 0
	#define READY 1
	#define ERROR -1
	// -------------
	
	extern void setup_slave();
	//extern void loop_slave();

#endif /* MAIN_H_ */