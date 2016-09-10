/*
    SIMP MIPS Pipelined Architecture Simulation Package

    Cache class implementation

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

#include "Cache.h"

Cache::Cache(Memory &_M, unsigned _setSize, unsigned _logIndex, unsigned _logBlockSize)
: M             (_M),
  setSize       (_setSize),
  logIndex      (_logIndex),
  logBlockSize  (_logBlockSize),
  accesses      (0),
  hits          (0),
  verbose       (false)
{
    if (setSize == 0)
        return;

    tagArray = new unsigned* [setSize];
    validArray = new bool* [setSize];
    dirtyArray = new bool* [setSize];
    lastUsedArray = new unsigned* [setSize];

    for (int i = 0;  i < setSize;  i++) {
        tagArray[i] = new unsigned[1<<logIndex];
        validArray[i] = new bool[1<<logIndex];
        dirtyArray[i] = new bool[1<<logIndex];
        lastUsedArray[i] = new unsigned[1<<logIndex];
    }

    dataArray = new uint8_t** [setSize];
    for (int i = 0;  i < setSize;  i++) {
        dataArray[i] = new uint8_t* [1<<logIndex];
        for (int j = 0;  j < (1<<logIndex);  j++)
            dataArray[i][j] = new uint8_t[1<<logBlockSize];
    }

    for (int w = 0;  w < setSize;  w++)
        for (int i = 0;  i < 1<<logIndex;  i++) {
            validArray[w][i] = false;
            dirtyArray[w][i] = false;
        }
}

void Cache::find(uint32_t addr, unsigned &tag, unsigned &way, unsigned &index, unsigned &offset, bool &hit) {

    assert(setSize == 0 && "Cache::find not yet implemented");

    /*
     * Implement the protocol for an associative cache here
     */

}

uint32_t Cache::read(unsigned size, uint32_t addr) {
    unsigned tag, way, index, offset;
    bool hit;
    uint8_t *dataPtr;
    uint32_t returnData;

    if (setSize == 0) {
        dataPtr = M.getMemoryPtr(addr);
    }
    else {
        // read the data word from the cache according to size and return
        find(addr, tag, way, index, offset, hit);
        dataPtr = &dataArray[way][index][offset];
    }

    switch (size) {
    case 8:
        returnData = *dataPtr;
        break;
    case 16:
        returnData = *((uint16_t *) dataPtr);
        break;
    case 32:
        returnData = *((uint32_t *) dataPtr);
        break;
    default:
        assert(false && "unknown size");
    }

    formatAccessString("read ", hit, addr, returnData, size, tag, way, index, offset);
    if (verbose)
        cout << accessString << endl;
    return returnData;
}

void Cache::write(unsigned size, uint32_t addr, uint32_t data) {
    unsigned tag, way, index, offset;
    bool hit;
    uint8_t *dataPtr;

    if (setSize == 0) {
        dataPtr = M.getMemoryPtr(addr);
    }
    else {
        // read the data word from the cache according to size and return
        find(addr, tag, way, index, offset, hit);
        dataPtr = &dataArray[way][index][offset];
    }

    switch (size) {
    case 8:
        *dataPtr = data;
        break;
    case 16:
        *((uint16_t *) dataPtr) = data;
        break;
    case 32:
        *((uint32_t *) dataPtr) = data;
        break;
    default:
        assert(false && "unknown size");
    }
    if (setSize != 0)
        dirtyArray[way][index] = true;

    formatAccessString("write", hit, addr, data, size, tag, way, index, offset);
    if (verbose)
        cout << accessString << endl;
}

void Cache::flush() {
    for (int w = 0;  w < setSize;  w++) {
        for (int i = 0;  i < (1<<logIndex);  i++) {
            if (dirtyArray[w][i]) {
                uint8_t *cacheBlockPtr = dataArray[w][i];
                uint32_t memAddr = ((tagArray[w][i] << logIndex) | i) << logBlockSize;
                uint8_t *memBlockPtr = M.getMemoryPtr(memAddr);
                memcpy(memBlockPtr, cacheBlockPtr, 1<<logBlockSize);
            }
        }
    }
}

void Cache::print() {
    printf("   index  ");
    for (int w = 0;  w < setSize;  w++)
        printf("     way%d ", w);
    printf("\n");
    for (int i = 0;  i < (1<<logIndex);  i++) {
        printf("%8x: ", i);
        for (int w = 0;  w < setSize;  w++) {
            if (dirtyArray[w][i])
                printf("*");
            else
                printf(" ");
            if (validArray[w][i])
                printf("%8x ", tagArray[w][i]);
            else
                printf("         ");
        }
        printf("\n");
    }
}

void Cache::formatAccessString(const char* rw, bool hit, uint32_t addr, uint32_t data, unsigned size,
        unsigned tag, unsigned way, unsigned index, unsigned offset) {
    char buf[256];
    if (setSize == 0) {
        sprintf(buf, "memory %s (%2d):  %08x  data = 0x%x", rw, size, addr, data);
    }
    else {
        int n = sprintf(buf, "cache %s (%2d):  %08x  ", rw, size, addr);
        if (hit)
            n += sprintf(buf+n, "hit\t");
        else
            n += sprintf(buf+n, "miss\t");
        sprintf(buf+n, "tag = 0x%x  index = %2d  offset = %2d  way = %2d  data = 0x%x",
                tag, index, offset, way, data);
    }
    accessString = string(buf);
}
