.set  MODE_USR, 0x10			
.set  MODE_FIQ, 0x11			
.set  MODE_IRQ, 0x12			
.set  MODE_SVC, 0x13			
.set  MODE_ABT, 0x17				
.set  MODE_UND, 0x1B			
.set  MODE_SYS, 0x1F				

.set  I_BIT, 0x80				
.set  F_BIT, 0x40	

.section .text

.globl _get_pc
_get_pc:
    	mov r0,lr
    	bx lr

.globl _get_irq_sp
_get_irq_sp:
   	msr cpsr_c, #MODE_IRQ|I_BIT|F_BIT 	
    	mov r0, sp
	
    	msr cpsr_c, #MODE_SVC|I_BIT|F_BIT
    	mov pc, lr
	
.globl _get_stack_pointer	
_get_stack_pointer:
    	str     sp, [sp]
    	ldr     r0, [sp]
    	mov     pc, lr


.globl _enable_interrupts	
_enable_interrupts:
	cpsie i
	mov pc, lr
	
.globl _disable_interrupts
_disable_interrupts:
	cpsid i
	mov pc, lr

	
.globl _get_cpsr
_get_cpsr:
	mrs     r0, cpsr
   	mov     pc, lr


.globl _set_sp
_set_sp:
	mov sp, r0
	bx lr

.globl _set_svc_mode
_set_svc_mode:
	msr cpsr_c, #MODE_SVC
	bx lr 
	
.globl _set_irq_mode
_set_irq_mode:
	msr cpsr_c, #MODE_IRQ
	bx lr 

.globl _set_usr_mode
_set_usr_mode:
	msr cpsr_c, #MODE_USR
	bx lr 

.globl PUT32
PUT32:
    	str r1, [r0]
    	bx lr

.globl GET32
GET32:
    	ldr r0, [r0]
    	bx lr

.globl _kernel_entry
_kernel_entry:
	push {r0-r11, lr}
	mrs r0, spsr
	push {r0}
	ldr r0, =kernel_entry
	bx r0

			
