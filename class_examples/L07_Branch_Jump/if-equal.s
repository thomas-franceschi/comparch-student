# if-equal.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
        addi $s0, $0, 1
        addi $s1, $0, 2
# if (x == y)
        bne $s0, $s1, sequel
        nop
#    p = 5;
        addi $s2, $0, 5

sequel:
# q = 7
        addi $s3, $0, 7

        ori $v0, $0, 10     # exit
        syscall
    .end main
