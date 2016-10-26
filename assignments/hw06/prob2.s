# prob2.s
    .set noreorder
    .data
A:  .word 2
    .text
    .globl main
    .ent main
main:
        addi    $t0, $0, 1
        addi    $t3, $0, 5
        lui     $t1, %hi(A)
        ori     $t1, $t1, %lo(A)
        lw      $t2, 0($t1)
        bne     $t0, $t2, L
        nop
        addi    $t3, $0, 7
L:
        add     $t4, $t0, $t3
        ori     $v0, $0, 10     # exit

# Do not edit below this line
        nop
        nop
        nop
        syscall
    .end main
