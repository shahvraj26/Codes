# BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT
# ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
# ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
# OR ONE OF OUR UNDERGRADUATE GRADERS. I WROTE THIS CODE BY HAND,
# IT IS NOT MACHINE GENRATED OR TAKEN FROM MACHINE GENERATED CODE.
# Vraj Shah Lab 6

.file "search.s"
.section .rodata

.printLargestString:
	.string "Search: The longest conversion is %d.\n"

.text
.globl search
        .type search, @function

search:
	pushq %rbp #Stack housekeeping #1
	movq %rsp, %rbp #Stack housekeeping #2

	pushq %rbx #Stores 1st parameter
	pushq %r12 #Stores max count
	pushq %r13 #Stores longest conversion
	pushq %r14 #Stores current pointer
	
	movq %rdi, %rbx #Stores %rdi into 1st paramater
	xorq %r12, %r12 #Set max count to 0
	xorq %r13, %r13 #Set longest convo to 0
	movq (%rbx), %r14 #Move pointer in 1st parameter into r14 register
	jmp largest_string #Jump to largest string

loop_start:
	movq %r14, %rdi #Move current pointer to 1st parameter
	call m_shim #Call middle Shim
	
	cmp %r12, %rax #Compare count to returned count
	cmovgq %rax, %r12 #If returned count is larger than %r12 count, set %r12 equal to returned count 
	cmovgq %r14, %r13 #Move current pointer into %r13, if larger than max count
	#Move current pointer to longest conversion. 
	leaq 8(%rbx), %rbx #point to next pointer
	movq (%rbx), %r14 #Get next pointer 	

largest_string:
	cmp $0, %r14 #Test if current pointer is NULL
	jne loop_start
		
	movq $.printLargestString, %rdi #Move string to 1st parameter
	movq %r12, %rsi #Move max count to 2nd parameter
	xorq %rax, %rax #Clear Register
	call print #Call print
	
	movq %r13, %rax #Move longest convo to return value
		
	popq %r14 #pop current pointer
	popq %r13 #pop longest conversation
	popq %r12 #pop max count
	popq %rbx #pop 1st paramater
	
	leave
	ret
.size search, .-search
