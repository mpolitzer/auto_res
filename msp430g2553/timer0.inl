#include <msp430.h>

static inline void timer0_init(uint16_t ticks) {
	TA0CCTL0 = CCIE; /* enable IRQ */
	TA0CCR0 = ticks;
	TA0CTL  = TASSEL_2 | MC_2 | ID_3;
}
