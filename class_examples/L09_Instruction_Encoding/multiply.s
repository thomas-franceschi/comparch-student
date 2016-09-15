# multiply.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
    add     $sp, $sp, -4
    sw      $ra, 0($sp)
    addi    $a0, $0, 3
    addi    $a1, $0, 4
    jal     multiply
    nop
    lw      $ra, 0($sp)
    add     $sp, $sp, 4
    jr      $ra
    nop
    .end main

    .globl multiply
    .ent multiply
multiply:
# int multiply(int a, int b)
# {
#     return a * b;
        mult    $a0,$a1
        mflo    $v0
        j   $ra
        nop
 # }
    .end multiply
