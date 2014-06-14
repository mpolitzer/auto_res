#include<stdio.h>
#include "radio_mock.h"

radio_t A, B;

void irq(uint8_t type, void *arg)
{
	uint8_t buf[32];
	const char *s;
	if (arg == &A) s = "A";
	if (arg == &B) s = "B";

	printf("hello world; type is: %d, to %s\n", type, s);

	if(type == RADIO_MOCK_IRQ_RECEIVED)
	{
		radio_read(&B, buf);
		puts(buf);
	}
}

int main(int argc, char *argv[])
{
	radio_init(&A, irq, &A);
	radio_set_to_rx(&A, false);

	radio_init(&B, irq, &B);
	radio_set_to_rx(&B, true);

	radio_listen(&B, 0, 10);
	radio_write(&A, 10, "asd", 4);
	radio_transfer(&A, &B);
	radio_end_transfer(&A);

	return 0;
}
