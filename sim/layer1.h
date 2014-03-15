#ifndef L1_H
#define L1_H

#include "layer2.h"
#include "common.h"

/* --------------------------------------- */

void l1_init(uint16_t count);

void    l1_set_weight(nodeid_t n1, nodeid_t n2, uint8_t v);
uint8_t l1_get_weight(nodeid_t n1, nodeid_t n2);

Node   *l1_get_node(nodeid_t n);

void    l1_send(nodeid_t n, MessageL2 *m);
void    l1_tick(void);
int     l1_get_tick(void);

/* --------------------------------------- */

#endif // L1_H
