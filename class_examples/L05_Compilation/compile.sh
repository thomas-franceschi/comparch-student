#!/bin/bash

gcc -S simple.c
gcc -S foo.c
as simple.s -o simple.o
as foo.s -o foo.o
ld --eh-frame-hdr -m elf_x86_64 -dynamic-linker \
    /lib64/ld-linux-x86-64.so.2 \
    /usr/lib/../lib64/crt1.o /usr/lib/../lib64/crti.o \
    /home/student/software/lib/gcc/x86_64-unknown-linux-gnu/4.9.2/crtbegin.o \
    -L/home/student/software/lib/gcc/x86_64-unknown-linux-gnu/4.9.2 \
    -L/home/student/software/lib/gcc/x86_64-unknown-linux-gnu/4.9.2/../../../../lib64 \
    -L/lib/../lib64 -L/usr/lib/../lib64 \
    -L/home/student/software/lib/gcc/x86_64-unknown-linux-gnu/4.9.2/../../.. \
    -lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed -lgcc_s --no-as-needed \
    /home/student/software/lib/gcc/x86_64-unknown-linux-gnu/4.9.2/crtend.o \
    /usr/lib/../lib64/crtn.o \
    foo.o simple.o \
    -o simple
