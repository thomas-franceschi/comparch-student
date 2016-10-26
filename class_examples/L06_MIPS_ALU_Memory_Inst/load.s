# load.s
    .set noreorder
    .data
x:  .word 7

    .text
    .globl main
    .ent main
main:
        lui $t0, %hi(x)
        ori $t0, $t0, %lo(x)
        lw $s0, 0($t0)

        ori $v0, $0, 10     # exit
        syscall
    .end main
