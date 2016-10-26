    .set noreorder
    .data
    #typedef struct record {
 #int field0;
 #int field1;
#} record;
record: .word 0, 0
    .text
    .globl main

#int main()
#{
    .ent main
main:
        #record *r = (record *) MALLOC(sizeof(record));
        addi $a0, $0, 8
        ori $v0, $0, 9
        syscall
        #r->field0 = 100;
        addi $t0, $0, 100
        sw $t0, 0($v0)
        #r->field1 = -1;
        addi $t0, $0, -1
        sw $t0, 4($v0)
        #EXIT;
        ori $v0, $0, 10     # exit
        syscall
    .end main
