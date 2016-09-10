/*
    SIMP MIPS Pipelined Architecture Simulation Package

    Combinational logic parent class definition

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

#ifndef COMBLOGIC_H_
#define COMBLOGIC_H_

#include <stdint.h>
#include <iostream>
#include <set>

using namespace std;

class CombLogic {
    static set<CombLogic *> instances;
public:
    CombLogic();
    static void evalAll();
    virtual void eval() = 0;
    virtual ~CombLogic();
};

#endif /* REGISTER_TRANSFER_COMBLOGIC_H_ */
