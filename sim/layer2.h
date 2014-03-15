#ifndef L2_H
#define L2_H

#include "layer3.h"
#include "common.h"
#include "node.h"

typedef struct {
	enum
	{
		L2_ACK,
		L2_ALIVE,
		L2_HELLO,
		L2_L3,
		L2_INVALID,

	} type;

	uint8_t ref;
	nodeid_t src;
	nodeid_t dst; /* to whom? (next hop) */

	MessageL3 *msg;
} MessageL2;

/* --------------------------------------- */

void l2_tick(Node *n);
void l2_recv(Node *n, MessageL2 *m); /* Callback from L1 */
void l2_send_l3_message(Node *self, MessageL3 *ml3, nodeid_t hop);
MessageL3 * l2_recv_l3_message(Node * n);

void l2_ref_message(MessageL2 *m);

/* --------------------------------------- */

#endif // L2_H
