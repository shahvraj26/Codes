# BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT
# ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
# ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
# OR ONE OF OUR UNDERGRADUATE GRADERS. I WROTE THIS CODE BY HAND,
# IT IS NOT MACHINE GENRATED OR TAKEN FROM MACHINE GENERATED CODE.
# Vraj Shah Lab 6

.file "expand.s"
.section .rodata

.text
.globl expand
        .type expand, @function
.plus:
	.string "plus"

.minus:
	.string "minus"

.times:
	.string "times"

.divide:
	.string "divided by"

.equals: 
	.string "equals"

expand:
	pushq %rbp #save base pointer
	movq %rsp, %rbp #set base pointer

	movq %rsi, %rdx #save output pointer in %rdx

loop:
	movzbl (%rdi), %eax #fetch byte from input pointer, storing into eax
	incq %rdi #increment input pointer
	testb %al, %al #test if byte is NULL
	#Value has to be 0, which is why jz is used
	jz end_loop #if NULL run the null terminator loop

	cmpb $'+', %al #Compare character byte with byte
	je plus_loop #A conditional jump if it does equal byte value

        cmpb $'-', %al #Compare character byte with byte
        je minus_loop #A conditional jump if it does equal byte value

        cmpb $'*', %al #Compare character byte with byte
        je times_loop #A conditional jump if it does equal byte value

        cmpb $'/', %al #Compare character byte with byte
        je divide_loop #A conditional jump if it does equal byte value
	
        cmpb $'=', %al #Compare character byte with byte
        je equals_loop #A conditional jump if it does equal byte value

	#non special characters
	movb %al, (%rsi) #Move byte into output pointer
	incq %rsi #advance output pointer 1 byte
	jmp loop #recursively run

plus_loop:
	movq $.plus, %rcx #load expansion string into %rcx
	jmp expand_loop #Jump to expand loop after loading

minus_loop:
	movq $.minus, %rcx #load expansion string into %rcx
        jmp expand_loop #Jump to expand loop after loading

times_loop:
        movq $.times, %rcx #load expansion string into %rcx
        jmp expand_loop #Jump to expand loop after loading

divide_loop:
        movq $.divide, %rcx #load expansion string into %rcx
        jmp expand_loop #Jump to expand loop after loading

equals_loop:
        movq $.equals, %rcx #load expansion string into %rcx
        jmp expand_loop #Jump to expand loop after loading

expand_loop:
        movzbl (%rcx), %eax #fetch byte from input pointer, storing into eax
        testb %al, %al #test if byte is NULL
        #Value has to be 0, which is why jz is used
        jz loop #if NULL run the null terminator loop

        #non special characters
        movb %al, (%rsi)
        incq %rsi #advance output pointer 1 byte
        incq %rcx #advance expansion pointer 1 byte
        jmp expand_loop #recursively run

end_loop:
	movb $0, (%rsi) #Null Terminator byte into output pointer
	incq %rsi #increment output pointer
	subq %rdx, %rsi #calculate number of bytes copied
	movq %rsi, %rax #return number of bytes copied
	        
	leave #undo the stack frame
        ret #give back control to caller
.size expand, .-expand #required directive

