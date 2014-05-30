#include "mesh.h"

void gpio_irq(void)
{
	mesh_irq();
}


void myrx(msg_t *t, void *arg)
{
	static int n;
	static float f, avg;

	f += *(float *)msg_getpayload(t);
	avg = f / ++n;

	printf("last = %f, %d, avg = %f\n", f, n, avg);

	/* respond */

	msg_free(t);
}

int main(int argc, char *argv[])
{
	mesh_init(&myrx, NULL);
	for (;;) {
		delay_ms(10);
		mesh_tick(10);
	}
	return 0;
}
