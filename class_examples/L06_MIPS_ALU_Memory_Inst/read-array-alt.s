# read-array-alt.s
    .set noreorder
    .data
# int A[1024];
A: .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
.space 4008

    .text
    .globl main
    .ent main
main:
        ori $a0, $0, 2
# int read_array(int i)
# {
#     return A[i+5];
# }
        lui     $t0, %hi(A)         # t0 = A
        ori     $t0, $t0, %lo(A)
        sll     $t1, $a0, 2         # t1 = 4*i (byte offset)
        add     $t0, $t0, $t1       # t0 = &A[i]
        lw      $v0, 20($t0)        # v0 = A[i+5]

        ori     $v0, $0, 10         # exit
        syscall
    .end main
