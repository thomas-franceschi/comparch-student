    .set noreorder
    .data
    #int A[8]
A: .space 32
    .text
    .globl main
#int main()
#{
    .ent main
main:
        #int i;
        #A[0] = 0;
        #A[1] = 1;
        add $s0, $0, $0     # i = 0
        la $t0, A           #load address of A[0]
        li $t1, 0           #load index (0)
        add $t2, $t1, $t0   #current = A[0]
        add $t3, $0, $0     #t3 = 0
        sw $t3, 0($t2)      #A[0] = 0
        addi $t2, $t2, 4    #A[1]
        addi $t3, $0, 1     #t3 = 1
        sw $t3, 0($t2)      #A[1] = 1

        addi $s0, $0, 2     #i = 2
        #for (i = 2; i < 8; i++) {
loop_cond:
        slti $t0, $s0, 8       # t0 = (i < 8)
        beq  $t0, $0, sequel    # _if (!t0) goto sequel
        nop
        lw $t4, 0($t2)          #t4 = A[n-1]
        addi $t2, $t2, -4
        lw $t5, 0($t2)
        #A[i] = A[i-1] + A[i-2];
        add $t6, $t4, $t5       #A[i] = A[i-1] + A[i - 2]
        addi $t2, $t2, 8        #A[i]
        sw $t6, 0($t2)          #stor A[i]
        add $a0, $0, $t6
        #PRINT_HEX_DEC(A[i]);
        ori $v0, $0, 20     # print in hex and decimal with newline.
        syscall
#     i = i + 1;
        addi $s0, $s0, 1        # s0 = s0 + 1
        j    loop_cond          # goto loop_cond
        nop
# }

sequel:
        ori $v0, $0, 10     # exit
        syscall
    .end main
