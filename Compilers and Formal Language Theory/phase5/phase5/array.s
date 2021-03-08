.globl	main
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl 	$4, %esp
	movl	$10, -4(%ebp)
	pushl	-4(%ebp)
	call	init_array
	addl	$4, %ebp
	pushl	-4(%ebp)
	call	print_array
	addl	$4, %ebp
	movl	%ebp, %esp
	popl	%ebp
	ret
	.comm	a, 40
