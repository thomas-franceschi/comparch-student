# if-lte.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
        addi $s0, $0, 2         # x = 2
        addi $s1, $0, 1         # y = 1
# if (x <= y)
        slt $t0, $s1, $s0       # t0 = !(x <= y) = (y < x)
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
