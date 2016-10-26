    .set noreorder
    .data
    #char A[] = { 1, 25, 7, 9, -1 };
A: .byte 1, 25, 7, 9, -1
    .text
    .globl main
#int main()
#{
    .ent main
main:
        #int i;
        #int current;
        #int max;
        add $s0, $0, $0     # i = 0
        la $t0, A           #load address of A[0]
        li $t1, 0           #load index (0)
        add $t2, $t1, $t0   #current = A[0]
        lb $t3, 0($t2)
        #while(current > 0)
        #if (current > max)
                #max = current;  
loop_cond:
        slti $t4, $t3, 1
        beq $t4, 1, sequel
        nop
        slt $t5, $s0, $t2
        beq $t5, $0, same_max
        add $s0, $0, $t3    # max = current
        nop
same_max:
        #i = i + 1;
        #current = A[i];
        addi $t2, $t2, 1    # i = i + 1
        lb $t3, 0($t2)      # current = A[i]
        j loop_cond
        nop

sequel:
        add $a0, $0, $s0
        ori $v0, $0, 20     # print in hex and decimal with newline.
        syscall

        ori $v0, $0, 10     # exit
        syscall
    .end main
