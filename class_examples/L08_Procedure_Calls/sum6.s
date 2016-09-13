# sum6.s
    .set noreorder
    .data

    .text
    .globl sum6
    .ent sum6
sum6:
# int sum6(int a, int b, int c, int d, int e, int f)
# {
        # PUSH s0 (4 bytes)
        addi    $sp, $sp, -4
        sw      $s0, 0($sp)
#     int y = a+b+c+d+e+f;  // force use of $s0 (by our rules!)
        # y = s0
        add     $s0, $a0, $a1       # s0 = a0 + a1
        add     $s0, $s0, $a2       # s0 = s0 + a2
        add     $s0, $s0, $a3       # s0 = s0 + a3
        lw      $t0, 4($sp)         # t0 = *(sp+4)
        add     $s0, $s0, $t0       # s0 = s0 + t0
        lw      $t0, 8($sp)         # t0 = *(sp+8)
        add     $s0, $s0, $t0       # s0 = s0 + t0
#     return y;
        add     $v0, $s0, $0        # v0 = s0
        # POP s0 (4 bytes)
        lw      $s0, 0($sp)
        addi    $sp, $sp, 4
        jr      $ra                 # return
        nop
# }
    .end sum6

    .globl PRINT_HEX_DEC
    .ent PRINT_HEX_DEC
PRINT_HEX_DEC:
        # syscall 20
        ori     $v0, $0, 20
        syscall
        jr      $ra
        nop
    .end PRINT_HEX_DEC

    .globl main
    .ent main
main:
# int main()
# {
        # PUSH ra, s0, space for parameters f, e (16 bytes)
        add     $sp, $sp, -16
        sw      $ra, 12($sp)
        sw      $s0, 8($sp)
#     int y = sum6(1, 2, 3, 4, 5, 6);
        addi    $a0, $0, 1          # a0 = 1
        addi    $a1, $0, 2          # a1 = 2
        addi    $a2, $0, 3          # a2 = 3
        addi    $a3, $0, 4          # a3 = 4
        addi    $t0, $0, 5          # t0 = 5
        sw      $t0, 0($sp)         # *(sp) = t0
        addi    $t0, $0, 6          # t0 = 6
        sw      $t0, 4($sp)         # *(sp+4) = t0
        jal     sum6                # v0 = call sum6
        nop
        add     $s0, $v0, $0        # s0 = v0
#     PRINT_HEX_DEC(y);
        add     $a0, $s0, $0        # a0 = s0
        jal     PRINT_HEX_DEC       # call PRINT_HEX_DEC
        nop
        # POP ra, s0, space for  parameters f, e (16 bytes)
        lw      $ra, 12($sp)
        lw      $s0, 8($sp)
        add     $sp, $sp, 16
        jr      $ra                 # return
        nop
# }
    .end main
