/* --------------------------------------- */

#include <assert.h>

#include "node.h"
#include "layer1.h"
#include <stdlib.h>
#include <limits.h>

/* --------------------------------------- */

static uint8_t M[NODE_MAX][NODE_MAX];
static Node nodes[NODE_MAX];
static uint16_t node_count;

/* --------------------------------------- */

void l1_init(uint16_t count)
{
	assert(count && count < NODE_MAX && "Amount of nodes is too damn high!");
	node_count = count;

	int i;
	for (i=1; i<count; i++) {
		nodes[i].exist = true;
		nodes[i].id = i;
		cbuf_init(&(nodes[i].tx), malloc(sizeof(void*)*MSG_BUF_MAX), MSG_BUF_MAX);
		cbuf_init(&(nodes[i].rx), malloc(sizeof(void*)*MSG_BUF_MAX), MSG_BUF_MAX);
	}
}

void l1_set_weight(nodeid_t n1, nodeid_t n2, uint8_t v)
{
	assert(n1 < NODE_MAX && "node is out of bounds!");
	assert(n2 < NODE_MAX && "node is out of bounds!");
	M[n1][n2] = v;
}

uint8_t l1_get_weight(nodeid_t n1, nodeid_t n2)
{
	assert(n1 < NODE_MAX && "node is out of bounds!");
	assert(n2 < NODE_MAX && "node is out of bounds!");

	return M[n1][n2];
}

Node *l1_get_node(nodeid_t n)
{
	assert(n < NODE_MAX && "node is out of bounds!");

	return &nodes[n];
}

void l1_send(nodeid_t n, MessageL2 *m)
{
	nodeid_t i;
	for (i=1; i<node_count; i++) {
		if (l1_get_weight(n, i) > (rand() % UCHAR_MAX))
			l2_recv(l1_get_node(i), m);
	}
}
