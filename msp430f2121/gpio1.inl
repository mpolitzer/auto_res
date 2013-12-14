#ifndef GPIO0_INL
#define GPIO0_INL

#include <msp430f2121/gpio.h>

static inline void gpio1_init(void) {}
static inline void gpio1_fini(void) {}

static inline void gpio1_set (gpio_mask m) { P2OUT |= m; } 
static inline void gpio1_clr (gpio_mask m) { P2OUT &=~m; }
static inline void gpio1_flip(gpio_mask m) { P2OUT ^= m; } 
static inline void gpio1_out (gpio_mask m) { P2DIR |= m; }
static inline void gpio1_in  (gpio_mask m) { P2DIR &=~m; }
static inline void gpio1_pu  (gpio_mask m) { P2REN |= m; }
static inline gpio_mask gpio1_read(void) { return P2IN; }
static inline void gpio1_irq_enable(gpio_mask m)  { P2IE |= m; }
static inline void gpio1_irq_onrise(gpio_mask m) {
	P2IES |= m;
	P2IFG &=~m;
}

static inline void gpio1_irq_onfall(gpio_mask m) {
	P2IES &=~m;
	P2IFG &=~m;
}


#endif /* GPIO0_INL */
