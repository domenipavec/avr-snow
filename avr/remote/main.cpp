/* File: main.cpp
 * Contains base main function and usually all the other stuff that avr does...
 */
/* Copyright (c) 2017 Domen Ipavec (domen@ipavec.net)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

//#include <util/delay.h>

#include <avr/io.h>
// #include <avr/interrupt.h>
// #include <avr/pgmspace.h>
// #include <avr/eeprom.h>
#include <util/delay.h>

#include <stdint.h>

#include "bitop.h"
// #include "io.h"
// #include "random8.h"

// CONFIG
static const uint8_t SNOW_SMALL = 100;
static const uint8_t SNOW_BIG = 15;

#define NULL 0

void send_byte(uint8_t v) {
	while (BITCLEAR(UCSR0A, UDRE0));
	UDR0 = v;
}

void send_packet(uint8_t address, uint8_t *data, uint8_t data_len) {
	send_byte((address & 0xf) | (data_len << 4));
	for (uint8_t i = 0; i < data_len; i++) {
		send_byte(data[i]);
	}
}

void change_to_snow() {
	send_packet(0xb, NULL, 0);
}

void change_to_stars() {
	send_packet(0xc, NULL, 0);
}

void set_speed(uint8_t s) {
	uint8_t buffer[2];
	buffer[0] = 0;
	buffer[1] = s;
	send_packet(0xd, buffer, 2);
}

int main() {
	// init

	// enable pull up for buttons
	SETBIT(PUEA, PA4);
	SETBIT(PUEA, PA6);

	// uart init
	// enable send
	UCSR0B = BIT(TXEN0);
	// 8 bits
	UCSR0C = BIT(UCSZ01) | BIT(UCSZ00);
	// 19200 baud rate
	UBRR0 = 25;

	for (uint16_t i = 0; i < 3000; i++) {
		_delay_ms(1);
	}

	uint8_t snow = 1;
	uint8_t big = 0;
	set_speed(SNOW_SMALL);

	for (;;) {
		if (BITSET(PINA, PA4) && !snow) {
			snow = 1;
			change_to_snow();
		}
		if (BITCLEAR(PINA, PA4) && snow) {
			snow = 0;
			change_to_stars();
		}
		if (BITSET(PINA, PA6) && !big) {
			big = 1;
			set_speed(SNOW_BIG);
		}
		if (BITCLEAR(PINA, PA6) && big) {
			big = 0;
			set_speed(SNOW_SMALL);
		}

		for (uint8_t i = 0; i < 100; i++) {
			_delay_ms(1);
		}
	}
}



