/* --------------------------------------- */

#include "common.h"
#include "report.h"
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

// break radio loop from l2_tick timeout.
void l2_tick(Node *self)
{
	int i;

	if(!self->l2_cnt)
	{
		report(self, REPORT_L2_HELLO, "L2_HELLO: %d -> %d\n", self->id, 0);
		l1_send(self->id, l2_new_message(self->id, 0, L2_ALIVE, NULL));
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

	// somebody to send?
	if(!cbuf_isempty(&(self->tx_ack)))
	{
		MessageL2 *m = cbuf_get(&(self->tx_ack));
		report(self, REPORT_L2_ACK, "L2_ACK: %d -> %d\n", m->src, m->dst);
		l1_send(m->src, m);
	}
	if(!cbuf_isempty(&(self->tx)))
	{
		if(self->pending_timeout == 0)
		{
			MessageL2 *m = cbuf_peek(&(self->tx));

			if(m->type == L2_ALIVE)
				report(self, REPORT_L2_ALIVE, "L2_ALIVE: %d -> %d\n", m->src, m->dst);
			else
				report(self, REPORT_L2_L3, "L2_L3: %d -> %d\n", m->src, m->dst);

			l1_send(m->src, m);
			self->pending_timeout = PENDING_MAX;
		}
		else self->pending_timeout--;
	}
}

void l2_send_l3_message(Node *self, MessageL3 *ml3, nodeid_t hop)
{
	if(!hop) // broadcast
	{
		int i;
		for (i = 0; i < self->l2_cnt; i++)
		{
			MessageL2 *ml2 = l2_new_message(self->id, self->l2[i].id, L2_L3, ml3); // TODO: dup ml3 
			cbuf_put(&(self->tx), ml2);
		}
	}
	else // unicast
	{
		MessageL2 *ml2 = l2_new_message(self->id, hop, L2_L3, ml3);
		cbuf_put(&(self->tx), ml2);
	}
}

void l2_send_alive(Node *self, nodeid_t to)
{
	MessageL2 *ml2 = l2_new_message(self->id, to, L2_ALIVE, NULL);
	cbuf_put(&(self->tx), ml2);
}

void l2_send_ack(Node *self, nodeid_t to)
{
	MessageL2 *ml2 = l2_new_message(self->id, to, L2_ACK, NULL);
	cbuf_put(&(self->tx_ack), ml2);
}

void l2_recv(Node *self, MessageL2 *m)
{
	assert(self && "fuck you!");
	assert(m && m->src && "invalid message");

	// TODO: check sequence number from package.

	int i;
	int l2_idx;
	// Timeout = 0 only happens if we don't know the src node

	for(i=0, l2_idx=-1; i < self->l2_cnt; i++)
	{
		if ((m->src == self->l2[i].id))
		{
			l2_idx=i;
			break;
		}
	}
	if(l2_idx < 0)
	{
		if(l3_found(self, m->src))	
		{
			self->l2[self->l2_cnt].id = m->src;
			self->l2[self->l2_cnt].timeout = TIMEOUT_TO_DEAD;
			self->l2_cnt++;
		}
	} else if(m->type < L2_INVALID)
		self->l2[l2_idx].timeout = TIMEOUT_TO_DEAD;

	/* msg is not for me! */
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
