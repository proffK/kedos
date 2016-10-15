//  Part of the Raspberry-Pi Bare Metal Tutorials
//  Copyright (c) 2013, Brian Sidebotham
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice,
//      this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.

.section ".text.boot"

.globl _start

// From the ARM ARM (Architecture Reference Manual). Make sure you get the
// ARMv5 documentation which includes the ARMv6 documentation which is the
// correct processor type for the Broadcom BCM2835. The ARMv6-M manuals
// available on the ARM website are for Cortex-M parts only and are very
// different.
//
// See ARM section A2.2 (Processor Modes)

.set  MODE_USR, 0x10			
.set  MODE_FIQ, 0x11			
.set  MODE_IRQ, 0x12			
.set  MODE_SVC, 0x13			
.set  MODE_ABT, 0x17				
.set  MODE_UND, 0x1B			
.set  MODE_SYS, 0x1F				

.set  I_BIT, 0x80				
.set  F_BIT, 0x40	

_start:
    ldr pc, _reset_h
    ldr pc, _undefined_instruction_vector_h
    ldr pc, _software_interrupt_vector_h
    ldr pc, _prefetch_abort_vector_h
    ldr pc, _data_abort_vector_h
    ldr pc, _unused_handler_h
    ldr pc, _interrupt_vector_h
    ldr pc, _fast_interrupt_vector_h

_reset_h:                           .word   _reset_
_undefined_instruction_vector_h:    .word   _inf_loop
_software_interrupt_vector_h:       .word   software_handler
_prefetch_abort_vector_h:           .word   _inf_loop
_data_abort_vector_h:               .word   _inf_loop
_unused_handler_h:                  .word   _inf_loop
_interrupt_vector_h:                .word   irq_handler
_fast_interrupt_vector_h:           .word   _inf_loop
	
_reset_:
    // We enter execution in supervisor mode. For more information on
    // processor modes see ARM Section A2.2 (Processor Modes)

    	mrs	r0 , cpsr
    	eor	r0, r0, #0x1A
    	tst	r0, #0x1F
    	bic	r0 , r0 , #0x1F				
    	orr	r0 , r0 , #MODE_SVC|I_BIT|F_BIT
    	bne	2f							
    	orr	r0, r0, #0x100				
    	adr	lr, 3f
    	msr	spsr_cxsf, r0
    	.word	0xE12EF30E					
    	.word	0xE160006E				
2:  	msr cpsr_c, r0
3:
    	mov r0, #0x0000
    	mov r1, #0x8000
    	ldmia r1!, {r2-r9}
    	stmia r0!, {r2-r9}
    	ldmia r1!, {r2-r9}
    	stmia r0!, {r2-r9}

    	msr CPSR_c,#MODE_IRQ|I_BIT|F_BIT 	
    	mov r0, #0x2000
    	mov sp, r0
	
    	msr CPSR_c,#MODE_SVC|I_BIT|F_BIT
    	mov r0, #0x8000
    	mov sp, r0
	
    	ldr r4, =__bss_start
    	ldr r9, =__bss_end
    	mov r5, #0
    	mov r6, #0
    	mov r7, #0
    	mov r8, #0
    	b       4f
 
1:
    // store multiple at r4.
    	stmia r4!, {r5-r8}
 
    // If we are still below bss_end, loop.
4:
    	cmp r4, r9
    	blo 1b

    // The c-startup function which we never return from. This function will
    // initialise the ro data section (most things that have the const
    // declaration) and initialise the bss section variables to 0 (generally
    // known as automatics). It'll then call main, which should never return.
    	ldr r3, =kernel_main
    	blx r3

    // If main does return for some reason, just catch it and stay here.
_inf_loop:
    	b       _inf_loop



