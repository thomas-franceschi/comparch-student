/*
    SIMP MIPS Pipelined Architecture Simulation Package

    2-stage MIPS pipeline eval methods

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

#include "Pipe2Stage.h"

#include <inttypes.h>

void FetchStage::eval() {
    ir.d = new Instruction(iCache.read(32, pc.q));
    ir.d->issue_pc = pc.q;
    if (Pipeline::verboseIcache)
        cout << "\tI" << iCache.str() << endl;
}

void ExecStage::eval() {
    pc.d = pc.q + 4;

    if (ir.q == 0)
        return;

    uint64_t p;  // product for mult, div

    switch(ir.q->token) {
    case SLL:
        reg[ir.q->rd] = reg[ir.q->rt] << ir.q->shamt;
        break;
    case SRL:
        reg[ir.q->rd] = reg[ir.q->rt] >> ir.q->shamt;
        break;
    case SRA:
        reg[ir.q->rd] = (int) reg[ir.q->rt] >> ir.q->shamt;
        break;
    case SLLV:
        reg[ir.q->rd] = reg[ir.q->rt] << reg[ir.q->rs];
        break;
    case SRLV:
        reg[ir.q->rd] = reg[ir.q->rt] >> reg[ir.q->rs];
        break;
    case SRAV:
        reg[ir.q->rd] = (int) reg[ir.q->rt] >> reg[ir.q->rs];
        break;
    case ADD:
        reg[ir.q->rd] = reg[ir.q->rs] + reg[ir.q->rt];
        break;
    case ADDU:
        reg[ir.q->rd] = reg[ir.q->rs] + reg[ir.q->rt];
        break;
    case SUB:
        reg[ir.q->rd] = reg[ir.q->rs] - reg[ir.q->rt];
        break;
    case SUBU:
        reg[ir.q->rd] = reg[ir.q->rs] - reg[ir.q->rt];
        break;
    case AND:
        reg[ir.q->rd] = reg[ir.q->rs] & reg[ir.q->rt];
        break;
    case OR:
        reg[ir.q->rd] = reg[ir.q->rs] | reg[ir.q->rt];
        break;
    case XOR:
        reg[ir.q->rd] = reg[ir.q->rs] ^ reg[ir.q->rt];
        break;
    case NOR:
        reg[ir.q->rd] = ~(reg[ir.q->rs] | reg[ir.q->rt]);
        break;
    case MULT:
        p = (int) reg[ir.q->rs] * (int) reg[ir.q->rt];
        hi = p >> 32L;
        lo = p & 0x00000000ffffffffL;
        break;
    case MULTU:
        p = (uint64_t) reg[ir.q->rs] * (uint64_t) reg[ir.q->rt];
        hi = p >> 32L;
        lo = p & 0x00000000ffffffffL;
        break;
    case DIV:
        // behavior undefined for division by 0 or overflow
        if (reg[ir.q->rt] != 0 &&  reg[ir.q->rs] != 0x80000000 && reg[ir.q->rt] != 0xffffffff) {
            lo = (int) reg[ir.q->rs] / (int) reg[ir.q->rt];
            hi = (int) reg[ir.q->rs] % (int) reg[ir.q->rt];
        }
        break;
    case DIVU:
        // behavior undefined for division by 0 or overflow
        if (reg[ir.q->rt] != 0 &&  reg[ir.q->rs] != 0x80000000 && reg[ir.q->rt] != 0xffffffff) {
            lo = reg[ir.q->rs] / reg[ir.q->rt];
            hi = reg[ir.q->rs] % reg[ir.q->rt];
        }
        break;
    case SLT:
        reg[ir.q->rd] = ((int) reg[ir.q->rs] < (int) reg[ir.q->rt]) ? 1 : 0;
        break;
    case SLTU:
        reg[ir.q->rd] = (reg[ir.q->rs] < reg[ir.q->rt]) ? 1 : 0;
        break;
    case MFHI:
        reg[ir.q->rd] = hi;
        break;
    case MFLO:
        reg[ir.q->rd] = lo;
        break;
    case MTHI:
        hi = reg[ir.q->rs];
        break;
    case MTLO:
        lo = reg[ir.q->rs];
        break;
    case JR:
        pc.d = reg[ir.q->rs];
        break;
    case J:
        pc.d = (ir.q->target << 2) | (pc.q & 0xf0000000);
        break;
    case JAL:
        reg[31] = pc.d;   // pc has been pre-incremented
        pc.d = (ir.q->target << 2) | (pc.q & 0xf0000000);
        break;
    case JALR:
        reg[31] = pc.d;
        pc.d = reg[ir.q->rs];
        break;
    case BEQ:
        // note pc was pre-incremented
        pc.d = (reg[ir.q->rs] == reg[ir.q->rt]) ? pc.q + (signExtend16(ir.q->imm) << 2) : pc.q + 4;
        break;
    case BNE:
        pc.d = (reg[ir.q->rs] != reg[ir.q->rt]) ? pc.q + (signExtend16(ir.q->imm) << 2) : pc.q + 4;
        break;
    case BGEZ:
        pc.d = ((int) reg[ir.q->rs] >= 0) ? pc.q + (signExtend16(ir.q->imm) << 2) : pc.q + 4;
        break;
    case BGTZ:
        pc.d = ((int) reg[ir.q->rs] > 0) ? pc.q + (signExtend16(ir.q->imm) << 2) : pc.q + 4;
        break;
    case BLEZ:
        pc.d = ((int) reg[ir.q->rs] <= 0) ? pc.q + (signExtend16(ir.q->imm) << 2) : pc.q + 4;
        break;
    case BLTZ:
        pc.d = ((int) reg[ir.q->rs] < 0) ? pc.q + (signExtend16(ir.q->imm) << 2) : pc.q + 4;
        break;
    case ADDI:
        reg[ir.q->rt] = reg[ir.q->rs] + signExtend16(ir.q->imm);
        break;
    case ADDIU:
        reg[ir.q->rt] = reg[ir.q->rs] + signExtend16(ir.q->imm);;
        break;
    case SLTI:
        reg[ir.q->rt] = ((int) reg[ir.q->rs] < (int) signExtend16(ir.q->imm)) ? 1 : 0;
        break;
    case SLTIU:
        reg[ir.q->rt] = (reg[ir.q->rs] < signExtend16(ir.q->imm)) ? 1 : 0;
        break;
    case ANDI:
        reg[ir.q->rt] = reg[ir.q->rs] & ir.q->imm;
        break;
    case ORI:
        reg[ir.q->rt] = reg[ir.q->rs] | ir.q->imm;
        break;
    case XORI:
        reg[ir.q->rt] = reg[ir.q->rs] ^ ir.q->imm;
        break;
    case LUI:
        reg[ir.q->rt] = (ir.q->imm << 16);
        break;
    case LB:
        reg[ir.q->rt] = signExtend8(dCache.read(8, reg[ir.q->rs] + signExtend16(ir.q->imm)));
        break;
    case LH:
        reg[ir.q->rt] = signExtend16(dCache.read(16, reg[ir.q->rs] + signExtend16(ir.q->imm)));
        break;
    case LW:
        reg[ir.q->rt] = dCache.read(32, reg[ir.q->rs] + signExtend16(ir.q->imm));
        break;
    case LBU:
        reg[ir.q->rt] = dCache.read(8, reg[ir.q->rs] + signExtend16(ir.q->imm));
        break;
    case LHU:
        reg[ir.q->rt] = dCache.read(16, reg[ir.q->rs] + signExtend16(ir.q->imm));
        break;
    case SB:
        dCache.write(8, reg[ir.q->rs] + signExtend16(ir.q->imm), reg[ir.q->rt]);
        break;
    case SH:
        dCache.write(16, reg[ir.q->rs] + signExtend16(ir.q->imm), reg[ir.q->rt]);
        break;
    case SW:
        dCache.write(32, reg[ir.q->rs] + signExtend16(ir.q->imm), reg[ir.q->rt]);
        break;
    case SYSCALL:
        switch (reg[2]) {
        case 1:
            printf("%d", reg[4]);
            break;
        case 4:
            printf("%s", M.getMemoryPtr(reg[4]));
            break;
        case 9:
            reg[2] = M.alloc(reg[4]);
            break;
        case 10:
            Pipeline::continueExec = false;
            break;
        case 11:
            printf("%c", reg[4]);
            break;
        case 20:
            printf("0x%1$x (%1$d)\n", reg[4]);
            break;
        default:
            printf("Undefined syscall code: %d\n", reg[2]);
            assert(false && "undefined syscall code");
            break;
        }
        break;
    case BREAK:
        Pipeline::continueExec = false;
        break;
    default:
        printf("undefined opcode: %u\n", ir.q->opcode);
        //            assert(ir.q->rt(false);
        break;
    }

    if (Pipeline::verbose) {
        printf("%08x: ", ir.q->issue_pc);
        cout << ir.q->str();
        if (ir.q->regWrite)
            printf("| $%1$u = 0x%2$x (%2$d)", ir.q->regDest, reg[ir.q->regDest]);
        else if (ir.q->token == MULT || ir.q->token == MULTU || ir.q->token == DIV || ir.q->token == DIVU)
            printf("| $hi = 0x%1$08x (%1$d)  $lo = 0x%2$08x (%2$d)", hi, lo);
        else if (ir.q->token == MTLO)
            printf("| $lo = 0x%1$x (%1$d)", lo);
        else if (ir.q->token == MTHI)
            printf("| $hi = 0x%1$x (%1$d)", hi);
        else if (ir.q->xtype == STORE)
            printf("| M[%1$08x] = 0x%2$08x (%2$d)", reg[ir.q->rs]+ir.q->imm, M.read(32, reg[ir.q->rs]+ir.q->imm));
        printf("\n");
    }
    if (Pipeline::verboseDcache && (ir.q->xtype == STORE || ir.q->xtype == LOAD))
        cout << "\tD" << dCache.str() << endl;
    delete ir.q;
}

