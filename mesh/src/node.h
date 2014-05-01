#ifndef NODE_H
#define NODE_H
#include <stdint.h>
#include "list.h"

#define PRIO_MAX 2
typedef nid_t uint16_t;

struct l2_info {
	nid_t id;
	uint8_t timeout;
};

struct l3_info {
	nid_t id;
	nid_t hop;
	uint8_t seq; /* any message increments seq. */
};

struct node_t {
	nid_t id;

	uint8_t alive_timeout;
	uint8_t ogm_timeout;

	struct l2_info *l2;
	struct l3_info *l3;

	uint16_t l2_count;
	uint16_t l3_count;

	/* queues */
	struct list_head tx[PRIO_MAX], rx;
};

#endif /* NODE_H */
