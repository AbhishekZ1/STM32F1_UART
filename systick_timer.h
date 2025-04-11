#define SYSTEM_CLOCK_HZ 108000000 // Example clock frequency
#define SYSTICK_LOAD_1MS (SYSTEM_CLOCK_HZ / 1000 - 1)


void systick_init_timer(void);
void systick_init_timer_interrupt(void);
void delayM(void);
void delay(unsigned long t);