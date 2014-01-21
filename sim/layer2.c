/* --------------------------------------- */

#include "common.h"
#include "layer1.h"
#include "layer2.h"
#include <stdlib.h>

/* --------------------------------------- */

void l2_send_alive(Node *self, nodeid_t to);

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

// TODO: botar a fila do ack
// break radio loop from l2_tick timeout.
void l2_tick(Node *self)
{
	int i;

	// somebody to send?
	if(!cbuf_isempty(&(self->tx)))
	{
		if(self->pending_timeout == 0)
		{
			MessageL2 *m = cbuf_peek(&(self->tx));
			l1_send(m->dst, m);
			self->pending_timeout = PENDING_MAX;
		}
		else self->pending_timeout--;
	}

	// send alive
	if (self->alive_timeout == 0)
	{
		for (i = 0; i < self->l2_cnt; i++)
			l2_send_alive(self, self->l2[i].id);
		self->alive_timeout = ALIVE_INTERVAL;
	}
	else self->alive_timeout--;

	// detect missing neighbors via timeout
	for (i = 0; i < self->l2_cnt; i++)
	{
		if (self->l2[i].timeout == 0)
		{
			l3_died(self, self->l2[i].id);

			self->l2[i] = self->l2[self->l2_cnt-1];
			self->l2_cnt--;
		}
		else self->l2[i].timeout--;
	}
}

void l2_send_l3_message(Node *self, MessageL3 *ml3, nodeid_t hop)
{
	MessageL2 *ml2 = l2_new_message(self->id, hop, L2_L3, ml3);
	cbuf_put(&(self->tx), ml2);
}

void l2_send_alive(Node *self, nodeid_t to)
{
	MessageL2 *ml2 = l2_new_message(self->id, to, L2_ALIVE, NULL);
	cbuf_put(&(self->tx), ml2);
}

void l2_send_ack(Node *self, nodeid_t to)
{
	MessageL2 *ml2 = l2_new_message(self->id, to, L2_ACK, NULL);
	cbuf_put(&(self->tx), ml2);
}

void l2_recv(Node *self, MessageL2 *m)
{
	assert(self && "fuck you!");
	assert(m && m->src && m->dst && "invalid message");

	// TODO: check sequence number from package.

	if (self->l2[m->src].timeout == 0)
		l3_found(self, m->src);

	if(m->type < L2_INVALID)
		self->l2[m->src].timeout = TIMEOUT_TO_DEAD;

	if (self->id != m->dst)
		return;

	switch (m->type) 
	{
		case L2_L3:
			cbuf_put(&(self->rx), m);
			l2_send_ack(self, m->src);
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
