#include <msp430f2121/cpu.inl>
#include <msp430f2121/spi0.inl>
#include <msp430f2121/gpio0.inl>
#include <msp430f2121/timer0.inl>

#define NRF24L01P_CE	(BIT0)
#define NRF24L01P_CSN	(BIT1)
#define NRF24L01P_IRQ	(BIT2)

static inline void nrf24l01p_init(void) {
	spi0_init();
	gpio1_out(NRF24L01P_CE | NRF24L01P_CSN);
	gpio1_in (NRF24L01P_IRQ);
	gpio1_pu (NRF24L01P_IRQ);
	gpio1_irq_enable(NRF24L01P_IRQ);
	gpio1_irq_onrise(NRF24L01P_IRQ);
}
