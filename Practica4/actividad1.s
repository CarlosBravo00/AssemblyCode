@ ---------------------------------------
@	Data Section
@ ---------------------------------------
	
	.data
	.balign 4	
string: .asciz "\nAddress memory %x\n"
stringY: .asciz "\nValue %x\n"
y:	.word	0
a:      .word 	0xAAAAAAAA
b:      .word 	0xBBBBBBBB
c:   	.word 	0xCCCCCCCC

	
@ ---------------------------------------
@	Code Section
@ ---------------------------------------
	
.text
.global main
.extern printf

storeVal:
        push    {ip, lr}

        str    	r2, [r1]        
	
        pop     {ip, pc}


storeRef:
	push	{ip, lr}

        ldr     r2, [r2]
        str    	r2, [r1] 

	pop	{ip, pc}

storeImp:
	push	{ip, lr}

        ldr     r2, =c   
        ldr     r2, [r2]
        str    	r2, [r1] 

	pop	{ip, pc}


@ ---------	------------------------------
main:	        
        push   {ip, lr}       

        ldr    r1, =y		
        ldr    r0, =string       
        bl     printf		@ print direcc
        ldr    r1, =y		

        ldr     r2, =a          
        ldr     r2, [r2]
        bl      storeVal

	ldr     r1, [r1]
        ldr    r0, =stringY       
        bl     printf		
        ldr    r1, =y	

        ldr    r1, =a		
        ldr    r0, =string       
        bl     printf		@ print direcc
        ldr    r1, =y	

        ldr     r2, =b          
        bl      storeRef

	ldr     r1, [r1]
        ldr    r0, =stringY       
        bl     printf		
        ldr    r1, =y

        ldr    r1, =b		
        ldr    r0, =string       
        bl     printf		@ print direcc
        ldr    r1, =y		

        ldr     r2, =b          
        bl      storeImp

	ldr     r1, [r1]
        ldr    r0, =stringY       
        bl     printf		
        ldr    r1, =y	

        ldr    r1, =c	
        ldr    r0, =string       
        bl     printf		@ print direcc
        ldr    r1, =y	

        pop    {ip, pc}          @ pop return address into pc
