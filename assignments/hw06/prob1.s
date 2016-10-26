# prob1.s
    .set noreorder
    .data
A:  .word 4

    .text
    .globl main
    .ent main
main:
        addi    $3, $0, 7
        lui     $4, %hi(A)
        ori     $4, $4, %lo(A)
        lw      $5, 0($4)
        add     $6, $5, $3
        ori     $v0, $0, 10     # exit

# DO NOT EDIT BELOW THIS POINT
        nop
        nop
        nop
        syscall
    .end main
