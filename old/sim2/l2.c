#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "l3.h"
#include "l2.h"
#include "l1.h"
#include "report.h"

static const char *type2s(uint8_t type);
static struct l2_msg *l2_msg_ack(nid from, nid to);
static struct l2_msg *l2_msg_alive(nid from, nid to);
static struct l2_msg *l2_msg_hello(nid from, nid to);

/* ========================================================================== */

void l2_tick(struct node_t *self)
{
	if (self->n_l2 == 0) { /* no neighbhors */
		l2_send(self, l2_msg_hello(self->id, BROADCAST));
	} else for (int i=0; i<self->n_l2; i++) {
			if (self->l2[i].alive_timeout-- == 0) {
				l2_send(self, l2_msg_alive(self->id,
							self->l2[i].id));
				self->l2[i].alive_timeout = ALIVE_TIMEOUT;
			}
	}
#if 0
	if (self->alive_tick-- == 0) {
		self->alive_tick = ALIVE_TICK_SET;

		/* self doesn't know anybody! */
		if (self->n_l2 == 0) {
			l2_send(self, l2_msg_hello(self->id, BROADCAST));
		} else {
			l2_send(self, l2_msg_alive(self->id, BROADCAST));
		}
	}
#endif
	for (int i=0; i < self->n_l2; i++) {
		if (self->l2[i].time_until_lost-- == 0) {
			l3_lost(self, &self->l2[i]);
		}
	}

	if (!cbuf_isempty(&self->tx)) {
		struct l2_msg *m = cbuf_get(&self->tx);
		l1_send(m);
		l2_msg_unref(m);
	}
}

void l2_recv(struct node_t *self, struct l2_msg *m) {
	int i, hopidx = 0;
	bool is_hop = false;

	if (self->id == m->src)
		return;

	report(self, "L2(%d): recvd %s from %d.\n",
			self->id, type2s(m->type), m->src);

	for (i=0; i<self->n_l2; i++) {
		if (self->l2[i].id == m->src) {
			is_hop = true;
			break;
		}
	}
	hopidx = i;

	if (!is_hop) { /* he is always my neighbhor! */
		if (!l3_found(self, m->src, self->id))
			goto done;
		self->l2 = realloc(self->l2,
				sizeof(struct l2_info) * (self->n_l2+1));
		self->l2[hopidx].id              = m->src;
		self->l2[hopidx].time_until_lost = ALIVE_TIMEOUT;
		self->n_l2++;
		report(self, "L2(%d): added new hop %d.\n", self->id, m->src);
	}

	switch (m->type) {
	case L2_ACK:
		self->l2[hopidx].time_until_lost = ALIVE_TIMEOUT;
		break;
	case L2_HELLO:
		break;
	case L2_ALIVE: /* reset the timeout. */
		self->l2[hopidx].time_until_lost = ALIVE_TIMEOUT;
		l2_send(self, l2_msg_ack(self->id, m->src));
		break;
	default:
		break;
	}
done:
	l2_msg_unref(m);
}

void l2_send(struct node_t *self, struct l2_msg *m)
{
	if (!cbuf_put(&self->tx, m)) {
		report(self, "cbuf full, dropping packacge.\n");
		l2_msg_unref(m);
	}
}

/* ========================================================================== */

struct l2_msg *l2_msg_alloc(nid src, nid dst, uint8_t t, uint16_t len) {
	struct l2_msg *m = malloc(sizeof(*m) + len);
	m->ref = 1;
	m->type= t;
	m->src = src;
	m->dst = dst;
	m->len = len;
	return m;
}

void l2_msg_ref(struct l2_msg *m) {
	m->ref++;
}

void l2_msg_unref(struct l2_msg *m) {
	if (--m->ref == 0)
		free(m);
}

void *l2_msg_data(struct l2_msg *m) {
	return m->data;
}

uint16_t l2_msg_len(struct l2_msg *m) {
	return m->len;
}

static struct l2_msg *l2_msg_ack(nid from, nid to) {
	return l2_msg_alloc(from, to, L2_ACK, 0);
}

static struct l2_msg *l2_msg_alive(nid from, nid to) {
	return l2_msg_alloc(from, to, L2_ALIVE, 0);
}

static struct l2_msg *l2_msg_hello(nid from, nid to) {
	return l2_msg_alloc(from, to, L2_HELLO, 0);
}

/* ========================================================================== */

static const char *type2s(uint8_t type) {
	static const char *msgs[] = {
		"alive",
		"hello",
		"ack",
		"l3",
	};
	return msgs[type];
}
