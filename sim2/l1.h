#ifndef L1_H
#define L1_H

#include "node.h"
#include "l2.h"

void           l1_init      (uint32_t nodes);
void           l1_fini      (void);
void           l1_tick      (void);
uint32_t       l1_get_n     (void);
uint32_t       l1_get_tick  (void);
void           l1_set_weight(nid from, nid to, uint8_t weight);
uint8_t        l1_get_weight(nid from, nid to);
struct node_t *l1_get_node  (nid id);

/* l2_send calls l1_send, checks the graph and then calls l2_recv if the
 * transmission is a success. */
void l1_send   (struct l2_msg *msg);
void l1_send_to(struct l2_msg *msg, nid to);

void l1_foreach_node(void (*run)(struct node_t *self));

#endif /* L1_H */
