/* --------------------------------------- */

#include <stdlib.h>
#include "common.h"
#include "report.h"
#include "layer3.h"
#include "layer2.h"

MessageL3 * l3_create_ogm_msg(Node *self);
MessageL3 * l3_create_rogm_msg(Node *self, uint16_t dst);
void l3_handle_rogm(Node *self, MessageL3 *m);
void l3_handle_ogm(Node *self, MessageL3 *m);

/* --------------------------------------- */

// INI L2 CALLBACK

bool l3_died(Node *self, nodeid_t id)
{
	return true;
	MessageL3 *ml3 = l3_create_rogm_msg(self, id);

	report(self, REPORT_L3_DIED,"L3_DIED %d -> %d\n", self->id, id);
	l2_send_l3_message(self, ml3, 0); // Broadcast
	return true;
}

bool l3_found(Node *self, nodeid_t id)
{
	report(self, REPORT_L3_FOUND,"L3_FOUND %d -> %d\n", self->id, id);
	return true;

	self->l3[id].id          = id;
	self->l3[id].hop         = id;
	self->l3[id].seq_bcast   = 0;
	self->l3[id].seq_ogm     = 0;
	self->l3[id].seq_rogm    = 0;
	self->l3[id].ogm_timeout = 0;

	// TODO: send known messages
	return true;
}

bool l3_recvd_l2(Node *self, MessageL3 *msg)
{
	// TODO: Print message / report?
	switch (msg->type)
	{
		case L3_OGM: l3_handle_ogm(self, msg); break;
		case L3_ROGM: l3_handle_rogm(self, msg); break;
		default: return false;
	}
	return true;
}

// END L2 CALLBACK

MessageL3 * l3_create_ogm_msg(Node *self)
{
	MessageL3 *ml3 = malloc(sizeof(MessageL3));
	assert(ml3 && "Out of Memory.");

	self->l3[self->id].seq_ogm ++;
	ml3->type = L3_OGM;
	ml3->src = self->id;
	ml3->dst = 0;
	ml3->seq = self->l3[self->id].seq_ogm;
	return ml3;
}

MessageL3 * l3_create_rogm_msg(Node *self, uint16_t dst)
{
	MessageL3 *ml3 = malloc(sizeof(MessageL3));
	assert(ml3 && "Out of Memory.");

	self->l3[self->id].seq_rogm ++;
	ml3->type = L3_ROGM;
	ml3->src = self->id;
	ml3->dst = dst;
	ml3->seq = self->l3[self->id].seq_rogm;
	return ml3;

}

void l3_handle_rogm(Node *self, MessageL3 *m)
{
	if(m->dst == self->id)
	{
		MessageL3 *ml3 = l3_create_ogm_msg(self);

		report(self, REPORT_L3_OGM,"L3_OGM %d -> %d\n", self->id, 0);
		l2_send_l3_message(self, ml3, 0); // Broadcast

		//l2_send_l3_message(self, m, 0); // Broadcast
	}
	else
	{
		// kill route?
		l2_send_l3_message(self, m, 0); // Broadcast
	}
}

void l3_handle_ogm(Node *self, MessageL3 *m)
{
	if(self->l3[m->src].seq_ogm != m->seq)
	{
		self->l3[m->src].seq_ogm = m->seq;
		self->l3[m->src].hop = m->src;
		l2_send_l3_message(self, m, 0); // Broadcast
	}
}

bool l3_send(uint16_t dst, msize_t msize, uint8_t msg[])
{
	return true;
}

bool l3_recv(uint16_t *src, msize_t *msize, uint8_t msg[])
{
	return true;
}

/* --------------------------------------- */
