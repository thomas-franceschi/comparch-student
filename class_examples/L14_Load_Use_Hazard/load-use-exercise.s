# load-use-exercise.s
    .set noreorder
    .data
A:  .word 3, 5, 0, 0

    .text
    .globl main
    .ent main
main:
        lui     $t0, %hi(A)
        ori     $t0, $t0, %lo(A)
        lw      $t1, 0($t0)
        lw      $t2, 4($t0)
        add     $t3, $t1, $t2
        sw      $t3, 8($t0)
        lw      $t1, 12($t0)

        ori $v0, $0, 10     # exit
        nop
        nop
        nop
        syscall
    .end main
