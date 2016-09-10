/*
    SIMP MIPS Pipelined Architecture Simulation Package

    5-stage MIPS pipeline pipe stage class definitions

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

#ifndef PIPE5STAGE_H_
#define PIPE5STAGE_H_

#include "global.h"
#include "Pipeline.h"
#include "Reg.h"
#include "CombLogic.h"
#include "RegFile.h"
#include "Memory.h"
#include "Cache.h"

//
// Pipeline Registers
//

struct IF_ID {
    RegInstruction  ir;
};

struct ID_EX {
    RegInstruction  ir;
    RegUint32       regData1;
    RegUint32       regData2;
    RegUint32       immSignExt;
    RegUint32       immZeroExt;
    RegUint32       linkPc;
};

struct EX_MEM {
    RegInstruction  ir;
    RegUint32       aluOut;
    RegUint32       writeData;
};

struct MEM_WB {
    RegInstruction  ir;
    RegUint32       wbData;
};

//
// Pipeline Stages Combinational Logic
//

class IfStage : CombLogic {
    IF_ID       &if_id;
    RegUint32   &pc;
    Memory      &M;
    Cache       &iCache;
public:
    IfStage(
        IF_ID       &_if_id,
        RegUint32   &_pc,
        Memory      &_M,
        Cache       &_iCache)
    :
        if_id(_if_id),
        pc(_pc),
        M(_M),
        iCache(_iCache)
    {

    }
    void eval();
};

class IdStage : CombLogic {
    IF_ID       &if_id;
    ID_EX       &id_ex;
    EX_MEM      &ex_mem;
    MEM_WB      &mem_wb;
    RegUint32   &pc;
    RegFile     &reg;
public:
    IdStage(
        IF_ID       &_if_id,
        ID_EX       &_id_ex,
        EX_MEM      &_ex_mem,
        MEM_WB      &_mem_wb,
        RegUint32   &_pc,
        RegFile     &_reg)
    :
        if_id(_if_id),
        id_ex(_id_ex),
        ex_mem(_ex_mem),
        mem_wb(_mem_wb),
        pc(_pc),
        reg(_reg)
    {

    }
    void eval();
};

class ExStage : CombLogic {
    ID_EX       &id_ex;
    EX_MEM      &ex_mem;
    MEM_WB      &mem_wb;
    unsigned    &hi;
    unsigned    &lo;
public:
    ExStage(
        ID_EX       &_id_ex,
        EX_MEM      &_ex_mem,
        MEM_WB      &_mem_wb,
        unsigned    &_hi,
        unsigned    &_lo)
    :
        id_ex(_id_ex),
        ex_mem(_ex_mem),
        mem_wb(_mem_wb),
        hi(_hi),
        lo(_lo)
    {

    }
    void eval();
};

class MemStage : CombLogic {
    EX_MEM      &ex_mem;
    MEM_WB      &mem_wb;
    Memory      &M;
    Cache       &dCache;
public:
    MemStage(
        EX_MEM      &_ex_mem,
        MEM_WB      &_mem_wb,
        Memory      &_M,
        Cache       &_dCache)
    :
        ex_mem(_ex_mem),
        mem_wb(_mem_wb),
        M(_M),
        dCache(_dCache)
    {

    }
    void eval();
};

class WbStage : CombLogic {
    MEM_WB      &mem_wb;
    RegFile     &reg;
public:
    WbStage(
        MEM_WB      &_mem_wb,
        RegFile     &_reg)
    :
        mem_wb(_mem_wb),
        reg(_reg)
    {

    }
    void eval();
};

class Pipe5Stage : public Pipeline {
    IF_ID       if_id;
    ID_EX       id_ex;
    EX_MEM      ex_mem;
    MEM_WB      mem_wb;
    IfStage     ifStage;
    IdStage     idStage;
    ExStage     exStage;
    MemStage    memStage;
    WbStage     wbStage;
public:
    Pipe5Stage(
        unsigned iAssoc,
        unsigned iLogIndex,
        unsigned iLogBlockSize,
        unsigned dAssoc,
        unsigned dLogIndex,
        unsigned dLogBlockSize)
    :
        Pipeline(iAssoc, iLogIndex, iLogBlockSize, dAssoc, dLogIndex, dLogBlockSize),
        ifStage(if_id, pc, M, iCache),
        idStage(if_id, id_ex, ex_mem, mem_wb, pc, reg),
        exStage(id_ex, ex_mem, mem_wb, hi, lo),
        memStage(ex_mem, mem_wb, M, dCache),
        wbStage(mem_wb, reg)
    {

    }
};

#endif /* PIPE5STAGE_H_ */
