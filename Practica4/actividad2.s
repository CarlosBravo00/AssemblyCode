@ ---------------------------------------
@	Data Section
@ ---------------------------------------
	
	.data
	.balign 4
prompt1:	.asciz	"LANZATE EL NUMERO 1: "
prompt2:	.asciz	"ROLATE EL NUMERO 2: "
format:	.asciz	"%d"	
string: .asciz "\n%d + %d = %d\n"
n1:	.int	0		
n2:	.int	0

	
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

readNum2:
	push 	{ip, lr}	
				
	ldr	r0, =prompt2	
	bl	printf

	ldr     r0, =format	
	ldr	r1, =n2		
	bl	scanf

        pop 	{ip, pc}
	


main:   push 	{ip, lr}	

	bl	readNum1
	bl	readNum2
			
	ldr	r1, =n1		
	ldr	r1, [r1]

	ldr	r2, =n2		
	ldr	r2, [r2]	

        add	r3, r1, r2       
        ldr    r0, =string       
        bl     printf		
	

        pop 	{ip, pc}	
