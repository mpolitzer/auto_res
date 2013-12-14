#ifndef GPIO0_INL
#define GPIO0_INL

#include <msp430f2121/gpio.h>

static inline void gpio0_init(void) {}
static inline void gpio0_fini(void) {}

static inline void gpio0_set (gpio_mask m) { P1OUT |= m; } 
static inline void gpio0_clr (gpio_mask m) { P1OUT &=~m; }
static inline void gpio0_flip(gpio_mask m) { P1OUT ^= m; } 
static inline void gpio0_out (gpio_mask m) { P1DIR |= m; }
static inline void gpio0_in  (gpio_mask m) { P1DIR &=~m; }
static inline void gpio0_pu  (gpio_mask m) { P1REN |= m; }
static inline gpio_mask gpio0_read(void) { return P1IN; }
static inline void gpio0_irq_enable(gpio_mask m)  { P1IE |= m; }
static inline void gpio0_irq_disable(gpio_mask m) { P1IE &=~m; }
static inline void gpio0_irq_onrise(gpio_mask m) {
	P1IES |= m;
	P1IFG &=~m;
}

static inline void gpio0_irq_onfall(gpio_mask m) {
	P1IES &=~m;
	P1IFG &=~m;
}


#endif /* GPIO0_INL */
