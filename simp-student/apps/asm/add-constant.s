# add-constant.s
    .set noreorder
    .data
x:  .word -2
y:  .word

    .text
    .globl main
    .ent main
main:
# y = x + 5
        lui     $t0, %hi(x)        # t0 = &x
        ori     $t0, $t0, %lo(x)
        lw      $t1, 0($t0)        # t1 = x
        addi    $t2, $t1, 5        # t2 = x + 5
        lui     $t3, %hi(y)        # t3 = &y
        ori     $t3, $t3, %lo(y)
        sw      $t2, 0($t3)        # y = t2

        ori $v0, $0, 10            # exit
        syscall
    .end main
