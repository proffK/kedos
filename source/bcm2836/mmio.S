.arm 

.text

.globl memory_flush
memory_flush:
        push {r3}
        mov r3, #0
        mcr p15, 0, r3, C7, C6, 0       /* Invalidate Entire Data Cache */
        mcr p15, 0, r3, c7, c10, 0      /* Clean Entire Data Cache */
        mcr p15, 0, r3, c7, c14, 0      /* Clean and Invalidate Entire Data Cache */
        mcr p15, 0, r3, c7, c10, 4      /* Data Synchronization Barrier */
        mcr p15, 0, r3, c7, c10, 5      /* Data Memory Barrier */
        pop {r3}
        mov pc, lr

.globl memory_barier
memory_barier:
        push {r3}
        mov r3, #0
        mcr p15, 0, r3, c7, c5, 0   /* Invalidate instruction cache */
        mcr p15, 0, r3, c7, c5, 6   /* Invalidate BTB */
        mcr p15, 0, r3, c7, c10, 4  /* Drain write buffer */
        mcr p15, 0, r3, c7, c5, 4   /* Prefetch flush */
        pop {r3}
        mov pc, lr                  /* Return */
