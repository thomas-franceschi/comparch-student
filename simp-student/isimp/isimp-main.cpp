/*
    SIMP MIPS Pipelined Architecture Simulation Package

    mipsim main procedure

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

void printHelp()
{
    printf("Usage:  pipesim [options] [mips-elf-file]\n");
    printf("options:\n");
    printf("-h\t help\n");
    printf("-i\t interactive mode\n");
    printf("-icache [assoc] [index-bits] [offset-bits]\t instruction cache parameters\n");
    printf("-dcache [assoc] [index-bits] [offset-bits]\t data cache parameters\n");
}

int main(int argc, char **argv)
{
    unsigned iAssoc             = 0;
    unsigned iLogIndex          = 0;
    unsigned iLogBlockSize      = 0;
    unsigned dAssoc             = 0;
    unsigned dLogIndex          = 0;
    unsigned dLogBlockSize      = 0;
    bool     interactiveMode    = false;
    char     *elfFileName       = argv[argc-1];

    if (argc < 2) {
        printHelp();
        exit(0);
    }
    for (int i = 1;  i < argc;  i++) {
        if (!strcmp(argv[i], "-h")) {
            printHelp();
            exit(0);
        }
        else if (!strcmp(argv[i], "-i")) {
            interactiveMode = true;
        }
        else if (!strcmp(argv[i], "-icache")) {
            iAssoc          = atoi(argv[++i]);
            iLogIndex       = atoi(argv[++i]);
            iLogBlockSize   = atoi(argv[++i]);
        }
        else if (!strcmp(argv[i], "-dcache")) {
            dAssoc          = atoi(argv[++i]);
            dLogIndex       = atoi(argv[++i]);
            dLogBlockSize   = atoi(argv[++i]);
        }
    }

    Pipe2Stage pipeline(iAssoc, iLogIndex, iLogBlockSize, dAssoc, dLogIndex, dLogBlockSize);
    if (interactiveMode)
        pipeline.runInteractive(elfFileName);
    else
        pipeline.run(elfFileName);

    pipeline.outputStats();

    return 0;
}
