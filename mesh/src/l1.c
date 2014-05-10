#include "node.h"
#include "l1.h"

struct graph {
	uint16_t length;
	uint8_t M[NODE_MAX][NODE_MAX];
	struct node_t N[NODE_MAX];
};
struct graph _graph;

/* call all the ticks... */
static void l1_foreach_node(void (*run)(struct node_t *))
{
	for (int i=0; i<_graph.length; i++)
		run(&_N[i]);
}

void l1_init(uint16_t n)
{
	_graph.length = n;
	l1_foreach_node(node_init);
}

void l1_set_weight(nid_t i, nid_t j, uint8_t v)
{
	_graph.M[i][j] = v;
}

uint8_t l1_get_weight(nid_t i, nid_t j)
{
	return _graph.M[i][j];
}
