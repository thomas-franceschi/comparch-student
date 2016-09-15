# encoding.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
    add     $sp, $sp, -4
    sw      $ra, 0($sp)
    addi    $t0, $0, 5
    addi    $t1, $0, 3
    bne     $t0, $t1, L1
    nop
    add     $t2, $t1, $t0
L1:
    sub     $t2, $t1, $t0
    lw      $ra, 0($sp)
    add     $sp, $sp, 4
    jr      $ra
    nop
    .end main
