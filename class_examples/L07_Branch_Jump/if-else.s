# if-else.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
        addi $s0, $0, 1     # x = 1
        addi $s1, $0, 2     # y = 2
# _if (x < y)
        slt $t0, $s0, $s1       # t0 = (x < y)
        beq $t0, $0, else_block # if (!t0) goto else_block
        nop
#     p = 5;
        addi $s2, $0, 5         # p = 5
        j sequel                # goto sequel
        nop
# _else

else_block:
#     p = 7;
        addi $s3, $0, 7         # p = 7

sequel:
# q = 8;
        addi $s4, $0, 8         # q = 8

        ori $v0, $0, 10     # exit
        syscall
    .end main
