    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
        addi $a0, $0, 7
        addi $a1, $0, 9
# int addsub(int a, int b)
# {
#     int x = 5;
        addi $s0, $0, 5
#     int y = 4;
        addi $s1, $0, 4
#     return (a + x) – (b + y);
        add $t0, $a0, $s0
        add $t1, $a1, $s1
        sub $v0, $t0, $t1
# }


        ori $v0, $0, 10     # exit
        syscall
    .end main
