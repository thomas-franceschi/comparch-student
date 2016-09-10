/*
    SIMP MIPS Pipelined Architecture Simulation Package

    Pipeline parent class definition

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

#ifndef PIPELINE_H_
#define PIPELINE_H_

#include "global.h"
#include "Reg.h"
#include "CombLogic.h"
#include "RegFile.h"
#include "Memory.h"
#include "Cache.h"

class Pipeline {
protected:
    RegUint32 pc;
    RegFile reg;
    unsigned lo;
    unsigned hi;
    Memory M;
    Cache iCache;
    Cache dCache;
public:
    static bool continueExec;
    static bool verbose;
    static bool verboseIcache;
    static bool verboseDcache;
    static int  forwardingLevel;
    static int  loadStalls;
    static int  controlStalls;

    Pipeline(
        unsigned iAssoc,
        unsigned iLogIndex,
        unsigned iLogBlockSize,
        unsigned dAssoc,
        unsigned dLogIndex,
        unsigned dLogBlockSize)
    :
        hi(0),
        lo(0),
        iCache(M, iAssoc, iLogIndex, iLogBlockSize),
        dCache(M, dAssoc, dLogIndex, dLogBlockSize)
    {

    }
    void printRegsHex();
    void printRegsDec();
    void listCode();
    void run(char *elfFileName);
    void runInteractive(char *elfFileName);
    void outputStats();
};

#endif /* PIPELINE_H_ */
