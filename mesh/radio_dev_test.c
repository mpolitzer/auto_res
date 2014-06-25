#include <stdio.h>
#include "radio_dev.h"

RadioDev A, B;

void irq(uint8_t type, void *arg)
{
	uint8_t buf[32];
	const char *s;
	if (arg == &A) s = "A";
	if (arg == &B) s = "B";

	printf("hello world; type is: %d, to %s\n", type, s);

	if(type == RADIO_IRQ_RECEIVED)
	{
		radio_dev_read(&B, buf);
		puts((char *)buf);
	}
}

int main(int argc, char *argv[])
{
	radio_dev_init(&A, irq, &A);
	radio_dev_set_to_rx(&A, false);

	radio_dev_init(&B, irq, &B);
	radio_dev_set_to_rx(&B, true);

	radio_dev_listen(&B, 0, 10);
	radio_dev_write(&A, 10, (uint8_t *)"asd", 4);
	radio_dev_transfer(&A, &B);
	radio_dev_end_transfer(&A);

	return 0;
}
