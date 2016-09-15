	.set noreorder
	.gnu_attribute 4, 1
	.text
	.globl	gcc_test
   # /*
   #  * gcc_test.c
   #  *
   #  *  Created on: Sep 14, 2016
   #  *      Author: Jay Brockman
   #  */
   # 
   # void foo(int);
   # 
   # void gcc_test(int a, int b)
   # {
	.ent	gcc_test
gcc_test:
		addiu	$sp,$sp,-32
		sw	$ra,28($sp)
   #     int x = 5;
   #     int y = 7;
   #     int z = a + b + x + y;
		addu	$a0,$a0,$a1
   #     foo(z);
		addiu	$a0,$a0,12
		jal	foo
		nop

   # }
		lw	$ra,28($sp)
		nop
		j	$ra
		addiu	$sp,$sp,32

	.end	gcc_test
