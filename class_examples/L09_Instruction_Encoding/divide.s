# multiply.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
    add     $sp, $sp, -4
    sw      $ra, 0($sp)
    addi    $a0, $0, 17
    addi    $a1, $0, 5
    jal     divide
    nop
    lw      $ra, 0($sp)
    add     $sp, $sp, 4
    jr      $ra
    nop
    .end main

    .globl divide
    .ent divide
divide:
# int divide(int a, int b)
# {
#     return a / b;
        div $a0,$a1
        mflo    $v0
        j       $ra
        nop
# }
    .end divide
