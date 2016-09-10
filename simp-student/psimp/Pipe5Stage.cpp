/*
    SIMP MIPS Pipelined Architecture Simulation Package

    5-stage MIPS pipeline eval methods

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

#include "Pipe5Stage.h"

void IfStage::eval() {
    if_id.ir.d = new Instruction(iCache.read(32, pc.q));
    if_id.ir.d->issue_pc = pc.q;
    if (Pipeline::verbose) {
        cout << "----------------------------------------------------------" << endl;
        cout << "IF:  " << if_id.ir.d->issuePcStr() << "--" << if_id.ir.d->str() << endl;
    }
    if (Pipeline::verboseIcache)
        cout << "\tI" << iCache.str() << endl;
}

void IdStage::eval() {
    if (Pipeline::verbose) {
        cout << "ID:  " << if_id.ir.q->issuePcStr() << "--" << if_id.ir.q->str() << endl;
    }

    uint32_t regData1;
    uint32_t regData2;
    IToken iToken = if_id.ir.q->token;

    /*
     * Forwarding Level 0: No Pipelining
     */
    if (Pipeline::forwardingLevel == 0) {
        regData1 = reg[if_id.ir.q->rs];
        regData2 = reg[if_id.ir.q->rt];
    }
    /*
     * Forwarding Level 1: This is what is handed out to students
     *   - load-use stall
     *   - register file bypass from WB stage only
     */
    else if (Pipeline::forwardingLevel == 1) {
        // look for branch/jump/syscall stall
        // stall condition:
        //   branch/jr/jalr/syscall instruction in this stage AND
        //   (EX stage has an instruction that writes to rs or rt OR
        //    MEM stage has an instruction that reads memory to rs or rt)
        if (if_id.ir.q->xtype == BRANCH || iToken == JR || iToken == JALR || iToken == SYSCALL) {

            // Not implemented

        }

        // look for load/use stall
        // stall condition:
        //   load is in EX stage AND
        //   destReg of instruction in EX stage matches rs or rt
        if (id_ex.ir.q->memToReg
                && (   if_id.ir.q->rs == id_ex.ir.q->regDest
                        || if_id.ir.q->rs == id_ex.ir.q->regDest)) {
            if (Pipeline::verbose) {
                cout << "\tLOAD-USE STALL" << endl;
            }
            pc.stall();
            if_id.ir.stall();
            ++Pipeline::loadStalls;
            id_ex.ir.d = new Instruction(0);
            return;
        }

        // forward values to branch compare unit and to EX stage
        // forwarding for rs/regData1

        // Not implemented
    }
    /*
     * Forwarding Level 2:  Full forwarding
     *   - branch/jump/syscall stall
     *   - load/use stall
     *   - forwarding to branch compare and EX stage
     */
    else if (Pipeline::forwardingLevel == 2) {  // partial forwarding for assignment
        // look for branch/jump/syscall stall
        // stall condition:
        //   branch/jr/jalr/syscall instruction in this stage AND
        //   (EX stage has an instruction that writes to rs or rt OR
        //    MEM stage has an instruction that reads memory to rs or rt)
        if (if_id.ir.q->xtype == BRANCH || iToken == JR || iToken == JALR || iToken == SYSCALL) {

            // Insert code here

        }

        // look for load/use stall
        // stall condition:
        //   load is in EX stage AND
        //   destReg of instruction in EX stage matches rs or rt
        if (id_ex.ir.q->memToReg
                && (   if_id.ir.q->rs == id_ex.ir.q->regDest
                        || if_id.ir.q->rs == id_ex.ir.q->regDest)) {
            if (Pipeline::verbose) {
                cout << "\tLOAD-USE STALL" << endl;
            }
            pc.stall();
            if_id.ir.stall();
            ++Pipeline::loadStalls;
            id_ex.ir.d = new Instruction(0);
            return;
        }

        // forward values to branch compare unit and to EX stage
        // forwarding for rs/regData1

        // Insert code here
    }
    /*
     * Undefined Forwarding Level
     */
    else {
        assert(false && "unknown forwarding level");
    }

    // Handle BREAK instruction
    if (iToken == BREAK) {
        Pipeline::continueExec = false;
    }

    // SYSCALL is a very special instruction!!!
    // We need to handle it as early as possible in the pipeline since it may
    // signal program termination and we don't want to risk executing any
    // illegal instructions beyond it (certainly not a branch or jump).
    // It reads $2 to determine the code and may read $4 as an argument.
    // Some codes (eg 9 for memory allocation) may also write a value to $4;
    // this situation can only be detected at run time.
    if (iToken == SYSCALL) {
        switch (regData1) {
        case 9:
            // This is a real hack!!
            // Since the code can only be determined at run time,
            // for cases where SYSCALL writes back to a register we need to
            // set regWrite and regDest at runtime.
            // Convert this to something that looks like a LOAD instruction.
            if_id.ir.q->regDest = 2;
            if_id.ir.q->regWrite = true;
            if_id.ir.q->memToReg = true;
            break;
        case 10:
            Pipeline::continueExec = false;
            break;
        default:
            // remaining cases handled in MEM stage
            break;
        }
    }

    // calculate next PC
    switch (if_id.ir.q->token) {
    case JR:
        pc.d = regData1;
        break;
    case J:
        pc.d = (if_id.ir.q->target << 2) | (pc.q & 0xf0000000);
        break;
    case JAL:
        pc.d = (if_id.ir.q->target << 2) | (pc.q & 0xf0000000);
        break;
    case JALR:
        pc.d = regData1;
        break;
    case BEQ:
        // note pc was pre-incremented
        pc.d = (regData1 == regData2) ? pc.q + (signExtend16(if_id.ir.q->imm) << 2) : pc.q + 4;
        break;
    case BNE:
        pc.d = (regData1 != regData2) ? pc.q + (signExtend16(if_id.ir.q->imm) << 2) : pc.q + 4;
        break;
    case BGEZ:
        pc.d = ((int) regData1 >= 0) ? pc.q + (signExtend16(if_id.ir.q->imm) << 2) : pc.q + 4;
        break;
    case BGTZ:
        pc.d = ((int) regData1 > 0) ? pc.q + (signExtend16(if_id.ir.q->imm) << 2) : pc.q + 4;
        break;
    case BLEZ:
        pc.d = ((int) regData1 <= 0) ? pc.q + (signExtend16(if_id.ir.q->imm) << 2) : pc.q + 4;
        break;
    case BLTZ:
        pc.d = ((int) regData1 < 0) ? pc.q + (signExtend16(if_id.ir.q->imm) << 2) : pc.q + 4;
        break;
    default:
        pc.d = pc.q + 4;
    }

    // pass register arguments to EX stage
    id_ex.regData1.d = regData1;
    id_ex.regData2.d = regData2;

    // sign extend immediate
    id_ex.immSignExt.d = signExtend16(if_id.ir.q->imm);
    id_ex.immZeroExt.d = zeroExtend16(if_id.ir.q->imm);

    // pass link pc
    id_ex.linkPc.d = pc.q + 4;

    // pass along the instruction
    id_ex.ir.d = if_id.ir.q;
}

void ExStage::eval() {
    if (Pipeline::verbose) {
        cout << "EX:  " << id_ex.ir.q->issuePcStr() << "--" << id_ex.ir.q->str();
    }

    // pass along instruction
    ex_mem.ir.d = id_ex.ir.q;

    uint32_t regData1, regData2;

    /*
     * Forwarding Level 0:  no forwarding
     */
    if (Pipeline::forwardingLevel == 0) {
        regData1 = id_ex.regData1.q;
        regData2 = id_ex.regData2.q;
    }
    /*
     * Forwarding Level 1:  Handed out to students
     *   - no forwarding
     */
    else if (Pipeline::forwardingLevel == 1) {
        regData1 = id_ex.regData1.q;
        regData2 = id_ex.regData2.q;
    }
    /*
     * Forwarding Level 2: Complete forwarding
     *   -forwarding from MEM stage
     *   -forwarding from WB stage
     */
    else if (Pipeline::forwardingLevel == 2) {
        // check for forwarded ALU inputs
        // regData1 forwarding
        //
        // Not implemented, replace the 2 lines below with your code
        //
        regData1 = id_ex.regData1.q;

        // regData2 forwarding
        //
        // Not implemented, replace the 2 lines below with your code
        //
        regData2 = id_ex.regData2.q;
    }
    /*
     * Undefined Forwarding Level
     */
    else {
        assert(false && "unknown forwarding level");
    }

    ex_mem.writeData.d = regData2;

    // Perform ALU operation
    uint64_t p;  // product for mult, div
    switch(id_ex.ir.q->token) {
    case SLL:
        ex_mem.aluOut.d = regData2 << id_ex.ir.q->shamt;
        break;
    case SRL:
        ex_mem.aluOut.d = regData2 >> id_ex.ir.q->shamt;
        break;
    case SRA:
        ex_mem.aluOut.d = (int) regData2 >> id_ex.ir.q->shamt;
        break;
    case SLLV:
        ex_mem.aluOut.d = regData2 << regData1;
        break;
    case SRLV:
        ex_mem.aluOut.d = regData2 >> regData1;
        break;
    case SRAV:
        ex_mem.aluOut.d = (int) regData2 >> regData1;
        break;
    case ADD:
        ex_mem.aluOut.d = regData1 + regData2;
        break;
    case ADDU:
        ex_mem.aluOut.d = regData1 + regData2;
        break;
    case SUB:
        ex_mem.aluOut.d = regData1 - regData2;
        break;
    case SUBU:
        ex_mem.aluOut.d = regData1 - regData2;
        break;
    case AND:
        ex_mem.aluOut.d = regData1 & regData2;
        break;
    case OR:
        ex_mem.aluOut.d = regData1 | regData2;
        break;
    case XOR:
        ex_mem.aluOut.d = regData1 ^ regData2;
        break;
    case NOR:
        ex_mem.aluOut.d = ~(regData1 | regData2);
        break;
    case MULT:
        p = (int) regData1 * (int) regData2;
        hi = p >> 32L;
        lo = p & 0x00000000ffffffffL;
        break;
    case MULTU:
        p = (uint64_t) regData1 * (uint64_t) regData2;
        hi = p >> 32L;
        lo = p & 0x00000000ffffffffL;
        break;
    case DIV:
        // behavior undefined for division by 0 or overflow
        if (regData2 != 0 &&  regData1 != 0x80000000 && regData2 != 0xffffffff) {
            lo = (int) regData1 / (int) regData2;
            hi = (int) regData1 % (int) regData2;
        }
        break;
    case DIVU:
        // behavior undefined for division by 0 or overflow
        if (regData2 != 0 &&  regData1 != 0x80000000 && regData2 != 0xffffffff) {
            lo = regData1 / regData2;
            hi = regData1 % regData2;
        }
        break;
    case SLT:
        ex_mem.aluOut.d = ((int) regData1 < (int) regData2) ? 1 : 0;
        break;
    case SLTU:
        ex_mem.aluOut.d = (regData1 < regData2) ? 1 : 0;
        break;
    case MFHI:
        ex_mem.aluOut.d = hi;
        break;
    case MFLO:
        ex_mem.aluOut.d = lo;
        break;
    case MTHI:
        hi = regData1;
        break;
    case MTLO:
        lo = regData1;
        break;
    case ADDI:
        ex_mem.aluOut.d = regData1 + id_ex.immSignExt.q;
        break;
    case ADDIU:
        ex_mem.aluOut.d = regData1 + id_ex.immSignExt.q;
        break;
    case SLTI:
        ex_mem.aluOut.d = ((int) regData1 < (int) id_ex.immSignExt.q) ? 1 : 0;
        break;
    case SLTIU:
        ex_mem.aluOut.d = (regData1 < id_ex.immSignExt.q) ? 1 : 0;
        break;
    case ANDI:
        ex_mem.aluOut.d = regData1 & id_ex.immZeroExt.q;
        break;
    case ORI:
        ex_mem.aluOut.d = regData1 | id_ex.immZeroExt.q;
        break;
    case XORI:
        ex_mem.aluOut.d = regData1 ^ id_ex.immZeroExt.q;
        break;
    case LUI:
        ex_mem.aluOut.d = (id_ex.ir.q->imm << 16);
        break;
    case JAL:
    case JALR:
        ex_mem.aluOut.d = id_ex.linkPc.q;
        break;
    case LB:
    case LH:
    case LW:
    case LBU:
    case LHU:
    case SB:
    case SH:
    case SW:
        ex_mem.aluOut.d = regData1 + id_ex.immSignExt.q;
        break;
    case SYSCALL:
        ex_mem.aluOut.d = regData1;
        break;
    default:
        ex_mem.aluOut.d = 0;
        break;
    }
    if (Pipeline::verbose) {
        if (id_ex.ir.q->token == MULT || id_ex.ir.q->token == MULTU || id_ex.ir.q->token == DIV || id_ex.ir.q->token == DIVU)
            printf("| $hi = 0x%08x  $lo = 0x%08x", hi, lo);
        else if (id_ex.ir.q->token == MTLO)
            printf("| $lo = 0x%x", lo);
        else if (id_ex.ir.q->token == MTHI)
            printf("| $hi = 0x%x", hi);
        printf("\n");
    }

}

void MemStage::eval() {
    if (Pipeline::verbose) {
        cout << "MEM: " << ex_mem.ir.q->issuePcStr() << "--" << ex_mem.ir.q->str();
    }

    uint32_t memOut;

    // pass along instruction
    mem_wb.ir.d = ex_mem.ir.q;

    // read memory for loads
    // write memory for stores
    switch (ex_mem.ir.q->token) {
    case LB:
        memOut = signExtend8(dCache.read(8, ex_mem.aluOut.q));
        break;
    case LH:
        memOut = signExtend16(dCache.read(16, ex_mem.aluOut.q));
        break;
    case LW:
        memOut = dCache.read(32, ex_mem.aluOut.q);
        break;
    case LBU:
        memOut = dCache.read(8, ex_mem.aluOut.q);
        break;
    case LHU:
        memOut = dCache.read(16, ex_mem.aluOut.q);
        break;
    case SB:
        dCache.write(8, ex_mem.aluOut.q, ex_mem.writeData.q);
        break;
    case SH:
        dCache.write(16, ex_mem.aluOut.q, ex_mem.writeData.q);
        break;
    case SW:
        dCache.write(32, ex_mem.aluOut.q, ex_mem.writeData.q);
        break;
    case SYSCALL:
        switch (ex_mem.aluOut.q) {
        case 1:
            printf("%d", ex_mem.writeData.q);
            break;
        case 4:
            printf("%s", M.getMemoryPtr(ex_mem.writeData.q));
            break;
        case 9:
            memOut = M.alloc(ex_mem.writeData.q);
            break;
        case 11:
            printf("%c", ex_mem.writeData.q);
            break;
        default:
            assert(false && "illegal SYSCALL code");
        }
        break;
        default:
            memOut = 0;
            break;
    }

    mem_wb.wbData.d = ex_mem.ir.q->memToReg ? memOut : ex_mem.aluOut.q;
    if (Pipeline::verbose) {
        if (ex_mem.ir.q->xtype == STORE)
            printf("| M[%08x] = 0x%08x", ex_mem.aluOut.q, ex_mem.writeData.q);
        printf("\n");
    }
    if (Pipeline::verboseDcache && (ex_mem.ir.q->xtype == STORE || ex_mem.ir.q->xtype == LOAD))
        cout << "\tD" << dCache.str() << endl;
}

void WbStage::eval() {
    if (Pipeline::verbose) {
        cout << "WB:  " << mem_wb.ir.q->issuePcStr() << "--" << mem_wb.ir.q->str();
    }

    // write back to registers for ALU, load, jal
    if (mem_wb.ir.q->regWrite) {
        reg[mem_wb.ir.q->regDest] = mem_wb.wbData.q;
    }

    if (Pipeline::verbose) {
        if (mem_wb.ir.q->regWrite)
            printf("| $%u = 0x%x", mem_wb.ir.q->regDest, mem_wb.wbData.q);
        printf("\n");
    }

    delete mem_wb.ir.q;
}

