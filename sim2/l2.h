#ifndef L2_H
#define L2_H

#include "node.h"

struct l2_msg {
	uint16_t ref;

	nid src, dst;

#define L2_ALIVE 0
#define L2_HELLO 1
#define L2_ACK   2
#define L2_L3    3
	uint8_t type;
	uint16_t len;
	char data[];
};

/* other level will handle memory allocation, */
void l2_send(struct node_t *self, struct l2_msg *m);
void l2_recv(struct node_t *self, struct l2_msg *m);

struct l2_msg *l2_msg_alloc(nid src, nid dst, uint8_t t, uint16_t len);
void           l2_msg_ref  (struct l2_msg *m);
void           l2_msg_unref(struct l2_msg *m);

/** \brief Grab l2 payload/data filed.
 *  \note Checking for NULL will not work! Check len instead. */
void          *l2_msg_data(struct l2_msg *m);

/** \brief lenght of data field.
 * \retval 0 for no data. */
uint16_t       l2_msg_len (struct l2_msg *m);

/* ========================================================================== */
void l2_tick(struct node_t *self);

#endif /* L2_H */
