# for-loop.s
    .set noreorder
    .data
A:  .space 64
    .text
    .globl main
    .ent main
main:
# for (i = 0;  i < 16;  i++)
        addi $s0, $0, 0         # i = 0
loop_cond:
        slti $t0, $s0, 16       # t0 = (i < 16)
        beq  $t0, $0, sequel    # _if (!t0) goto sequel
        nop
#     A[i] = i;
        lui  $t1, %hi(A)        # t1 = A
        ori  $t1, $t1, %lo(A)
        sll  $t2, $s0, 2        # t2 = i * 4
        add  $t2, $t1, $t2      # t2 = A + t2
        sw   $s0, 0($t2)        # *(t2) = i
        addi $s0, $s0, 1        # i++
        j    loop_cond          # goto loop_cond
        nop

sequel:
        ori $v0, $0, 10     # exit
        syscall
    .end main
