    .set noreorder
    .data
    #typedef struct elt {
 #int value;
 #struct elt *next;
#} elt;
elt: .word 0, 0
    .text
    .globl main

#int main()
#{
    .ent main
main:
        #elt *head;
        #elt *newelt;
        #newelt = (elt *) MALLOC(sizeof (elt));
        addi $a0, $0, 16
        ori $v0, $0, 9
        syscall
        #newelt->value = 1;
        #newelt->next = 0;
        #head = newelt;
        addi $t0, $0, 1
        sw $t0, 0($v0)      #value = 1

        addi $t0, $v0, 8
        sw $t0, 4($v0)      #next 

        #newelt = (elt *) MALLOC(sizeof (elt));
        #newelt->value = 2;
        #newelt->next = head;
        #head = newelt;
        addi $t1, $0, 2
        sw $t1, 8($v0)
        sw $0, 12($v0)


        
        

        #PRINT_HEX_DEC(head->value);
        lw $a0, 0($v0)
        ori $v0, $0, 20     # print in hex and decimal with newline.
        syscall
        #PRINT_HEX_DEC(head->next->value);
        lw $a0, 0($t0)
        ori $v0, $0, 20     # print in hex and decimal with newline.
        syscall

        ori $v0, $0, 10     # exit
        syscall
    .end main
