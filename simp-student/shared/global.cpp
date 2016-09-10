/*
    SIMP MIPS Pipelined Architecture Simulation Package

    Global utility function implementation

    Copyright (C) 2016  Jay B. Brockman

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "global.h"

/*
 * This function should operate on the 32-bit raw value
 * and return a value consisting of the range of bits
 * between bit positions hi and lo, inclusive
 */
unsigned bitRange(unsigned word, unsigned hi, unsigned lo) {
    return (word << (31 - hi)) >> (31 - hi + lo);
}

/*
 * This function should sign extend the 8-bit value n
 * to 32 bits and return it
 */
unsigned signExtend8(unsigned n) {
    return (((int) n << 24) >> 24);
}

/*
 * This function should sign extend the 16-bit value n
 * to 32 bits and return it
 */
unsigned signExtend16(unsigned n) {
    return (((int) n << 16) >> 16);
}

unsigned zeroExtend16(unsigned n) {
    return ((n << 16) >> 16);
}
