/* --------------------------------------- */

#include "common.h"
#include "layer1.h"
#include "layer2.h"
#include <stdlib.h>

/* --------------------------------------- */

static MessageL2 *l2_new_message(nodeid_t src, nodeid_t dst, int type, MessageL3 *m)
{
	MessageL2 *ml2 = malloc(sizeof(MessageL2));
	assert(ml2 && "Out of Memory.");

	ml2->msg = m;
	ml2->src = src;
	ml2->dst = dst;
	ml2->type = type;

	return ml2;
}

void l2_tick(Node *self)
{
}

void l2_send_l3_message(Node *self, MessageL3 *ml3, nodeid_t hop)
{
	MessageL2 *ml2 = l2_new_message(self->id, hop, L2_L3, ml3);
	cbuf_put(&(self->tx), ml2);
	//l1_send(self, ml2);
}

void l2_send_alive(Node *self, nodeid_t to)
{
	MessageL2 *ml2 = l2_new_message(self->id, to, L2_ALIVE, NULL);
	cbuf_put(&(self->tx), ml2);
	//l1_send(self, ml2);
}

void l2_send_ack(Node *self, nodeid_t to)
{
	MessageL2 *ml2 = l2_new_message(self->id, to, L2_ACK, NULL);
	cbuf_put(&(self->tx), ml2);
	// l1_send(self, ml2);
}

void l2_recv(Node *self, MessageL2 *m)
{
	assert(self && "fuck you!");
	assert(m && m->src && m->dst && "invalid message");

	if (self->nodes[m->src].timeout == 0)
		l3_found(self, m->src);

	if(m->type < L2_INVALID)
		self->nodes[m->src].timeout = ALIVE_MAX;

	if (self->id != m->dst)
		return;
	
	switch (m->type) 
	{
		case L2_L3:
			cbuf_put(&(self->rx), m);
			break;
		case L2_ACK:
			self->pending_timeout = 0;
			free(cbuf_get(&(self->tx)));
			break;
		case L2_ALIVE:
			l2_send_ack(self, m->src);
			break;
		default:
			assert("invalid l2 message.");
			break;
	}
}

MessageL3 * l2_recv_l3_message(Node * n)
{
	MessageL2 * m = cbuf_get(&(n->rx));
	MessageL3 * ret = m->msg;
	free(m);
	return ret;
}

/* --------------------------------------- */
