	.cpu cortex-a57+fp+simd+crypto+crc
	.file	"foo.c"
	.text
	.align	2
	.global	foo
	.type	foo, %function
foo:
	sub	sp, sp, #16
	str	w0, [sp,12]
	str	w1, [sp,8]
	ldr	w1, [sp,12]
	ldr	w0, [sp,8]
	add	w0, w1, w0
	add	sp, sp, 16
	ret
	.size	foo, .-foo
	.ident	"GCC: (Sourcery CodeBench Lite 2014.11-95) 4.9.1"
	.section	.note.GNU-stack,"",%progbits
