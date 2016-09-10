/*
    SIMP MIPS Pipelined Architecture Simulation Package

    Clocked register parent class definition and subclass implementation

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

#ifndef REG_H_
#define REG_H_

#include <stdint.h>
#include <iostream>
#include <set>
#include <string>
#include "global.h"
#include "Instruction.h"

using namespace std;

class Reg {
	static set<Reg *> instances;
protected:
    bool stalled;
public:
	Reg();
	static void clockAll();
	virtual void clock() = 0;
	void stall()  { stalled = true; }
	virtual ~Reg();
};

class RegUint32 : public Reg {
public:
	uint32_t	d;
	uint32_t	q;
    RegUint32() : d(0), q(0) { }
	void		clock()	{ if (!stalled) q = d; stalled = false; }
};

class RegInstruction : public Reg {
public:
    Instruction *d;
    Instruction *q;
    RegInstruction() : d(0), q(new Instruction(0)) { }
    void    clock() { if (!stalled) q = d; stalled = false; }
};

#endif /* REG_H_ */
