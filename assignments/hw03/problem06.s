    .set noreorder
    .data
A: .space 32
    .text
    .globl main
    .ent main
#void print(int a)
#{
    printcall:
        ori $v0, $0, 20     # print in hex and decimal with newline.
        syscall

        jr $ra
#}  

#int main()
#{
main:
        #int A[8];
        addi $a0, $0, 32
        ori $v0, $0, 9
        syscall

        #A[0] = 0;
        addi $t0, $0, 0
        sw $t0, 0($v0)      #A[0] = 0
        
        #A[1] = 1;
        addi $t0, $0, 1
        addi $t1, $v0, 4
        sw $t0, ($t1)      #A[1] = 1

        #int i;
        addi $s0, $0, 2     #i = 2
        #for (i = 2; i < 8; i++) {
loop_cond:
        slti $t0, $s0, 8       # t0 = (i < 8)
        beq  $t0, $0, sequel    # _if (!t0) goto sequel
        nop
        lw $t4, 0($t1)          #t4 = A[n-1]
        addi $t1, $t1, -4
        lw $t5, 0($t1)

        #A[i] = A[i-1] + A[i-2];
        add $t6, $t4, $t5       #A[i] = A[i-1] + A[i - 2]
        addi $t1, $t1, 8        #A[i]
        sw $t6, 0($t1)          #stor A[i]
        add $a0, $0, $t6

        #print(A[i])
        jal printcall

        #ori $v0, $0, 20     # print in hex and decimal with newline.
        #syscall
#     i = i + 1;
        addi $s0, $s0, 1        # s0 = s0 + 1
        j    loop_cond          # goto loop_cond
        nop
        #}
# }

sequel:
        ori $v0, $0, 10     # exit
        syscall
    .end main

