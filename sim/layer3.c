/* --------------------------------------- */

#include <stdlib.h>
#include "common.h"
#include "report.h"
#include "layer3.h"
#include "layer2.h"

MessageL3 * l3_create_ogm_msg(void);
void l3_handle_rogm(Node *self, MessageL3 *m);
void l3_handle_ogm(Node *self, MessageL3 *m);

/* --------------------------------------- */

// INI L2 CALLBACK

bool l3_died(Node *self, nodeid_t id)
{
	report(self, REPORT_L3_DIED,"L3_DIED %d -> %d\n", self->id, id);
	return true;
}

bool l3_found(Node *self, nodeid_t id)
{
	report(self, REPORT_L3_FOUND,"L3_FOUND %d -> %d\n", self->id, id);
	return true;
}

bool l3_recvd_l2(Node *self, MessageL3 *msg)
{
	// TODO: Print message
	switch (msg->type)
	{
		case L3_OGM: l3_handle_ogm(self, msg); break;
		default: break;
	}
}

// END L2 CALLBACK

MessageL3 * l3_create_ogm_msg(void)
{
	MessageL3 *ml3 = malloc(sizeof(MessageL3));
	assert(ml3 && "Out of Memory.");

	ml3->type = L3_OGM;
	ml3->src = self->id;
	ml3->dst = 0;
	ml3->seq_ogm = self->l3[self->id].seq_ogm;
	self->l3[self->id].seq_ogm ++;
	return ml3;
}

void l3_handle_rogm(Node *self, MessageL3 *m)
{

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

}

bool l3_recv(uint16_t *src, msize_t *msize, uint8_t msg[])
{

}



/* --------------------------------------- */
