# const32.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
        ori $s1, $0, 0xabcd
        sll $s1, $s1, 16
        ori $s1, $s1, 0x1234

        ori $v0, $0, 10     # exit
        syscall
    .end main
