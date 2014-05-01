#ifndef L3_H
#define L3_H

#include "node.h"

struct l3_msg {
	nid src, dst;

#define L3_OGM  0
#define L3_ROGM 1
#define L3_DATA 2
	uint8_t type;
	uint16_t len;
	uint8_t data[];
};

bool l3_found  (struct node_t *self, nid found, nid by);
bool l3_lost   (struct node_t *self, struct l2_info *lost);

struct l2_msg *l3_msg_ogm(nid src, nid dst);

#endif /* L3_H */
