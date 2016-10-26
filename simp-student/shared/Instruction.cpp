/*
    SIMP MIPS Pipelined Architecture Simulation Package

    MIPS instruction class implementation

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

#include "Instruction.h"
#include "RegFile.h"
#include "Memory.h"
#include <iomanip>

unsigned Instruction::instructionCount;
unsigned Instruction::nopCount;
unsigned Instruction::itokenCounts[NUM_ITOKEN];
unsigned Instruction::xtypeCounts[NUM_XTYPE];

const char* Instruction::ITokenName[] = {
    "NONE", "sll", "srl", "sra", "sllv", "srlv", "srav",
    "jr", "add", "addu", "sub", "subu", "and",
    "or", "xor", "nor", "slt", "sltu", "j", "jal", "jalr",
    "mult", "multu", "div", "divu",
    "mfhi", "mthi", "mflo", "mtlo",
    "beq", "bne", "bgez", "bgtz", "blez", "bltz",
    "addi", "addiu", "slti", "sltiu", "andi", "ori", "xori",
    "lui", "lb", "lh", "lw", "lbu", "lhu", "sb", "sh", "sw",
    "syscall", "break"
};

const char* Instruction::IFormatName[] = { "NONE", "R_TYPE", "I_TYPE", "J_TYPE" };
const char* Instruction::XTypeName[] =   { "NONE", "ALU", "SHIFT", "LOAD", "STORE", "BRANCH", "JUMP", "OTHER" };

/*
 * This procedure should decode the 32-bit instruction
 * machineCode and instantiate it as an Instruction object
 * The decoding process includes extracting values from the
 * machineCode instruction for the opcode, func, rs, rt, rd,
 * shamt, imm, and target fields, as well as assigning a format,
 * token, and execution type (xtype)
 */
Instruction::Instruction(unsigned machineCode)
: issue_pc    (0),
  raw         (machineCode),
  opcode      (bitRange(raw, 31, 26)),
  func        (bitRange(raw, 5,  0)),
  rs          (bitRange(raw, 25, 21)),
  rt          (bitRange(raw, 20, 16)),
  rd          (bitRange(raw, 15, 11)),
  shamt       (bitRange(raw, 10, 6)),
  imm         (bitRange(raw, 15, 0)),
  target      (bitRange(raw, 25, 0)),
  regWrite    (false),
  regDest     (0),
  memRead     (false),
  memWrite    (false),
  memToReg    (false)
{
  switch (opcode) {
  case 0:
    format = R_TYPE;
    switch(func) {
    case 0:
      token = SLL;
      xtype = SHIFT;
      regWrite = true;
      regDest = rd;
      break;
    case 2:
      token = SRL;
      xtype = SHIFT;
      regWrite = true;
      regDest = rd;
      break;
    case 3:
      token = SRA;
      xtype = SHIFT;
      regWrite = true;
      regDest = rd;
      break;
    case 4:
      token = SLLV;
      xtype = SHIFT;
      regWrite = true;
      regDest = rd;
      break;
    case 6:
      token = SRLV;
      xtype = SHIFT;
      regWrite = true;
      regDest = rd;
      break;
    case 7:
      token = SRAV;
      xtype = SHIFT;
      regWrite = true;
      regDest = rd;
      break;
    case 8:
      token = JR;
      xtype = JUMP;
      break;
    case 9:
      token = JALR;
      xtype = JUMP;
      regWrite = true;
      regDest = rd;
      break;
    case 12:
      // This is a very special case (and somewhat of a hack)!!
      // Note that SYSCALL may write a value to register $2
      // depending on the code (also contained in $2).  The
      // code can only be known at run time.  If SYSCALL does
      // write back to a register regWrite and regDest will
      // be changed at run time.
      token = SYSCALL;
      xtype = OTHER;
      rs = 2;
      rt = 4;
      break;
    case 13:
      token = BREAK;
      xtype = OTHER;
      break;
    case 16:
      token = MFHI;
      xtype = ALU;
      regWrite = true;
      regDest = rd;
      break;
    case 17:
      token = MTHI;
      xtype = ALU;
      break;
    case 18:
      token = MFLO;
      xtype = ALU;
      regWrite = true;
      regDest = rd;
      break;
    case 19:
      token = MTLO;
      xtype = ALU;
      break;
    case 24:
      token = MULT;
      xtype = ALU;
      break;
    case 25:
      token = MULTU;
      xtype = ALU;
      break;
    case 26:
      token = DIV;
      xtype = ALU;
      break;
    case 27:
      token = DIVU;
      xtype = ALU;
      break;
    case 32:
      token = ADD;
      xtype = ALU;
      regWrite = true;
      regDest = rd;
      break;
    case 33:
      token = ADDU;
      xtype = ALU;
      regWrite = true;
      regDest = rd;
      break;
    case 34:
      token = SUB;
      xtype = ALU;
      regWrite = true;
      regDest = rd;
      break;
    case 35:
      token = SUBU;
      xtype = ALU;
      regWrite = true;
      regDest = rd;
      break;
    case 36:
      token = AND;
      xtype = ALU;
      regWrite = true;
      regDest = rd;
      break;
    case 37:
      token = OR;
      xtype = ALU;
      regWrite = true;
      regDest = rd;
      break;
    case 38:
      token = XOR;
      xtype = ALU;
      regWrite = true;
      regDest = rd;
      break;
    case 39:
      token = NOR;
      xtype = ALU;
      regWrite = true;
      regDest = rd;
      break;
    case 42:
      token = SLT;
      xtype = ALU;
      regWrite = true;
      regDest = rd;
      break;
    case 43:
      token = SLTU;
      xtype = ALU;
      regWrite = true;
      regDest = rd;
      break;
    default:
      printf("unknown func:  raw=%08x  opcode=%u  func=%u\n", raw, opcode, func);
      assert(false && "unknown func");
    }
    break;
  case 1:
    format = I_TYPE;
    xtype = BRANCH;
    switch (rt) {
    case 0:
      token = BLTZ;
      break;
    case 1:
      token = BGEZ;
      break;
    default:
      printf("unknown opcode 1 subtype: raw=%08x  rt=%u\n", raw, rt);
      assert(false && "unknown opcode 1 subtype");
      break;
    }
    break;
  case 2:
    token = J;
    format = J_TYPE;
    xtype = JUMP;
    break;
  case 3:
    token = JAL;
    format = J_TYPE;
    xtype = JUMP;
    regWrite = true;
    regDest = 31;
    break;
  case 4:
    token = BEQ;
    format = I_TYPE;
    xtype = BRANCH;
    break;
  case 5:
    token = BNE;
    format = I_TYPE;
    xtype = BRANCH;
    break;
  case 6:
    token = BLEZ;
    format = I_TYPE;
    xtype = BRANCH;
    break;
  case 7:
    token = BGTZ;
    format = I_TYPE;
    xtype = BRANCH;
    break;
  case 8:
    token = ADDI;
    format = I_TYPE;
    xtype = ALU;
    regWrite = true;
    regDest = rt;
    break;
  case 9:
    token = ADDIU;
    format = I_TYPE;
    xtype = ALU;
    regWrite = true;
    regDest = rt;
    break;
  case 10:
    token = SLTI;
    format = I_TYPE;
    xtype = ALU;
    regWrite = true;
    regDest = rt;
    break;
  case 11:
    token = SLTIU;
    format = I_TYPE;
    xtype = ALU;
    regWrite = true;
    regDest = rt;
    break;
  case 12:
    token = ANDI;
    format = I_TYPE;
    xtype = ALU;
    regWrite = true;
    regDest = rt;
    break;
  case 13:
    token = ORI;
    format = I_TYPE;
    xtype = ALU;
    regWrite = true;
    regDest = rt;
    break;
  case 14:
    token = XORI;
    format = I_TYPE;
    xtype = ALU;
    regWrite = true;
    regDest = rt;
    break;
  case 15:
    token = LUI;
    format = I_TYPE;
    xtype = ALU;
    regWrite = true;
    regDest = rt;
    break;
  case 32:
    token = LB;
    format = I_TYPE;
    xtype = LOAD;
    regWrite = true;
    regDest = rt;
    memRead = true;
    memToReg = true;
    break;
  case 33:
    token = LH;
    format = I_TYPE;
    xtype = LOAD;
    regWrite = true;
    regDest = rt;
    memRead = true;
    memToReg = true;
    break;
  case 35:
    token = LW;
    format = I_TYPE;
    xtype = LOAD;
    regWrite = true;
    regDest = rt;
    memRead = true;
    memToReg = true;
    break;
  case 36:
    token = LBU;
    format = I_TYPE;
    xtype = LOAD;
    regWrite = true;
    regDest = rt;
    memRead = true;
    memToReg = true;
    break;
  case 37:
    token = LHU;
    format = I_TYPE;
    xtype = LOAD;
    regWrite = true;
    regDest = rt;
    memRead = true;
    memToReg = true;
    break;
  case 40:
    token = SB;
    format = I_TYPE;
    xtype = STORE;
    memWrite = true;
    break;
  case 41:
    token = SH;
    format = I_TYPE;
    xtype = STORE;
    memWrite = true;
    break;
  case 43:
    token = SW;
    format = I_TYPE;
    xtype = STORE;
    memWrite = true;
    break;
  default:
    printf("unknown opcode: raw=%08x  opcode=%u\n", raw, opcode);
    assert(false && "unknown opcode");
    break;
  }
  ++instructionCount;
  ++itokenCounts[token];
  ++xtypeCounts[xtype];
  if (machineCode == 0)
      ++nopCount;
}

/*
 * Helper function to print decoded instruction results
 */
void Instruction::print() {
  if (token == ITOKEN_NONE) {
    printf("0x%08x  Unable to decode\n", raw);
    return;
  }

  printf("%08x  %-8s %-8s %-8s ", raw, ITokenName[token], IFormatName[format], XTypeName[xtype]);
  if (format == R_TYPE)
    printf("rs=%2u  rt=%2u  rd=%2u  shamt=%u\n", rs, rt, rd, shamt);
  else if (format == I_TYPE)
    printf("rs=%2u  rt=%2u  imm=0x%x\n", rs, rt, imm);
  else if (format == J_TYPE)
    printf("target=0x%x\n", target);
}

/*
 * Function to produce a formatted string with the assembly language
 * representation of a decoded instruction.
 */
string Instruction::str() {
  char buf[64];
  switch (format) {
  case R_TYPE:
    switch (xtype) {
    case ALU:
      if (token == MULT || token == MULTU || token == DIV || token == DIVU) {
        sprintf(buf, "%08x  %s $%u, $%u", raw, ITokenName[token], rs, rt);
      }
      else if (token == MTHI || token == MTLO) {
        sprintf(buf, "%08x  %s $%u", raw, ITokenName[token], rs);
      }
      else if (token == MFHI || token == MFLO) {
        sprintf(buf, "%08x  %s $%u", raw, ITokenName[token], rd);
      }
      else {
        sprintf(buf, "%08x  %s $%u, $%u, $%u", raw, ITokenName[token], rd, rs, rt);
      }
      break;
    case SHIFT:
      if (token == SLLV || token == SRLV || token == SRAV) {
        sprintf(buf, "%08x  %s $%u, $%u, $%u", raw, ITokenName[token], rd, rs, rt);
      }
      else
      {
        sprintf(buf, "%08x  %s $%u, $%u, %u", raw, ITokenName[token], rd, rt, shamt);
      }
      break;
    case JUMP:
      if (token == JR) {
        sprintf(buf, "%08x  %s $%u", raw, ITokenName[token], rs);
      }
      else  { // JALR
        sprintf(buf, "%08x  %s $%u, $%u", raw, ITokenName[token], rd, rs);
      }
      break;
    default:
      sprintf(buf, "%08x  %s", raw, ITokenName[token]);
      break;
    }
    break;
  case I_TYPE:
    switch (xtype) {
    case ALU:
      sprintf(buf, "%08x  %s $%u, $%u, %d", raw, ITokenName[token], rt, rs, signExtend16(imm));
      break;
    case LOAD:
    case STORE:
      sprintf(buf, "%08x  %s $%u, %d($%u)", raw, ITokenName[token], rt, signExtend16(imm), rs);
      break;
    case BRANCH:
      if (token == BGEZ || token == BGTZ || token == BLEZ || token == BLTZ) {
        sprintf(buf, "%08x  %s $%u, %d", raw, ITokenName[token], rs, signExtend16(imm));
      }
      else {
        sprintf(buf, "%08x  %s $%u, $%u, %d", raw, ITokenName[token], rs, rt, signExtend16(imm));
      }
      break;
    default:
      sprintf(buf, "%08x  %s", raw, ITokenName[token]);
      break;
    }
    break;
  case J_TYPE:
    sprintf(buf, "%08x  %s 0x%x", raw, ITokenName[token], target<<2);
    break;
  default:
    sprintf(buf, "%08x  %s", raw, ITokenName[token]);
    break;
  }
  string s(buf);
  s.insert(s.end(), 36 - s.size(), ' ');
  return s;
}

string Instruction::issuePcStr() {
  char buf[9];
  sprintf(buf, "%08x", issue_pc);
  return string(buf);
}


