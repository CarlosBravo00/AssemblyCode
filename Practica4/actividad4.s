@ ---------------------------------------
@	Data Section
@ ---------------------------------------
	
	.data
	.balign 4
prompt1:	.asciz	"QUE HAGO (1-SUMA, 2-RESTA, 3-MULTI, 4-DIV): "
prompt2:	.asciz	"LANZATE EL NUMERO 1: "
prompt3:	.asciz	"ECHATE EL NUMERO 2: "
prompt4:	.asciz	"ROLATE EL NUMERO  3: "
format:	.asciz	"%d"	
stringIgual: .asciz "\nIGUAL A %d\n"
stringSuma: .asciz "\n%d + %d + %d = %d\n"
stringResta: .asciz "\n%d - %d - %d = %d\n"
stringMulti: .asciz "\n%d * %d * %d = %d\n"
stringDiv: .asciz "\n%d / %d / %d = %d\n"
n1:	.int	0		
n2:	.int	0
n3:	.int	0
nopp:   .int    0

	
@ ---------------------------------------
@	Code Section
@ ---------------------------------------
	
	.text
	.global main
	.extern printf
	.extern	scanf


readOpp:
	push 	{ip, lr}	
				
	ldr	r0, =prompt1
	bl	printf

	ldr     r0, =format	
	ldr	r1, =nopp	
	bl	scanf

        pop 	{ip, pc}

readNum1:
	push 	{ip, lr}	
				
	ldr	r0, =prompt2	
	bl	printf

	ldr     r0, =format	
	ldr	r1, =n1		
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

readNum3:
	push 	{ip, lr}	
				
	ldr	r0, =prompt4	
	bl	printf

	ldr     r0, =format	
	ldr	r1, =n3	
	bl	scanf

        pop 	{ip, pc}
	
suma:
	push 	{ip, lr}	

        add	r7, r1, r2      
	add 	r1, r7, r3 
        ldr     r0, =stringIgual       
        bl      printf	

        pop 	{ip, pc}

resta:
	push 	{ip, lr}	

        sub	r7, r1, r2   
	sub 	r1, r7, r3
        ldr     r0, =stringIgual      
        bl      printf	

        pop 	{ip, pc}
	
multi:
	push 	{ip, lr}	

        mul	r7, r1, r2      
	mul 	r1, r7, r3      
        ldr     r0, =stringIgual      
        bl      printf	

        pop 	{ip, pc}

div:
	push 	{ip, lr}
divLoop1:
	add     r10, #1 
        subs	r1, r1, r2 
        bpl     divLoop1
	sub	r10, #1

divLoop2:
	add     r11, #1 
        subs	r10, r10, r3 
        bpl     divLoop2
	sub	r11, #1
	
	mov r1, r11
	ldr     r0, =stringIgual 
        bl      printf	

        pop 	{ip, pc}

	

main:   push 	{ip, lr}

	mov 	r10, #0	
	mov  	r11, #0

	bl 	readOpp
	bl	readNum1
	bl	readNum2			
	bl	readNum3

	ldr	r9, =nopp	
	ldr	r9, [r9]

	ldr	r1, =n1		
	ldr	r1, [r1]

	ldr	r2, =n2		
	ldr	r2, [r2]	

	ldr	r3, =n3		
	ldr	r3, [r3]	

	subs	r9, #1
	BEQ     suma
	subs	r9, #1
	BEQ     resta
	subs	r9, #1
	BEQ     multi
	subs	r9, #1
	BEQ     div

        pop 	{ip, pc}
	