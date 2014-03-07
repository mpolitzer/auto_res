#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "l1.h"
#include "l2.h"

static void node_init(struct node_t *n, uint32_t i, uint32_t max);
static void node_fini(struct node_t *n, uint32_t i, uint32_t max);

/* ========================================================================== */

static uint8_t       *_weights;
static struct node_t *_nodes;
static uint32_t       _n;
static uint32_t       _tick;

/* ========================================================================== */

void l1_init(uint32_t n)
{
	assert(n <= (1<<8*sizeof(nid)) && "more nodes than nid can handle.");

	_n       = n;
	_nodes   = malloc(sizeof(*_nodes  )*n);
	_weights = malloc(sizeof(*_weights)*n*n);

	/* disconect every i from node j for each (i, j). */
	memset(_weights, 0, sizeof(*_weights)*n*n);

	for (uint32_t i=0; i < n; i++)
		node_init(&_nodes[i], i, n);
}

void l1_fini(void)
{
	for (uint32_t i=0; i < _n; i++)
		node_fini(&_nodes[i], i, _n);
	free(_nodes);
	free(_weights);
}

uint32_t l1_n(void)
{
	return _n;
}

uint32_t l1_get_tick(void)
{
	return _tick;
}

void l1_set_weight(nid from, nid to, uint8_t weight)
{
	assert(from < _n && "from value is out of bounds.");
	assert(to   < _n && "to   value is out of bounds.");

	_weights[to + from*_n] = weight;
}

uint8_t l1_get_weight(nid from, nid to)
{
	assert(from < _n && "from value is out of bounds.");
	assert(to   < _n && "to   value is out of bounds.");

	return _weights[to + from*_n];
}

struct node_t *l1_get_node(nid id)
{
	assert(id <= _n && "id is out of bounds.");

	return &_nodes[id];
}

void l1_send(struct l2_msg *msg)
{
	int i;
	if (msg->dst != BROADCAST)
		l1_send_to(msg, msg->dst);
	else for (i=0; i<_n; i++)
		l1_send_to(msg, i);
}

void l1_send_to(struct l2_msg *msg, nid to)
{
	uint8_t w = l1_get_weight(msg->src, to);
	if (w) {
		if (w >= (rand() & 255)) {
			l2_msg_ref(msg);
			l2_recv(l1_get_node(to), msg);
		} else	printf("L1: %d -> %d failed\n", msg->src, to);
	}
}

/* ========================================================================== */

void l1_tick(void)
{
	for (uint32_t i=0; i<_n; i++) {
		l2_tick(_nodes+i);
	}
	_tick++;
}

void l1_foreach_node(void (*run)(struct node_t *self))
{
	for (uint32_t i=0; i<_n; i++) {
		run(_nodes+i);
	}
}

/* ========================================================================== */

static void node_init(struct node_t *n, uint32_t i, uint32_t max)
{
	n->id = i;

	n->ogm_tick   = OGM_TICK_SET;

	/* pre allocate all nodes */
	n->l2 = NULL;
	n->n_l2 = 0;

	/* pre allocate all nodes */
	n->l3 = NULL;
	n->n_l3 = 0;

	cbuf_init(&n->tx,      malloc(CBUF_TX_MAX * sizeof(void *)), CBUF_TX_MAX);
	cbuf_init(&n->pending, malloc(CBUF_TX_MAX * sizeof(void *)), CBUF_TX_MAX);
}

static void node_fini(struct node_t *n, uint32_t i, uint32_t max)
{
	if (n->n_l2) free(n->l2);
	if (n->n_l3) free(n->l3);

	/* free message queues. */
	while (!cbuf_isempty(&n->tx)) {
		struct l2_msg *m = cbuf_get(&n->tx);
		l2_msg_unref(m);
	}
	free(cbuf_fini(&n->tx, NULL));

	while (!cbuf_isempty(&n->tx)) {
		struct l2_msg *m = cbuf_get(&n->tx);
		l2_msg_unref(m);
	}
	free(cbuf_fini(&n->pending, NULL));
}
