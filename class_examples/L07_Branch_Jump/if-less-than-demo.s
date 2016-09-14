# if-less-than-demo.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
# int main()
# {
#     int x = 2;
        addi $s0, $0, 2      # s0 = 2
#     int y = 1;
        addi $s1, $0, 1    # s1 = 1
#     int p;
        # s2 = p
#     int q;
        # s3 = q
#
#     if_ (x < y)
        slt $t0, $s0, $s1   # t0 = (x < y)
        beq $t0, $0, sequel # if_(!t0) goto sequel
        nop
#
  p = 5;
        addi $s2, $s0, 5    # s2 = 5
sequel:
#     q = 7;
        addi $s3, $0, 7     # s3 = 7
# }
        ori $v0, $0, 10     # exit
        syscall
    .end main
