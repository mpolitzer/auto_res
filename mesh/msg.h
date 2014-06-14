#ifndef MSG_H
#define MSG_H
#include <stdint.h>
#include <stdlib.h>
#include "queue.h"
#define T struct msg

T {
	queue_entry entry;
	uint8_t prio_high;

	uint16_t dst;
	uint8_t len; /* 1 to 32bytes */
	char pl[];
};

#define L2_HELLO
#define L2_PING
#define L2_ACK
#define L2_PL
//#define L2_PL_BROADCAST
struct l2msg_t {
	uint16_t src; // 2

	uint8_t type; // 3
	uint8_t  crc; // 4

	char pl[];
};

#define L3_OGM
#define L3_ROGM
#define L3_KNOWN
#define L3_PL
#define L3_PL_BROADCAST
struct l3msg_t {
	uint16_t src; // 6
	uint16_t dst; // 8
	uint8_t type; // 9
#if 0
	/* Do split later */
	uint8_t df:1;
	uint8_t mf:1;
	uint8_t fragment_offset:6; // 10
#endif
	char pl[];
};

struct l3msg_ctl {
	uint8_t seq;
};

struct l3msg_pl_broadcast {
	uint8_t seq;
	char pl[];
};

struct l4msg_t {
	int derp;
};

/* msg API ================================================================== */
size_t          msg_sizeof(int layers);
struct l2msg_t *msg_get_l2(T *);
struct l3msg_t *msg_get_l3(T *);
struct l4msg_t *msg_get_l4(T *);

typedef msg_t T;
#undef T
#endif /* MSG_H */
