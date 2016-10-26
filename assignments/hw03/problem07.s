    .set noreorder
    .data

    .text
    .globl main

#void print(int a)
#{
    .ent print
print:
        ori     $v0, $0, 20     # print in hex and decimal with newline.
        syscall
        jr      $ra
        nop
    .end print
#}

#int sum3(int a, int b, int c)
#{
    .ent sum3
sum3:
        addi    $sp, $sp, -4
        sw      $s0, 0($sp)
        lw      $t0, 4($sp)
        lw      $t1, 8($sp)
        
        #return a+b+c;
        add     $s0, $t0, $t1
        add     $s0, $s0, $a3
        add     $v0, $0, $s0
        lw      $s0, 0($sp)
        
        addi    $sp, $sp, 4
        jr      $ra
        nop
    .end sum3
#}

#int polynomial(int a, int b, int c, int d, int e)
#{
    .ent polynomial
polynomial:
        #int x;
        #int y;
        #int z;
        addi $sp, $sp, -16
        sw $ra, 12($sp)
        sw $s0, 8($sp)
        lw $t0, 16($sp)

        #x = a << b;
        sllv    $t0, $t0, $a0   #t0 = a << b
        #y = c << d;
        sllv    $t1, $a1, $a2   #t1 = c << d
        sw      $t0, 4($sp)
        sw      $t1, 0($sp)
        #y = c << d;
        jal     sum3
        nop
        
        #print(x);
        add     $s0, $0, $v0
        lw $t0, 4($sp)
        add $a0, $0, $t0
        jal print
        nop
        
        #print(y);
        lw $t1, 0($sp)
        add $a0, $0, $t1
        jal print
        nop
        
        #print(z);
        add $a0, $0, $s0

        #return z;
        add $v1, $0, $a0
        jal print
        nop

        lw $ra, 12($sp)
        addi $sp, $sp, 16
        jr      $ra
    .end polynomial
#}



#int main()
#{
    .ent main
main:
        addi    $sp, $sp, -12
        sw      $ra, 8($sp)
        sw      $s0, 4($sp)

        #int a = 2;
        addi    $t0, $0, 2
        sw      $t0, 0($sp)    #a = 2
        addi    $a0, $0, 3     #b = 3
        addi    $a1, $0, 4     #c = 4    
        addi    $a2, $0, 5     #d = 5
        addi    $a3, $0, 6     #e = 6

        #int f = polynomial(a, 3, 4, 5, 6);
        jal     polynomial
        nop

        #print(a);
        lw $t2, 0($sp)
        add $a0, $0, $t2
        jal print
        nop

        #print(f);
        add $a0, $0, $v1
        jal print
        nop
        
        lw $ra, 8($sp)
        lw $s0, 4($sp)
        addi $sp, $sp,12
        
        
        ori     $v0, $0, 10     # exit
        syscall
    .end main
