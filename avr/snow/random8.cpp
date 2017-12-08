/* File: main.cpp
 * Contains base main function and usually all the other stuff that avr does...
 */
/* Copyright (c) 2012-2013 Domen Ipavec (domen.ipavec@z-v.si)
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

#include "random8.h"

#include <avr/pgmspace.h>

static uint8_t y8 = 1;
static const int8_t d_normal[] PROGMEM = {-127, -111, -103, -97, -93, -89, -86, -83, -81, -79, -77, -75, -73, -71, -70, -68, -67, -66, -64, -63, -62, -61, -60, -59, -58, -57, -56, -55, -54, -53, -52, -51, -50, -49, -49, -48, -47, -46, -46, -45, -44, -43, -43, -42, -41, -41, -40, -39, -39, -38, -37, -37, -36, -36, -35, -34, -34, -33, -33, -32, -32, -31, -31, -30, -29, -29, -28, -28, -27, -27,-26, -26, -25, -25, -24, -24, -23, -23, -22, -22, -21, -21, -20, -20, -19, -19, -18, -18, -17, -17, -17, -16, -16, -15, -15, -14, -14, -13, -13, -12, -12, -12, -11, -11, -10, -10, -9, -9, -8, -8, -8, -7, -7, -6, -6, -5, -5, -5, -4, -4,-3, -3, -2, -2, -2, -1, -1, 0, 0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 5, 6, 6, 7, 7, 8, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 31, 31, 32, 32, 33, 33, 34, 34, 35, 36, 36, 37, 37, 38, 39, 39, 40, 41, 41, 42, 43, 43, 44, 45, 46, 46, 47, 48, 49, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68, 70, 71, 73, 75, 77, 79, 81, 83, 86, 89, 93, 97, 103, 111, 127};

uint8_t random8() {
	y8 ^= (y8 << 7);
	y8 ^= (y8 >> 5);
	return y8 ^= (y8 << 3);
}

uint8_t random8_uniform(uint8_t max) {
	return random8() % max;
}

int8_t random8_normal() {
	return pgm_read_byte(&d_normal[random8()]);
}
