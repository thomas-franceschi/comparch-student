# prob2.s
    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
		addi  $4, $0, 7
		addi  $5, $0, 8
		addi  $6, $4, 3
		add   $7, $4, $5

# DO NOT EDIT BELOW THIS POINT
        ori $v0, $0, 10     # exit
        nop
        nop
        nop
        syscall
    .end main
