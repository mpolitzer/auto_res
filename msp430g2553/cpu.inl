#ifndef CPU_INL
#define CPU_INL

#include <msp430.h>

static inline void cpu_init() {
	WDTCTL = WDTPW | WDTHOLD; /* wdt off */
	BCSCTL1= CALBC1_16MHZ;
	DCOCTL = CALDCO_16MHZ;
}

static inline void cpu_irqs_on()  { _BIS_SR(GIE); } 
static inline void cpu_irqs_off() { _BIC_SR(GIE); }

#endif /* CPU_INL */
