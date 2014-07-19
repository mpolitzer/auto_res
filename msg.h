#ifndef MSG_H
#define MSG_H
#include <stdint.h>
#include <stdlib.h>
#include "queue.h"
#define T struct msg

T {
	queue_entry entry;

	uint8_t dst;
	uint8_t len:5; /* 1 to 32bytes */
	uint8_t prio_high:3;
	char pl[];
};

#define L2_HELLO
#define L2_PING
#define L2_ACK
#define L2_PL
//#define L2_PL_BROADCAST
struct l2msg_t {
	uint8_t src; // 1

	uint8_t type; // 2

	char pl[];
};

#define L3_OGM
#define L3_ROGM
#define L3_KNOWN
#define L3_PL
#define L3_PL_BROADCAST
struct l3msg_t {
	uint8_t seq:1;
	uint8_t type:7; // 3

	uint8_t src; // 4
	uint8_t dst; // 5

	char pl[];
};

/* msg API ================================================================== */
size_t          msg_sizeof(int layers);
struct l2msg_t *msg_get_l2(T *);
struct l3msg_t *msg_get_l3(T *);

typedef msg_t T;
#undef T
#endif /* MSG_H */
