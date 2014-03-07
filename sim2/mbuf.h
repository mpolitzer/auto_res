#ifndef MBUF_H
#define MBUF_H

#include <stdint.h>
#include "l1.h"
#include "l2.h"
#include "l3.h"

struct mbuf {
	uint8_t refcount;
	struct l2_msg l2;
};

struct mbuf   *mbuf_alloc(uint16_t len);
void           mbuf_ref  (struct mbuf *mb);
void           mbuf_free (struct mbuf *mb);

struct l2_msg *mbuf_get_l2(struct mbuf *mb);
struct l3_msg *mbuf_get_l3(struct mbuf *mb);

#endif /* MBUF_H */

