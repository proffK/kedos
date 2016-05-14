#ifndef ARMTIMER_H
#define ARMTIMER_H

#include "bcm2836/defines.h"

#define ARMTIMER_BASE               ( PBASE + 0xB400 )

/** @brief 0 : 16-bit counters - 1 : 23-bit counter */
#define ARMTIMER_CTRL_23BIT         ( 1 << 1 )

#define ARMTIMER_CTRL_PRESCALE_1    ( 0 << 2 )
#define ARMTIMER_CTRL_PRESCALE_16   ( 1 << 2 )
#define ARMTIMER_CTRL_PRESCALE_256  ( 2 << 2 )

/** @brief 0 : Timer interrupt disabled - 1 : Timer interrupt enabled */
#define ARMTIMER_CTRL_INT_ENABLE    ( 1 << 5 )
#define ARMTIMER_CTRL_INT_DISABLE   ( 0 << 5 )

/** @brief 0 : Timer disabled - 1 : Timer enabled */
#define ARMTIMER_CTRL_ENABLE        ( 1 << 7 )
#define ARMTIMER_CTRL_DISABLE       ( 0 << 7 )


typedef struct arm_timer_t{
	volatile uint32_t Load;
	volatile uint32_t Value;
	volatile uint32_t Control;
	volatile uint32_t IRQClear;
	volatile uint32_t RAWIRQ;
	volatile uint32_t MaskedIRQ;
	volatile uint32_t Reload;
	volatile uint32_t PreDivider;
	volatile uint32_t FreeRunningCounter;

} arm_timer;

extern arm_timer* ArmTimer;

extern arm_timer* GetArmTimer();
extern void ArmTimerInit(void);

#endif

