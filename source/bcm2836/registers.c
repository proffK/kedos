#include <bcm2836/registers.h>

void reg2arr(reg_t* arr)
{
        /*asm volatile ( "str %%r0, %0\n\t"
                        "ldr %%r0, %0\n\t"
                        "add %%r0, %%r0, #4\n\t"
                        "str %%pc, [%%r0]\n\t"
                        "add %%r0, %%r0, #4\n\t"
                        "str %%r1, [%%r0]\n\t"
                        "add %%r0, %%r0, #4\n\t"
                        "str %%r2, [%%r0]\n\t"
                        "add %%r0, %%r0, #4\n\t"
                        "str %%r3, [%%r0]\n\t"
                        "add %%r0, %%r0, #4\n\t"
                        "str %%r4, [%%r0]\n\t"
                        "add %%r0, %%r0, #4\n\t"
                        "str %%r5, [%%r0]\n\t"
                        "add %%r0, %%r0, #4\n\t"
                        "str %%r6, [%%r0]\n\t"
                        "add %%r0, %%r0, #4\n\t"
                        "str %%r7, [%%r0]\n\t"
                        "add %%r0, %%r0, #4\n\t"
                        "str %%r8, [%%r0]\n\t"
                        "add %%r0, %%r0, #4\n\t"
                        "str %%r9, [%%r0]\n\t"
                        "add %%r0, %%r0, #4\n\t"
                        "str %%r10, [%%r0]\n\t"
                        "add %%r0, %%r0, #4\n\t"
                        "str %%r11, [%%r0]\n\t"
                        "add %%r0, %%r0, #4\n\t"
                        "str %%r12, [%%r0]\n\t"
                        "add %%r0, %%r0, #4\n\t"
                        "str %%sp, [%%r0]\n\t"
                        "add %%r0, %%r0, #4\n\t" 
                        "str %%lr, [%%r0]\n\t" : "=m" (arr) : : "r1", "r2",
                        "r3", "r4", "r5", "r6", "r7",
                        "r8", "r9", "r10", "r11", "r12",
                        "memory" ); */
}
