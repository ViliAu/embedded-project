/*
 * sensor.c
 *
 * Created: 25.4.2024 18.05.16
 *  Author: Vili Huusko, Jani Heinikoski, Konsta Keski-Mattila
 */ 

#include "sensor.h"

#define sensor_DD DDRL // data direction
#define sensor_PORT PORTL // port
#define trig_PIN 2 // pin for transmitting
#define echo_PIN 3 // pin for receiving

#define HIGH 1
#define LOW 0

#define AIR_SPEED 34600 // CM/S
#define TOLERANCE 10 // How many cm the signal has to be disturbed in order to trigger the alarm

int setup_done = 0;

double base_distance = 0; // Baseline for tolerance check

void setup() {
	if (setup_done == 0) {
		DDRL |= (1 << trig_PIN); // Set trig pin as OUTPUT
		DDRL &= ~(1 << echo_PIN); // Set echo pin as INPUT (Not needed as pins are input by default)
		setup_done = 1;
		set_base_distance();
	}
}

void set_pin(int pin, int state) {
	if (state == 1) {
		sensor_PORT |= (1 << pin);
	}
	else if (state == 0) {
		sensor_PORT &= ~(1 << pin);
	}
}

int read_pin_digital(int pin) {
	return ((PORTL & (1 << pin)) == (1 << pin));
}

void transmit() {
	set_pin(trig_PIN, HIGH);
	_delay_us(10);
	set_pin(trig_PIN, LOW);
}

double get_reading() {
	setup();
	
	// Wait for previous pulse
	while (read_pin_digital(echo_PIN) == 1);
	
	long loops = 0;
	double distance = 0;
	transmit();
	
	// Wait for the echo pin to become HIGH
	while (read_pin_digital(echo_PIN) == 0);
	while (read_pin_digital(echo_PIN) == 1) {
		loops++;
	}
	// Calculate duration
	distance = loops / F_CPU * AIR_SPEED / 2;
	return distance;
}

void set_base_distance() {
	base_distance = get_reading();
}

int check_motion() {
	const double dist = get_reading();
	return (dist < base_distance - TOLERANCE / 2 || dist > base_distance + TOLERANCE / 2);
}