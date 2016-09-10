/*
    SIMP MIPS Pipelined Architecture Simulation Package

    Global utility function and macro definitions

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

#ifndef NDSIM_GLOBAL_H_
#define NDSIM_GLOBAL_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define TEST(e) \
  if (!(e)) \
    printf("* TEST   FAIL: %s, %s line %d in %s\n", #e, __FILE__, __LINE__, __func__); \
  else \
    printf("  TEST   pass: %s, %s line %d in %s\n", #e, __FILE__, __LINE__, __func__);

#define TESTEQ(act, exp) \
  if ((exp) == (act)) \
    cout << "  TESTEQ pass: " << __FILE__ << " line " << dec << __LINE__ << " in " << __func__ << endl; \
  else \
    cout << "* TESTEQ FAIL: " << __FILE__ << " line " << dec << __LINE__ << " in " << __func__ << \
      " EXPECTED= " << dec << exp << "/" << hex << "0x" << exp << \
      " ACTUAL= " << dec << act << "/" << hex << "0x" << act << endl;

unsigned bitRange(unsigned word, unsigned hi, unsigned lo);
unsigned signExtend8(unsigned n);
unsigned signExtend16(unsigned n);
unsigned zeroExtend16(unsigned n);

#endif /* NDSIM_GLOBAL_H_ */
