	.file	1 "loop-test.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=32
	.module	nooddspreg
	.abicalls
	.option	pic0
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
$LC0:
	.ascii	"sum = %d\012\000"
	.text
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$sp,32,$31		# vars= 0, regs= 1/0, args= 16, gp= 8
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lui	$2,%hi(A)
	addiu	$2,$2,%lo(A)
	lui	$4,%hi(A+32)
	addiu	$4,$4,%lo(A+32)
	move	$5,$0
$L2:
	lw	$3,0($2)
	addiu	$2,$2,4
	bne	$2,$4,$L2
	addu	$5,$5,$3

	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	lui	$4,%hi($LC0)
	addiu	$4,$4,%lo($LC0)
	jal	tfp_printf
	nop

	move	$2,$0
	lw	$31,28($sp)
	nop
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.globl	A
	.data
	.align	2
	.type	A, @object
	.size	A, 32
A:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.ident	"GCC: (Sourcery CodeBench Lite 2016.05-8) 5.3.0"
