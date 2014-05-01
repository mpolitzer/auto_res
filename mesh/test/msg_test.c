#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "msg.h"

bool test_layer_sizes(void)
{
	if (msg_sizeof(2) != sizeof(struct l2msg_t))
	{
		printf("Error msg_sizeof(2)\n");
		return false;
	}
	
	if (msg_sizeof(3) != sizeof(struct l2msg_t)
			   + sizeof(struct l3msg_t))
	{
		printf("Error msg_sizeof(3)\n");
		return false;
	}

	if (msg_sizeof(4) != sizeof(struct l2msg_t)
			   + sizeof(struct l3msg_t)
			   + sizeof(struct l4msg_t))
	{
		printf("Error msg_sizeof(4)\n");
		return false;
	}

	if (msg_sizeof(1) != 0)
	{
		printf("Error msg_sizeof(1)\n");
		return false;
	}

	if (msg_sizeof(5) != 0)
	{
		printf("Error msg_sizeof(5)\n");
		return false;
	}

	return true;
}

bool test_alloc_and_fill(void)
{
	for (int i=2; i<=4; i++)
	{
		struct msg_t *msg = msg_alloc(i, 1);
		memset(msg, 0xAA, msg_sizeof(i)+1);
		free(msg);
	}
	return true;
}

int main(int argc, char *argv[])
{
	test_layer_sizes();
	test_alloc_and_fill();
	return 0;
}
