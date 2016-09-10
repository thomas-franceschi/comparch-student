# if-gte.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
        addi $s0, $0, 1         # x = 1
        addi $s1, $0, 2         # y = 2
# if (x >= y)
        slt $t0, $s0, $s1       # t0 = !(x >= y) = (x < y)
        bne $t0, $0, sequel     # if (t0) goto sequel
        nop
#    p = 5;
        addi $s2, $0, 5         # p = 5

sequel:
# q = 7
        addi $s3, $0, 7         # q = 7

        ori $v0, $0, 10     # exit
        syscall
    .end main
