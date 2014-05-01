#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stddef.h>

#include "cbuf.h"

/* reset values for alive and ogm intervals. */
#define ALIVE_TICK_SET (100)
#define ALIVE_TIMEOUT  ((1.3)*ALIVE_TICK_SET)
#define OGM_TICK_SET (250)

#define CBUF_TX_MAX    (8)

/* dst (destination) field special meaning. */
#define BROADCAST ((nid)-1)

/* node ID */
typedef uint16_t nid;

struct node_t {
	nid id;

	nid n_l2;
	nid n_l3;

	uint8_t ogm_tick;

	struct l2_info {
		nid id;
		uint8_t time_until_lost;
		uint8_t alive_timeout;
	} *l2;

	struct l3_info {
		nid id;
		nid hop;
	} *l3;

	struct cbuf tx,
		    pending;
};

#endif /* COMMON_H */
