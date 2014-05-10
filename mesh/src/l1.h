#ifndef L1_H
#define L1_H

void          l1_init(uint16_t nodes);
void          l1_set_weight(nid_t i, nid_t j, uint8_t v);
uint8_t       l1_get_weight(nid_t i, nid_t j);
struct node_t l1_get_node(nid_t i);

#endif /* L1_H */
