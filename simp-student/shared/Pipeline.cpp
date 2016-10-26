/*
    SIMP MIPS Pipelined Architecture Simulation Package

    Pipeline parent class implementation

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

#include "Pipeline.h"

bool Pipeline::continueExec = true;
bool Pipeline::verbose = false;
bool Pipeline::verboseIcache = false;
bool Pipeline::verboseDcache = false;
int  Pipeline::forwardingLevel = 1;
int  Pipeline::loadStalls = 0;
int  Pipeline::controlStalls = 0;

void Pipeline::printRegsHex() {
    printf(" r0( 0): %08x   r1(at): %08x   r2(v0): %08x   r3(v1): %08x\n", reg[0],  reg[1],  reg[2],  reg[3]);
    printf(" r4(a0): %08x   r5(a1): %08x   r6(a2): %08x   r7(a3): %08x\n", reg[4],  reg[5],  reg[6],  reg[7]);
    printf(" r8(t0): %08x   r9(t1): %08x  r10(t2): %08x  r11(t3): %08x\n", reg[8],  reg[9],  reg[10], reg[11]);
    printf("r12(t4): %08x  r13(t5): %08x  r14(t6): %08x  r15(t7): %08x\n", reg[12], reg[13], reg[14], reg[15]);
    printf("r16(s0): %08x  r17(s1): %08x  r18(s2): %08x  r19(s3): %08x\n", reg[16], reg[17], reg[18], reg[19]);
    printf("r20(s4): %08x  r21(s5): %08x  r22(s6): %08x  r23(s7): %08x\n", reg[20], reg[21], reg[22], reg[23]);
    printf("r24(t8): %08x  r25(t9): %08x  r26(k0): %08x  r27(k1): %08x\n", reg[24], reg[25], reg[26], reg[27]);
    printf("r28(gp): %08x  r29(fp): %08x  r30(sp): %08x  r31(ra): %08x\n", reg[28], reg[29], reg[30], reg[31]);
}

void Pipeline::printRegsDec() {
    printf(" r0( 0): %-10d   r1(at): %-10d   r2(v0): %-10d   r3(v1): %-10d\n", reg[0],  reg[1],  reg[2],  reg[3]);
    printf(" r4(a0): %-10d   r5(a1): %-10d   r6(a2): %-10d   r7(a3): %-10d\n", reg[4],  reg[5],  reg[6],  reg[7]);
    printf(" r8(t0): %-10d   r9(t1): %-10d  r10(t2): %-10d  r11(t3): %-10d\n", reg[8],  reg[9],  reg[10], reg[11]);
    printf("r12(t4): %-10d  r13(t5): %-10d  r14(t6): %-10d  r15(t7): %-10d\n", reg[12], reg[13], reg[14], reg[15]);
    printf("r16(s0): %-10d  r17(s1): %-10d  r18(s2): %-10d  r19(s3): %-10d\n", reg[16], reg[17], reg[18], reg[19]);
    printf("r20(s4): %-10d  r21(s5): %-10d  r22(s6): %-10d  r23(s7): %-10d\n", reg[20], reg[21], reg[22], reg[23]);
    printf("r24(t8): %-10d  r25(t9): %-10d  r26(k0): %-10d  r27(k1): %-10d\n", reg[24], reg[25], reg[26], reg[27]);
    printf("r28(gp): %-10d  r29(fp): %-10d  r30(sp): %-10d  r31(ra): %-10d\n", reg[28], reg[29], reg[30], reg[31]);
}

void Pipeline::listCode() {
    for (int i = -4;  i < 12;  i+=4) {
        Instruction I(M.read(32, pc.q + i));
        cout << I.str() << endl;
    }
}

void Pipeline::run(char *elfFileName) {
    M.readElfFile(elfFileName);
    reg[28] = M.getInitGp();
    reg[29] = M.getInitSp();
    pc.q    = M.getInitPc();
    continueExec = true;
    verbose = false;
    while (continueExec) {
        CombLogic::evalAll();
        Reg::clockAll();
    }
}

void Pipeline::runInteractive(char *elfFileName) {
    M.readElfFile(elfFileName);
    reg[28] = M.getInitGp();
    reg[29] = M.getInitSp();
    pc.q    = M.getInitPc();
    continueExec = true;
    verbose = true;
    verboseIcache = false;
    verboseDcache = false;

    bool keepGoing = true;

    while (keepGoing && continueExec)
    {
        char *buffer = NULL;
        size_t bufsize = 0;
        char *token;

        printf("simp> ");
        getline(&buffer, &bufsize, stdin);
        token = strtok (buffer," ,\n");
        if (token == NULL) {
            // do nothing, try again
        }
        else if (!strcmp(token, "h")) {
            printf("Commands:\n\n");
            printf("h\t help\n");
            printf("q\t quit\n");
            printf("s\t step\n");
            printf("c\t continue\n");
            printf("v\t toggle verbose instruction mode\n");
            printf("vicache\t toggle verbose instruction cache mode\n");
            printf("vdcache\t toggle verbose data cache mode\n");
            printf("rh\t display registers (hex)\n");
            printf("rd\t display registers (dec)\n");
            printf("l\t list code\n");
            printf("sym [name]\t display address of symbol name\n");
            printf("memh [addr]\t display memory contents at addr (hex), addr is in hex\n");
            printf("memd [addr]\t display memory contents at addr (dec), addr is in hex\n");
            printf("picache\t print instruction cache\n");
            printf("pdcache\t print data cache\n");
            printf("\n");
        }
        else if (!strcmp(token, "q")) {
            printf("quitting\n");
            keepGoing = false;
        }
        else if (!strcmp(token, "s")) {
            CombLogic::evalAll();
            Reg::clockAll();
        }
        else if (!strcmp(token, "c")) {
            while (continueExec) {
                CombLogic::evalAll();
                Reg::clockAll();
            }
        }
        else if (!strcmp(token, "v")) {
            verbose = !verbose;
        }
        else if (!strcmp(token, "vicache")) {
            verboseIcache = !verboseIcache;
        }
        else if (!strcmp(token, "vdcache")) {
            verboseDcache = !verboseDcache;
        }
        else if (!strcmp(token, "rh")) {
            printRegsHex();
        }
        else if (!strcmp(token, "rd")) {
            printRegsDec();
        }
        else if (!strcmp(token, "l")) {
            listCode();
        }
        else if (!strcmp(token, "sym")) {
            token = strtok (NULL," \n");
            printf("0x%x\n", M.getSymbolAddr(token));
        }
        else if (!strcmp(token, "memh")) {
            iCache.flush();
            dCache.flush();
            token = strtok (NULL," \n");
            uint32_t wordAddr = strtol(token, NULL, 16) & 0xfffffffc;
            printf("%x: %x\n", wordAddr, M.read(32, wordAddr));
        }
        else if (!strcmp(token, "memd")) {
            iCache.flush();
            dCache.flush();
            token = strtok (NULL," \n");
            uint32_t wordAddr = strtol(token, NULL, 16) & 0xfffffffc;
            printf("%x: %d\n", wordAddr, M.read(32, wordAddr));
        }
        else if (!strcmp(token, "picache")) {
            iCache.print();
        }
        else if (!strcmp(token, "pdcache")) {
            dCache.print();
        }
        else {
            printf("unknown command (enter h for list of commands)\n");
        }
    }
}

void Pipeline::outputStats() {
  ofstream statFile;
  statFile.open("stats.csv");
  assert(statFile && "unable to open statFile");
  statFile << "instructionCount," << Instruction::instructionCount << endl;
  for (int i = 0;  i < NUM_XTYPE;  i++) {
    statFile << Instruction::XTypeName[i] << "," << Instruction::xtypeCounts[i] << endl;
  }
  for (int i = 0;  i < NUM_ITOKEN;  i++) {
    statFile << Instruction::ITokenName[i] << "," << Instruction::itokenCounts[i] << endl;
  }
  statFile << "nopCount, " << Instruction::nopCount << endl;
  statFile << "loadStalls, " << loadStalls << endl;
  statFile << "controlStalls, " << controlStalls << endl;
  float iCacheMissRate = 1 - ((float) iCache.hits/iCache.accesses);
  float dCacheMissRate = 1 - ((float) dCache.hits/dCache.accesses);
  statFile << "iCacheMissRate, " << iCacheMissRate << endl;
  statFile << "dCacheMissRate, " << dCacheMissRate << endl;
}
