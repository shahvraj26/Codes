# BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT
# ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
# ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
# OR ONE OF OUR UNDERGRADUATE GRADERS. I WROTE THIS CODE BY HAND,
# IT IS NOT MACHINE GENRATED OR TAKEN FROM MACHINE GENERATED CODE.
# Vraj Shah Lab6

.file "middle.s"
.section .rodata

.printMiddle:
	.string "Expanding %s\n"

.printStringLong:
	.string "%d bytes to expand '%s' to '%s'\n"

.text
.globl middle
	.type middle, @function

middle:
	pushq %rbp #Stack housekeeping 1: push rbp to stack
	movq %rsp, %rbp #Stack housekeeping 2: set rbp to current stack pointer
	
	subq $1024, %rsp #Allocate 1024 bytes to output buffer	

	pushq %rbx #Push callee saved register
	pushq %r12 #Push callee saved register	
	leaq 16(%rsp), %r12 #Moves pointer to output buffer into second parameter

	movq %rdi, %rbx #Hold the rbx value in input pointer string
	movq %rdi, %rsi #move the address of the second parameter into %rsi

	#.string "Expanding %s\n"
	movq $.printMiddle, %rdi #Load the address of printMiddle to rdi
	xorq %rax, %rax #clear rax register
	call print #call print function to print printMiddle
	
	movq %rbx, %rdi #Moves pointer to input string in first parameter
	movq %r12, %rsi #Moves pointer to output buffer into second parameter
	call ex_shim #call ex_shim
	
	movq $.printStringLong, %rdi #Add printStringLong into rdi
	movq %rax, %rsi #Put bytes into first parameter
	movq %rbx, %rdx #Moves pointer to input string in second parameter
	movq %rax, %rbx #Moves and saves callee save register from ex_shim
	movq %r12, %rcx #Moves output buffer into third parameter	

	xorq %rax, %rax # clear rax register
        call print #call print on printDecode

	movq %rbx, %rax #Move the last return value to rax
	
	popq %r12 #frees r12
	popq %rbx #Pop rbx from stack

	leave #restore stack pointer and base poiner 
	ret #Return the last value in rax
.size middle, .-middle
	
