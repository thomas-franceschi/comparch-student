    .set noreorder
    .data

    .text
    .globl main
    .ent main
main:
        #int score = 84;
        addi $s0, $0, 84        # score = 84
        addi $s1, $0, 90        # s1 = 90
        addi $s2, $0, 80        # s2 = 80
        addi $s3, $0, 70        # s3 = 70

        #if (score >= 90)
            #grade = 4;
        slt $t0, $s0, $s1       # t0 = ( s0 < 90)
        beq $t0, 1, three       #if score less than 90 jump to three
        addi $s4, $0, 4         # grade = 4
        j print
        nop

three:  

        #else if (score >= 80)
            #grade = 3;
        slt $t1, $s0, $s2
        beq $t1, 1, two         #if score less than 80 jump to 2
        addi $s4, $0, 3         # grade = 3
        j print
        nop

two:

        #else if (score >= 70)
            #grade = 2;
        slt $t2, $s0, $s3
        beq $t2, 1, zero        # if score less than 
        addi $s4, $0, 2         #grade = 2
        j print
        nop

zero:
    #else
        #grade = 0;
    addi $s4, $0, 0             #grade = 0
    j print
    nop

print:
        #PRINT_HEX_DEC(grade);
        add $a0, $0, $s4    #return grade
        ori $v0, $0, 20     # print in hex and decimal with newline.
        syscall

        #EXIT;
        ori $v0, $0, 10     # exit
        syscall
    .end main
