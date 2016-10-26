# load-use-hazard.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:

        ori $v0, $0, 10     # exit
        syscall
    .end main
