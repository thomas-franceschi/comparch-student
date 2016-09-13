# nonleaf_right.s
    .set noreorder
    .data

    .text

    .globl shift
    .ent shift
shift:
# int shift(int x)
# {
        # PUSH s0 (4 bytes)
        addi    $sp, $sp, -4;
        sw      $s0, 0($sp)
#     int y = 2;
        addi    $s0, $0, 2          # s0 = 2
#     return x << y;
        sllv    $v0, $a0, $s0       # v0 = a0 << s0
        # POP s0 (4 bytes)
        lw      $s0, 0($sp)
        addi    $sp, $sp, 4
        jr      $ra                 # return
        nop
# }
    .end shift


    .globl shift_add
    .ent shift_add
shift_add:
# int shift_add(int x)
# {
        # PUSH ra, s0 (8 bytes)
        addi    $sp, $sp, -8
        sw      $ra, 4($sp)
        sw      $s0, 0($sp)
#     int y = 7;
        addi    $s0, $0, 7          # s0 = 7
#     return shift(x) + shift(y);
        jal     shift               # v0 = call shift;
        nop
        add     $t0, $v0, $0        # t0 = v0
        add     $a0, $s0, $0        # a0 = s0
        jal     shift               # call shift
        nop
        add     $v0, $v0, $t0       # v0 = v0 + t0
        # POP ra, s0 (8 bytes)
        lw      $ra, 4($sp)
        lw      $s0, 0($sp)
        addi    $sp, $sp, 8
        jr      $ra                 # return
        nop
# }
    .end shift_add


    .globl main
    .ent main
main:
# int main()
# {
        # PUSH ra, s0 (8 bytes)
        addi    $sp, $sp, -8
        sw      $ra, 4($sp)
        sw      $s0, 0($sp)
#     int x = 5;
        addi    $s0, $0, 5          # s0 = 5
#     int z = shift_add(x);
        add     $a0, $s0, $0        # a0 = s0
        jal     shift_add           # v0 = call shift_add
        nop
        add     $t0, $v0, $0        # t0 = v0
#     PRINT_HEX_DEC(x);
        add     $a0, $s0, $0        # a0 = s0
        ori     $v0, $0, 20         # v0 = 20
        syscall                     # syscall
#     PRINT_HEX_DEC(z);
        add     $a0, $t0, $0        # a0 = $t0
        syscall                     # syscall
        # POP ra, s0 (8 bytes)
        lw      $ra, 4($sp)
        lw      $s0, 0($sp)
        addi    $sp, $sp, 8
        jr      $ra                 # return
        nop

# }
    .end main
