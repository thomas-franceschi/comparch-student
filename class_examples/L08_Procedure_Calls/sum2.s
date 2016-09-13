# sum2.s
    .set noreorder
    .data

    .text
    .globl sum2
    .ent sum2
sum2:
# int sum2(int x, int y)
# {
#     return x + y;
        add     $v0, $a0, $a1   # v0 = a0 + a1
        jr      $ra             # return
        nop
# }
    .end sum2

    .globl main
    .ent main
main:
# int main()
# {
#     int x = 5;
        addi    $a0, $0, 5      # $a0 = 5
#     int y = 7;
        addi    $a1, $0, 7      # $a1 = 7
#     int z;
        # t0
#
#     z = sum2(x, y);
        jal     sum2            # call sum2
        nop
        add     $t0, $v0, $0    # t0 = v0

        ori $v0, $0, 10         # exit
        syscall
# }
    .end main
