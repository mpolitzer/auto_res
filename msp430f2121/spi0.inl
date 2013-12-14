#include <stdint.h>
#include <msp430.h>

static inline void spi0_init() {
	P1SEL  = BIT1 + BIT2 + BIT4;
	P1SEL2 = BIT1 + BIT2 + BIT4;
	UCA0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 |= 0x02;                          // /2
	UCA0BR1 = 0;                              //
	UCA0MCTL = 0;                             // No modulation
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	IE2 |= UCA0RXIE;                          // Enable USCI0 RX interrupt
}

static volatile uint8_t spi_buf;
static uint8_t spi_rw8(uint8_t write) {
	UCA0TXBUF = write;
	__bis_SR_register(LPM0_bits + GIE);       // CPU off, enable interrupts
	return spi_buf;
}

__attribute__((__interrupt__(USCIAB0RX_VECTOR))) void USCIA0RX_ISR(void)
{
	while (!(IFG2 & UCA0TXIFG)); // USCI_A0 TX buffer ready?
	spi_buf = UCA0RXBUF;
	__bic_SR_register_on_exit(CPUOFF);
}
