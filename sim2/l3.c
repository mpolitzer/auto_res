#include <stdlib.h>

#include "l3.h"
#include "l2.h"
#include "l1.h"
#include "report.h"

bool l3_found(struct node_t *self, nid found, nid by) {

	self->l3 = realloc(self->l3, sizeof(struct l3_info) * (self->n_l3+1));
	self->l3[self->n_l3].id  = found;
	self->l3[self->n_l3].hop = by;
	self->n_l3++;

	report(self, "L3(%d): added %d to l3 via l2.\n", self->id, found, by);
	return true;
}

bool l3_lost(struct node_t *self, struct l2_info *lost) {
	report(self, "removed %d from l3.\n", lost->id);
	return true;
}

struct l2_msg *l3_msg_ogm(nid src, nid dst) {
	struct l2_msg *l2 = l2_msg_alloc(src, dst, L2_L3, sizeof(struct l3_msg));
	struct l3_msg *l3 = (struct l3_msg *)l2->data;

	l3->src = src;
	l3->dst = BROADCAST;
	l3->len = 0;

	return l2;
}
