#ifndef L3_H
#define L3_H

/* --------------------------------------- */

#include<stdbool.h>
#include<stdint.h>

#include "node.h"

/* --------------------------------------- */

typedef uint8_t msize_t;

typedef struct
{
	enum
	{
		L3_OGM,
		L3_ROGM,
		L3_KNOWN,
		L3_BROADCAST,
		L3_UNICAST,

	} type;

	uint16_t src;
	uint16_t dst;
	uint8_t seq;

	msize_t msize;
	uint8_t *msg; // Message L4

} MessageL3;

/* --------------------------------------- */

// called from layer 2

bool l3_died(Node *n, nodeid_t id);

bool l3_found(Node *n, nodeid_t id);

bool l3_recvd_l2(Node *self, MessageL3 *msg);

// called from layer 4

bool l3_send(uint16_t dst, msize_t msize, uint8_t msg[]);

bool l3_recv(uint16_t *src, msize_t *msize, uint8_t msg[]);

/* --------------------------------------- */
#endif // L3_H
