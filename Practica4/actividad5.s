@ ---------------------------------------
@	Data Section
@ ---------------------------------------
	
	.data
	.balign 4
prompt1:	.asciz	"Cuanto vale X: "
format:	.asciz	"%d"	
string: .asciz "\n6x^2 + 9x + 2 = %d\n"
n1:	.int	0		

	
@ ---------------------------------------
@	Code Section
@ ---------------------------------------
	
	.text
	.global main
	.extern printf
	.extern	scanf

readNum1:
	push 	{ip, lr}	
				
	ldr	r0, =prompt1	
	bl	printf

	ldr     r0, =format	
	ldr	r1, =n1		
	bl	scanf	

        pop 	{ip, pc}


main:   push 	{ip, lr}	

	bl	readNum1

			
	ldr	r1, =n1		
	ldr	r1, [r1]

	mov	r6, r1

	mul	r9, r6, r1

	mov	r6, #6
	
	mov	r5, r9

	mul	r9, r5, r6

	mov	r6, #9

	mul	r8, r1, r6

	add	r7, r8, r9

	add 	r1, r7, #2

        ldr    r0, =string       
        bl     printf		
	

        pop 	{ip, pc}	
