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
	.section	.text.startup,"ax",@progbits
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
	addiu	$6,$2,%lo(A)
	lw	$5,%lo(A)($2)
	lw	$4,4($6)
	lw	$3,8($6)
	lw	$2,12($6)
	addu	$4,$5,$4
	addu	$4,$4,$3
	lw	$5,16($6)
	addu	$3,$4,$2
	lw	$2,20($6)
	addu	$3,$3,$5
	lw	$4,24($6)
	addu	$2,$3,$2
	lw	$5,28($6)
	addu	$2,$2,$4
	lui	$4,%hi($LC0)
	addiu	$sp,$sp,-32
	addu	$5,$2,$5
	sw	$31,28($sp)
	jal	tfp_printf
	addiu	$4,$4,%lo($LC0)

	lw	$31,28($sp)
	move	$2,$0
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
