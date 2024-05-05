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
	#include <stdlib.h>
	#include "lib/master_spi.h"
	#include "lib/sensor.h"
	#include "lib/keypad.h"
	#include "lib/password_manager.h"
	
	#define ERROR_PORT PORTD
	#define ERROR_PIN 7
	
	// states
	#define INITIALIZE 0
	#define DISARMED 1
	#define ARMED 2
	#define TRIGGERED 3
	#define ALARM_PASSWORD 4
	#define ALARM_COUNTDOWN 5
	#define SET_PSWD 6
	#define ERROR -1
	// -----
	
	void setup_master();
	void loop_master();
	void try_pswd(char c);
	void handle_disarmed(char c);
	void handle_armed(char c);
	void handle_triggered(char c);
	void handle_alarm(char c);
	void handle_set_pswd(char c);
	void init_connection();
	void write_slave_lcd(char* l1, char* l2);
	void toggle_buzzer(int b);

#endif /* MAIN_H_ */