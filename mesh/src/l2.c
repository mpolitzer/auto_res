#include "l2.h"

void l2_tick(struct node_t *n)
{
	/* handle alive and timeouts. */
}

void l2_send(struct node_t *n, struct msg_t *m)
{
	list_add(m, n->tx[m->prio_high]);
	/* if radio queue is empty: enqueue a msg_t. */
}

void l2_recv(struct node_t *n, struct msg_t *m)
{
	/* filtrar mensagens que não são para mim... */
	if (msg_get_l2(m)->type == L2_PL) {
		l3_recv(n, m);
		return;
	}

	/* hello? register new node. */
	/* alive? send(l2_ack).  */
	/* l2_ack? reset timeouts. */
}
