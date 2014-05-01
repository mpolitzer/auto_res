#ifndef NODE_H
#define NODE_H

#include "common.h"
#include "cbuf.h"

typedef struct 
{
	bool exist;
	uint16_t id;

	struct 
	{
		// layer 3
		nodeid_t id;
		nodeid_t hop;
		uint8_t seq_bcast; 
		uint8_t seq_ogm; 
		uint8_t seq_rogm;
		uint8_t ogm_timeout;
	} l3[NODE_MAX];

	struct 
	{
		// layer 2
		nodeid_t id;
		uint8_t timeout;
	} l2[NODE_MAX];
	uint16_t l2_cnt;

	CBuf rx, tx, tx_ack;
	uint8_t pending_timeout;
	uint8_t alive_timeout;
} Node;

#endif  /* NODE_H */
