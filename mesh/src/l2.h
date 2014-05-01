#ifndef L2_H
#define L2_H

void l2_tick(struct node_t *n);
bool l2_send(struct node_t *n, struct msg_t *m);
void l2_recv(struct node_t *n, struct msg_t *m);

#endif /* L2_H */
