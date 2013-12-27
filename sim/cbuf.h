/** \file
 * Circular BUFfer with a power of 2 size.
 * Thread safe.
 * ========================================================================== */
#ifndef CBUF_H
#define CBUF_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

struct cbuf 
{
	void **p;
	uint16_t head, tail, mask;
};
typedef struct cbuf CBuf;

static inline void cbuf_init(struct cbuf *b, void **p, uint16_t n) 
{
	assert(b && "invalid 'b' is NULL");
	assert((n & (n-1)) == 0 && "'n' not a power of 2.");

	b->p = p;
	b->mask = n-1;
	b->head = b->tail = 0;
}

static inline void **cbuf_fini(struct cbuf *b, uint16_t *n) 
{
	if (n) *n = b->mask + 1;

	return b->p;
}

static inline uint16_t cbuf_count(struct cbuf *b) 
{
	assert(b && "invalid 'b' is NULL");

	return (b->head - b->tail) + b->mask + 1;
}

static inline bool cbuf_isfull(struct cbuf *b) 
{
	assert(b && "invalid 'b' is NULL");

	return cbuf_count(b) == 0;
}

static inline bool cbuf_isempty(struct cbuf *b) 
{
	assert(b && "invalid 'b' is NULL");

	return cbuf_count(b) == b->mask+1;
}

static inline void cbuf_put(struct cbuf *b, void *v) 
{
	assert(b && "invalid 'b' is NULL");
	assert(!cbuf_isfull(b) && "buffer overflow");

	/* if full, drop oldest value */
	if (cbuf_isfull(b)) b->head++;
	b->p[b->tail++ & b->mask] = v;
}

static inline void* cbuf_get(struct cbuf *b) 
{
	assert(b && "invalid 'b' is NULL");
	assert(!cbuf_isempty(b) && "buffer underflow");

	if (cbuf_isempty(b)) return NULL;
	return b->p[b->head++ & b->mask];
}

#endif /* CBUF_H */
