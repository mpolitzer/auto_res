#ifndef QUEUE_H
#define QUEUE_H

/* O(1) for put (enqueue).
 * O(1) for get (dequeue). */
#include <stdbool.h>

struct queue_entry {
	struct queue_entry *next;
};

struct queue_head {
	struct queue_entry *head, **tail;
};

/* -------------------------------------------------------------------------- */
static inline void queue_head_init(struct queue_head *h)
{
	h->tail = &h->head;
	h->head = 0;
}

static inline void queue_put(struct queue_entry *q, struct queue_head *h)
{
	q->next  = 0;
	*h->tail = q;
	h->tail  = &q->next;
}

static inline struct queue_entry *queue_get(struct queue_head *h)
{
	struct queue_entry *q = h->head;

	if (!q)
		return 0;
	if (!q->next)
		h->tail = &h->head;
	h->head = q->next;
	return q;
}

#endif /* QUEUE_H */
