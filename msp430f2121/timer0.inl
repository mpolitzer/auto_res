#include <msp430.h>

static inline void timer0_init(uint16_t ticks) {
	TACCTL0 = CCIE; /* enable IRQ */
	TACCR0 = ticks;
	TACTL  = TASSEL_2 | MC_2 | ID_3;
}
