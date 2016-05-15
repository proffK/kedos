#include "bcm2836/armtimer.h"

arm_timer* ArmTimer = (arm_timer *)ARMTIMER_BASE;

arm_timer* GetArmTimer()
{
	    return ArmTimer;
}
 
void ArmTimerInit(void)
{
           ArmTimer->Load = 0x40;

	        /* Setup the ARM Timer */
     	   ArmTimer->Control = ARMTIMER_CTRL_23BIT | ARMTIMER_CTRL_ENABLE | ARMTIMER_CTRL_INT_ENABLE | ARMTIMER_CTRL_PRESCALE_256;
}
