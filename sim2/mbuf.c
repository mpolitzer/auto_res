#include <stdlib.h>
#include "mbuf.h"

struct mbuf *mbuf_alloc(uint16_t len) {
	struct mbuf *mb = malloc(sizeof(*mb)
			+ len ?  sizeof(struct l3_msg) + len : 0);
	return mb;
}

void mbuf_ref(struct mbuf *mb) {
	mb->refcount++;
}

void mbuf_free(struct mbuf *mb) {
	if (--mb->refcount == 0)
		free(mb);
}

struct l2_msg *mbuf_get_l2(struct mbuf *mb) {
	return &mb->l2;
}

struct l3_msg *mbuf_get_l3(struct mbuf *mb) {
	return (struct l3_msg *)mb->l2.data;
}
