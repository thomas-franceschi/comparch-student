# while-loop.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
# int i = 0;
        addi $s0, $0, 0         # i = 0
# while (i < 10) {
        slti $t0, $s0, 10       # t0 = (i < 10)
loop_cond:
        beq  $t0, $0, sequel    # _if (!t0) goto sequel
        nop
#     i = i + 1;
        addi $s0, $s0, 1        # s0 = s0 + 1
        j    loop_cond          # goto loop_cond
        nop
# }

sequel:
        ori $v0, $0, 10     # exit
        syscall
    .end main
