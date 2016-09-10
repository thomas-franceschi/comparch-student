/*
    SIMP MIPS Pipelined Architecture Simulation Package

    2-stage MIPS pipeline pipe stage class definitions

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

#ifndef PIPE2STAGE_H_
#define PIPE2STAGE_H_

#include "global.h"
#include "Pipeline.h"
#include "Reg.h"
#include "CombLogic.h"
#include "RegFile.h"
#include "Memory.h"
#include "Cache.h"

class FetchStage : CombLogic {
    RegInstruction  &ir;
    RegUint32       &pc;
    Memory          &M;
    Cache           &iCache;
public:
    FetchStage(
        RegInstruction &_ir,
        RegUint32      &_pc,
        Memory         &_M,
        Cache          &_iCache)
    :
        ir(_ir),
        pc(_pc),
        M(_M),
        iCache(_iCache)
    {

    }
    void eval();
};

class ExecStage : CombLogic {
    RegInstruction  &ir;
    RegUint32       &pc;
    RegFile         &reg;
    unsigned        &hi;
    unsigned        &lo;
    Memory          &M;
    Cache           &dCache;
public:
    ExecStage(
        RegInstruction  &_ir,
        RegUint32       &_pc,
        RegFile         &_reg,
        unsigned        &_hi,
        unsigned        &_lo,
        Memory          &_M,
        Cache           &_dCache)
    :
        ir(_ir),
        pc(_pc),
        reg(_reg),
        hi(_hi),
        lo(_lo),
        M(_M),
        dCache(_dCache)
    {

    }
    void eval();
};

class Pipe2Stage : public Pipeline {
    RegInstruction  ir;
    FetchStage fetchStage;
    ExecStage  execStage;
public:
    Pipe2Stage(
        unsigned iAssoc,
        unsigned iLogIndex,
        unsigned iLogBlockSize,
        unsigned dAssoc,
        unsigned dLogIndex,
        unsigned dLogBlockSize)
    :
        Pipeline(iAssoc, iLogIndex, iLogBlockSize, dAssoc, dLogIndex, dLogBlockSize),
        fetchStage(ir, pc, M, iCache),
        execStage(ir, pc, reg, hi, lo, M, dCache)
    {

    }
};

#endif /* PIPE2STAGE_H_ */
