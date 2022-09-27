@ ---------------------------------------
@	Data Section
@ ---------------------------------------
	
	.data
	.balign 4
prompt1:	.asciz	"LANZATE EL NUMERO 1: "
prompt2:	.asciz	"QUE HAGO (1-SUMA, 2-RESTA, 3-MULTI, 4-DIV): "
prompt3:	.asciz	"ROLATE EL NUMERO 2: "
format:	.asciz	"%d"	
stringSuma: .asciz "\n%d + %d = %d\n"
stringResta: .asciz "\n%d - %d = %d\n"
stringMulti: .asciz "\n%d * %d = %d\n"
stringDiv: .asciz "\n%d / %d = %d\n"
n1:	.int	0		
n2:	.int	0
nopp:   .int    0

	
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

readOpp:
	push 	{ip, lr}	
				
	ldr	r0, =prompt2	
	bl	printf

	ldr     r0, =format	
	ldr	r1, =nopp	
	bl	scanf

        pop 	{ip, pc}	

readNum2:
	push 	{ip, lr}	
				
	ldr	r0, =prompt3	
	bl	printf

	ldr     r0, =format	
	ldr	r1, =n2		
	bl	scanf

        pop 	{ip, pc}
	
suma:
	push 	{ip, lr}	

        add	r3, r1, r2       
        ldr     r0, =stringSuma       
        bl      printf	

        pop 	{ip, pc}

resta:
	push 	{ip, lr}	

        sub	r3, r1, r2   
        ldr     r0, =stringResta      
        bl      printf	

        pop 	{ip, pc}
	
multi:
	push 	{ip, lr}	

        mul	r3, r1, r2       
        ldr     r0, =stringMulti      
        bl      printf	

        pop 	{ip, pc}

div:
	push 	{ip, lr}
	mov 	r3, r1
divLoop:
	add     r10, #1 
        subs	r3, r3, r2 
        bpl     divLoop
	sub	r10, #1

	mov 	r3, r10
   
	ldr     r0, =stringDiv 
        bl      printf	

        pop 	{ip, pc}

	

main:   push 	{ip, lr}

	mov 	r10, #0	

	bl	readNum1
	bl 	readOpp
	bl	readNum2
			
	ldr	r1, =n1		
	ldr	r1, [r1]

	ldr	r4, =nopp	
	ldr	r4, [r4]

	ldr	r2, =n2		
	ldr	r2, [r2]	

	subs	r4, #1
	BEQ     suma
	subs	r4, #1
	BEQ     resta
	subs	r4, #1
	BEQ     multi
	subs	r4, #1
	BEQ     div

        pop 	{ip, pc}	
