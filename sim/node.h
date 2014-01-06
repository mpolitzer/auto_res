#ifndef NODE_H
#define NODE_H

#include "common.h"
#include "cbuf.h"

typedef struct {
	bool exist;
	uint16_t id;
	struct {
		
		// layer 3
		nodeid_t hop;
		uint8_t seq_bcast; 
		uint8_t seq_ogm:1; 

		// layer 2
		uint8_t timeout:7;
	} nodes[NODE_MAX];

	CBuf rx, tx;
	uint8_t pending_timeout;
} Node;

#endif  /* NODE_H */
