    .set noreorder
    .data
hello: .asciiz "hello, world\n"

    .text
    .globl main
    .ent main
main:
        addi $a0, $0, -1
        ori $v0, $0, 20     # print -1 in hex and decimal with newline.
        syscall

        ori $a0, $0, 7
        ori $v0, $0, 1
        syscall				# print integer

        ori $a0, $0, 0x0a
        ori $v0, $0, 11
        syscall				# print '\n'

        la $a0, hello
        ori $v0, $0, 4
        syscall				# print "hello, world"

        ori $a0, $0, 4
        ori $v0, $0, 9
        syscall				# alloc memory

        ori $a0, $0, 4
        ori $v0, $0, 9
        syscall				# alloc memory (again)
        nop
        nop

        ori $v0, $0, 10
        syscall         	# exit
    .end main
