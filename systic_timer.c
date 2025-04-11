#include "systick_timer.h"
#include "stm32f10x.h" 

/// Intitallize Timer................
/// Initiallize Timer Interrupt
/// delay for 1 Millisecond............
/// delay for t milliseconds............

/// Intitallize Timer................
void systick_init_timer(void)
	{
			SysTick->CTRL = 0; // Disable SysTick
			SysTick->VAL = 0;  // Clear current value
			SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk; // Enable SysTick with processor clock
	}
/// Initiallize Timer Interrupt

void systick_init_timer_interrupt(void)
	{   __disable_irq();
			SysTick->CTRL = 0; // Disable SysTick
			SysTick->VAL = 0;  // Clear current value
			SysTick->LOAD = SYSTICK_LOAD_1MS;
			SysTick->CTRL = 7; // Enable SysTick with processor clock with Interrupt at one Ms,
		  __enable_irq(); 
	}

/// delay for 1 Millisecond............
void delayM(void) 
	{
			SysTick->LOAD = SYSTICK_LOAD_1MS;
			SysTick->VAL = 0;
			while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
	}
/// delay for t milliseconds............
void delay(unsigned long t)
	{
			for (; t > 0; t--) {
					delayM();
			}
	}
