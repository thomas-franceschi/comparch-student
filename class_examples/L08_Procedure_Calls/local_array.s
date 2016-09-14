# local_array.s
    .set noreorder
    .data

    .text
    .globl swap
    .ent swap
swap:
# void swap(int *A, int x, int y)
# {
        # PUSH s0 (4 bytes)
        addi    $sp, $sp, -4        # sp = sp - 4
        sw      $s0, 0($sp)         # *(sp) = s0
#     int temp;
        # temp = s0
#     temp = A[x];
        # convert x to byte offset
        sll     $t0, $a1, 2         # t0 = a1 << 2
        # add byte offset to A
        add     $t1, $a0, $t0       # t1 = &A[x] = (a0 + t0)
        lw      $s0, 0($t1)         # s0 = A[x] = *(t1)
#     A[x] = A[y];
        # convert y to byte offset
        sll     $t2, $a2, 2         # t2 = a2 << 2
        # add byte offset to A
        add     $t3, $a0, $t2       # t3 = &A[y] = (a0 + t2)
        lw      $t4, 0($t3)         # t4 = A[y] = *(t3)
        sw      $t4, 0($t1)         # *(t1) = t4
#     A[y] = temp;
        sw      $s0, 0($t3)         # *(t3) = s0
        # POP s0 (4 bytes)
        lw      $s0, 0($sp)         # s0 = *(sp)
        add     $sp, $sp, 4         # sp = sp + 4
        jr      $ra                 # return
        nop
# }
    .end swap


    .globl main
    .ent main
main:
# int main()
# {
        # PUSH ra, A[4] (20 bytes)
        add     $s0, $sp, -20       # sp = sp - 20
        sw      $ra, 16($sp)        # *(sp+16) = ra
#     int array[4] = { 0xa, 0xb, 0xc, 0xd};
        add     $s1, $0, $sp        # s1 = A    NEED TO PRESERVE!!!
        addi    $t1, $0, 0xa        # t1 = 0xa
        sw      $t1, 0($s1)         # *(s1) = t1
        addi    $t1, $0, 0xb        # t1 = 0xb
        sw      $t1, 4($s1)         # *(s1+4) = t1
        addi    $t1, $0, 0xc        # t1 = 0xc
        sw      $t1, 8($s1)         # *(s1+8) = t1
        addi    $t1, $0, 0xd        # t1 = 0xd
        sw      $t1, 12($s1)        # *(s1+12) = t1
#     printf("0x%1$x  (%1$d)\n", array[0]);
        lw      $a0, 0($s1)         # a0 = *(s1)
        ori     $v0, $0, 20         # syscall 20
        syscall
#     swap(array, 0, 3);
        add     $a0, $s1, $0        # a0 = A
        addi    $a1, $0, 0          # a1 = 0
        addi    $a2, $0, 3          # a1 = 3
        jal     swap                # call swap
        nop
#     printf("0x%1$x  (%1$d)\n", array[0]);
        lw      $a0, 0($s1)         # a0 = *(s1)
        ori     $v0, $0, 20         # syscall 20
        syscall
        # POP ra, A[4] (20 bytes)
        lw      $ra, 16($sp)        # ra = *(sp+16)
        addi    $sp, $sp, 20        # sp = sp + 20
        jr      $ra                 # return
        nop
# }
    .end main
