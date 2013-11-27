#include <msp430f2121/cpu.inl>
#include <msp430f2121/gpio0.inl>
#include <msp430f2121/timer0.inl>

void timer0_ta0_irq() {
	gpio0_clr(P0);
}

void gpio0_irq()  {
	TA0R = 0;
	gpio0_set(P0);
	P1IES ^= P1;
	P1IFG &=~P1;
}

int main(int argc, char *argv[]) {
	cpu_init();
	timer0_init(5000);
	gpio0_init();

	gpio0_out(P0);
	P1IE   = P1;
	P1IES  = P1;
	P1REN  = P1;
	P1IFG &=~P1;

	for (;;) {
		_BIS_SR(LPM0_bits | GIE);
	}

	return 0;
}
