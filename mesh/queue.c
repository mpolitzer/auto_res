#include "queue.h"
#define T struct queue_entry
#define H struct queue_head

void queue_head_init(H *h)
{
	h->head = 0;
	h->tail = &h->head;
}

void queue_entry_init(T *l)
{
	l->next = l;
}

void queue_put(T *l, H *h)
{
	if (l->next != l)
		return;
	l->next  = 0;
	*h->tail = l;
	h->tail  = &l->next;
}

T *queue_get(H *h)
{
	T *l = h->head;

	if (!l)
		return 0;
	if (!l->next)
		h->tail = &h->head;
	h->head = l->next; /* restore NULL on last element. */
	queue_entry_init(l);
	return l;
}
