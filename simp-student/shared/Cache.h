/*
    SIMP MIPS Pipelined Architecture Simulation Package

    Cache class definition

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

#ifndef CACHE_H_
#define CACHE_H_

#include "global.h"
#include "Memory.h"

class Cache {
    Memory          &M;
    unsigned        logBlockSize;
    unsigned        logIndex;
    unsigned        setSize;
    unsigned        **tagArray;
    bool            **validArray;
    bool            **dirtyArray;
    unsigned        **lastUsedArray;
    uint8_t         ***dataArray;
    string          accessString;
public:
    unsigned        accesses;
    unsigned        hits;
    bool            verbose;

    Cache(Memory &_M, unsigned _setSize, unsigned _logIndex, unsigned _logBlockSize);
    void        find(uint32_t addr, unsigned &tag, unsigned &way, unsigned &index, unsigned &offset, bool &hit);
    uint32_t    read(unsigned size, uint32_t addr);
    void        write(unsigned size, uint32_t addr, uint32_t data);
    void        flush();
    string&     str()   { return accessString; }
    void        print();
private:
    void            formatAccessString(const char* rw, bool hit, uint32_t addr, uint32_t data, unsigned size,
                        unsigned tag, unsigned way, unsigned index, unsigned offset);
};

#endif /* CACHE_H_ */
