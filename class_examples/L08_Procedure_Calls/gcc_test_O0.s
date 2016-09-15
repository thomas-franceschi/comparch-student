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
		addiu	$sp,$sp,-48
		sw	$ra,44($sp)
		sw	$fp,40($sp)
		move	$fp,$sp
		sw	$a0,48($fp)
		sw	$a1,52($fp)
   #     int x = 5;
		li	$v0,5			# 0x5
		sw	$v0,24($fp)
   #     int y = 7;
		li	$v0,7			# 0x7
		sw	$v0,28($fp)
   #     int z = a + b + x + y;
		lw	$v1,48($fp)
		lw	$v0,52($fp)
		nop
		addu	$v1,$v1,$v0
		lw	$v0,24($fp)
		nop
		addu	$v1,$v1,$v0
		lw	$v0,28($fp)
		nop
		addu	$v0,$v1,$v0
		sw	$v0,32($fp)
   #     foo(z);
		lw	$a0,32($fp)
		jal	foo
		nop

   # }
		move	$sp,$fp
		lw	$ra,44($sp)
		lw	$fp,40($sp)
		addiu	$sp,$sp,48
		j	$ra
		nop

	.end	gcc_test
