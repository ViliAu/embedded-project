/*
 * main.h
 *
 * Created: 27.4.2024 18.29.54
 *  Author: Vili
 */ 


#ifndef MAIN_H_
#define MAIN_H_
	
	#define F_CPU 16000000UL
	
	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdio.h>
	#include <string.h>
	#include "lib/master_spi.h"
	#include "lib/sensor.h"
	#include "lib/keypad.h"
	
	// states
	#define INITIALIZE 0
	#define DISARMED 1
	#define ARMED 2
	#define TRIGGERED 3
	#define SET_PSWD 4
	#define ERROR -1
	// -----
	
	void setup_master();
	void loop_master();
	void write_slave_lcd(char* l1, char* l2);

#endif /* MAIN_H_ */