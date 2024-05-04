/*
 * sensor.c
 *
 * Created: 25.4.2024 18.05.16
 * Author: Vili Huusko, Jani Heinikoski, Konsta Keski-Mattinen
 */ 

#include "sensor.h"

#define SENSOR_PORT PORTL // port
#define TRIG_PIN 1 // pin for transmitting
#define ECHO_PIN 0 // pin for receiving

#define HIGH 1
#define LOW 0

#define AIR_SPEED 34300 // CM/S
#define TOLERANCE 10 // How many cm the signal has to be disturbed in order to trigger the alarm

int setup_done = 0;

int base_distance = 0; // Baseline for tolerance check

void setup() {
	if (setup_done == 0) {
		DDRL |= (1 << TRIG_PIN); // Set trig pin as OUTPUT
		DDRL &= ~(1 << ECHO_PIN); // Set echo pin as INPUT (Not needed as pins are input by default)
		setup_done = 1;
		set_base_distance();
	}
}

void set_pin(int pin, int state) {
	if (state == 1) {
		SENSOR_PORT |= (1 << pin);
	}
	else if (state == 0) {
		SENSOR_PORT &= ~(1 << pin);
	}
}

int read_pin_digital(int pin) {
	return (PINL & (1 << pin)) == (1 << pin) ;
}

void transmit() {
	set_pin(TRIG_PIN, HIGH);
	_delay_us(10);
	set_pin(TRIG_PIN, LOW);
}

int get_reading() {
	setup();
	int loops = 0;
	// Wait for previous pulse
	while (read_pin_digital(ECHO_PIN) == 1) {};
	
	int distance = 0;
	transmit();
	
	// Wait for the echo pin to become HIGH
	while (read_pin_digital(ECHO_PIN) == 0){};
	while (read_pin_digital(ECHO_PIN) == 1) {
		loops++;
	}
	// Calculate duration
	distance = (double)loops / 800000 * AIR_SPEED / 2; // 800000 clock speed
	return distance;
}

void set_base_distance() {
	base_distance = get_reading();
}

int check_motion() {
	const int dist = get_reading();
	return (dist < base_distance - TOLERANCE / 2 || dist > base_distance + TOLERANCE / 2);
}