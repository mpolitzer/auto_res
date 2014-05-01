#include "msg.h"
#include <stdlib.h>

size_t msg_sizeof(int layers)
{
	size_t total = 0;

	switch (layers) {
	case 4: total += sizeof(struct l4msg_t);
	case 3: total += sizeof(struct l3msg_t);
	case 2: total += sizeof(struct l2msg_t);
	default:
		return total;
	}
}

struct msg_t *msg_alloc(int layers, size_t payload)
{
	size_t total = msg_sizeof(layers);
	if (total == 0)
		return NULL;
	return malloc(total+payload);
}

void msg_free(struct msg_t *m)
{
	free(m);
}

struct l2msg_t *msg_get_l2(struct msg_t *m)
{
	return m->pl;
}

struct l3msg_t *msg_get_l3(struct msg_t *m)
{
	struct l2msg_t *l2 = msg_get_l2(m);
	return l2->pl;
}

struct l4msg_t *msg_get_l4(struct msg_t *m)
{
	struct l3msg_t *l3 = msg_get_l3(m);
	return l3->pl;
}
