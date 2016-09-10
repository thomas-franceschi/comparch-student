/*
    SIMP MIPS Pipelined Architecture Simulation Package

    Memory class definition

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

#ifndef NDSIM_MEMORY_H_
#define NDSIM_MEMORY_H_

#include "global.h"
#include <map>

class Memory {
  uint8_t*  textMemory;
  unsigned  textSize;
  unsigned  textBase;
  unsigned  textBound;
  uint8_t*  dataMemory;
  unsigned  dataSize;
  unsigned  dataBase;
  unsigned  dataBound;
  uint8_t*  heapMemory;
  unsigned  heapSize;
  unsigned  heapBase;
  unsigned  heapBound;
  uint8_t*  stackMemory;
  unsigned  stackSize;
  unsigned  stackBound;
  unsigned  stackBase;
  uint32_t  mainAddr;
  uint32_t  initPc;
  uint32_t  initSp;
  uint32_t  initGp;

  map<string, uint32_t> symbolTable;

public:
  Memory(unsigned tSize = (1<<20),
         unsigned dSize = (1<<20),
         unsigned hSize = (1<<20),
         unsigned sSize = (1<<20));

  void      loadText(void *source, unsigned numBytes);
  void      loadData(void *source, unsigned numBytes);
  void      readSpimLogFile(char *filename);
  void      readElfFile(char *filename);
  uint32_t  read(unsigned size, uint32_t addr);
  void      write(unsigned size, uint32_t addr, uint32_t data);
  unsigned  alloc(unsigned n);
  uint32_t  getSymbolAddr(char *symbol);
  uint32_t  getInitPc()  { return initPc; }
  uint32_t  getInitSp()  { return initSp; }
  uint32_t  getInitGp()  { return initGp; }
  uint8_t*  getMemoryPtr(unsigned addr);
  virtual   ~Memory();
};

#endif /* NDSIM_MEMORY_H_ */
