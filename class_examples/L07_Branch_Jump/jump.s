# jump.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
        addi $s0, $0, 5
        j    foo
        nop
        addi $s1, $0, 6
foo:
        addi $s1, $0, 7

        ori $v0, $0, 10     # exit
        syscall
    .end main
