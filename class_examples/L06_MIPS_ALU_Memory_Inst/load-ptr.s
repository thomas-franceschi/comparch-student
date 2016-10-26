# load.s
    .set noreorder
    .data
x:  .word 7

    .text
    .globl main
    .ent main
main:
        lui $s0, %hi(x)
        ori $s0, $s0, %lo(x)
        lw $s1, 0($s0)

        ori $v0, $0, 10     # exit
        syscall
    .end main
