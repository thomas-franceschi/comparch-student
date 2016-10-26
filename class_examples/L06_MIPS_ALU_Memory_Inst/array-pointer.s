# array-pointer.s
    .set noreorder
    .data
# int A[1024];
A:  .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
    .space 4048

    .text
    .globl main
    .ent main
main:
# int main()
# {
#     int x = A[10];
        lui     $t0, %hi(A)         # t0 = A
        ori     $t0, $t0, %lo(A)
        # s0 = A[10]
        lw      $s0, 40($t0)
#     *(A + 5) = x;
        sw      $s0, 20($t0)
# }

        ori $v0, $0, 10     # exit
        syscall
    .end main
