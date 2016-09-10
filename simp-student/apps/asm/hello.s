    .set noreorder
    .data
foo:    .word 0xdecafbad
hello:  .asciiz "hello, world\n"

    .text
    .globl main
    .ent main
main:
        lui     $t0, %hi(foo)
        ori     $t0, $t0, %lo(foo)
        lw      $a0, 0($t0)
        ori     $v0, $0, 20
        syscall                     # print 0xdecafbad in hex and decimal

        lui     $a0, %hi(hello)
        ori     $a0, $a0, %lo(hello)
        ori     $v0, $0, 4
        syscall	        			# print "hello, world"

        ori $v0, $0, 10             # exit
        syscall
    .end main
