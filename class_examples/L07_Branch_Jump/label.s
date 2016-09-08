# label.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
        addi $s0, $0, 100
        addi $t0, $0, 5
        addi $t1, $0, 4
        bne  $t0, $t1, L1
        nop
        addi $s0, $0, 200

 L1:    addi $s1, $0, 300
        addi $s2, $0, 400

        ori $v0, $0, 10     # exit
        syscall
    .end main
