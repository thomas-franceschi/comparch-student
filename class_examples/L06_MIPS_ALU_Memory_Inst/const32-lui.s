# const32-lui.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
        lui $s1, 0xdeca
        ori $s1, $s1, 0xfbad

        ori $v0, $0, 10     # exit
        syscall
    .end main
