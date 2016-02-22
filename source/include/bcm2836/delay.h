#ifndef __DELAY__
#define __DELAY__

/* Loop <delay> times in a way that the compiler won't optimize away. */
static inline void delay(volatile uint32_t count)
{
    register volatile uint32_t reg = count;
	asm volatile("__delay_%=: subs %[count], %[count], #1;\
                  bne __delay_%="
		          :
                  : [count]"r"(reg) 
                  : "cc");
}

#endif
