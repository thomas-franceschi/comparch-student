/*
    SIMP MIPS Pipelined Architecture Simulation Package

    MIPS instruction class definition

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

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include "global.h"

using namespace std;

enum IToken {
  ITOKEN_NONE, SLL, SRL, SRA, SLLV, SRLV, SRAV,
  JR, ADD, ADDU, SUB, SUBU, AND,
  OR, XOR, NOR, SLT, SLTU, J, JAL, JALR,
  MULT, MULTU, DIV, DIVU,
  MFHI, MTHI, MFLO, MTLO,
  BEQ, BNE, BGEZ, BGTZ, BLEZ, BLTZ,
  ADDI, ADDIU, SLTI, SLTIU, ANDI, ORI, XORI,
  LUI, LB, LH, LW, LBU, LHU, SB, SH, SW,
  SYSCALL, BREAK, NUM_ITOKEN
};

enum IFormat { IFORMAT_NONE, R_TYPE, I_TYPE, J_TYPE };
enum XType   { XTYPE_NONE, ALU, SHIFT, LOAD, STORE, BRANCH, JUMP, OTHER, NUM_XTYPE };

class Instruction {
public:
    unsigned issue_pc;
    unsigned raw;
    IFormat  format;
    XType    xtype;
    IToken   token;
    unsigned opcode;
    unsigned func;
    unsigned rs;
    unsigned rt;
    unsigned rd;
    unsigned imm;
    unsigned shamt;
    unsigned target;

    bool        regWrite;  // instruction writes to register
    unsigned    regDest;   // destination register (if regWrite)
    bool        memRead;
    bool        memWrite;
    bool        memToReg;

    static unsigned instructionCount;
    static unsigned itokenCounts[];
    static unsigned xtypeCounts[];
    static const char* ITokenName[];
    static const char* IFormatName[];
    static const char* XTypeName[];

    Instruction(unsigned machineCode);
    void print();
    string str();
    string issuePcStr();
};

#endif /* INSTRUCTION_H_ */
