#ifndef QUEUE_H
#define QUEUE_H

/* single linked list implementation of a queue. This implementation has a
 * twist. It uses 'next != self' to mark as enqueued (busy) and 'next == self'
 * to mark as not queued. This way _put will fail gracefuly.
 *
 * O(1) for put (enqueue).
 * O(1) for get (dequeue). */
#include <stdbool.h>
#define T struct queue_entry
#define H struct queue_head

T {
	T *next;
};

H {
	T *head, **tail;
};

/* A queue entry uses its own pointer as guard. */
#define QUEUE_ENTRY_INIT(name) { &(name) }
#define QUEUE_HEAD_INIT(name) { 0, &(name.head) }

/* -------------------------------------------------------------------------- */
void queue_head_init(H *h);
void queue_entry_init(T *l);

/** Put a element on list tail.
 * Fails if the element is already on the list or uninitialized.
 *
 * @note Removal from the list automatically makes the element ready again. */
void queue_put(T *l, H *h);

/** Get a element from list head. */
T *queue_get(H *h);

/* put & get for overloading types: The types must create the list as the first
 * field like so: 'struct queue _;' */
#define queue_t_put(l, h, t) (queue_put(&((t*)l)->_, h))
#define queue_t_get(h, t)   ((t *)queue_get(h))

typedef T queue_entry;
typedef H queue_head;
#undef T
#undef H
#endif /* QUEUE_H */
