/*
    SIMP MIPS Pipelined Architecture Simulation Package

    Clocked register parent class implementation

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

#include "Reg.h"

set<Reg *> Reg::instances;

Reg::Reg() : stalled(false) {
	instances.insert(this);
}

void Reg::clockAll() {
	for (set<Reg *>::iterator it = instances.begin();
		 it != instances.end();
		 it++) {
	    (*it)->clock();
	}
}

Reg::~Reg() {
	instances.erase(this);
}


