#include "msg.h"
#include <stdlib.h>

size_t msg_sizeof(int layers)
{
	size_t total = 0;

	switch (layers) { /* using fall-through. */
	case 4: total += sizeof(struct l4msg_t);
	case 3: total += sizeof(struct l3msg_t);
	case 2: total += sizeof(struct l2msg_t);
	default:
		return total;
	}
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
