# encoding.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
    addi    $sp, $sp, -4
    sw      $ra, 0($sp)
    addi    $t0, $0, 5
    addi    $t1, $0, 3
    add     $s0, $t0, $t1
    bne     $t0, $t1, L1
    nop
    add     $t2, $t1, $t0
L1:
    sub     $t2, $t1, $t0
    lw      $ra, 0($sp)
    addi    $sp, $sp, 4
    jr      $ra
    nop
    .end main
