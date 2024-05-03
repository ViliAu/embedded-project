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
	#include <stdbool.h>
	#include "./lib/util.h"
	#include "./lib/buzzer.h"
	#include "./lib/slave_spi.h"
	
	#define INIT_STATE 0
	#define OK_STATE 1
	
	#define CHECK_CONN_BYTE 'c'
	#define CHECK_CONN_TIMEOUT_SECONDS 10
	
	bool initialize();
	bool check_connection();

#endif /* MAIN_H_ */