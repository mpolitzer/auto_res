#include <stdint.h>
#include <msp430.h>

#define IRQ(x) __attribute__((__interrupt__(x ## _VECTOR))) void x(void)
/* ========================================================================== */
__attribute__((weak)) void gpio0_irq(void) {}
IRQ(PORT1) {
	gpio0_irq();
}

/* ========================================================================== */

__attribute__((weak)) void timer0_ta0_irq(void) {}
IRQ(TIMER0_A0) { /* CCA0 */
	timer0_ta0_irq();
}

__attribute__((weak)) void timer0_ta1_irq(void) {}
__attribute__((weak)) void timer0_ta2_irq(void) {}
__attribute__((weak)) void timer0_ovf_irq(void) {}
IRQ(TIMER0_A1) { /* CCA1-2 */
	switch (TA0IV) {
	case TA0IV_TACCR1: timer0_ta1_irq(); break;
	case TA0IV_TACCR2: timer0_ta2_irq(); break;
	case TA0IV_TAIFG:  timer0_ovf_irq(); break;
	default: break;
	}
}

/* ========================================================================== */
